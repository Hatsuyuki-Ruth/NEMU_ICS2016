#include "common.h"
#include "memory.h"
#include <string.h>
#include <elf.h>

#define ELF_OFFSET_IN_DISK 0

#ifdef HAS_DEVICE
void ide_read(uint8_t *, uint32_t, uint32_t);
#else
void ramdisk_read(uint8_t *, uint32_t, uint32_t);
#endif

#define STACK_SIZE (1 << 24)

void create_video_mapping();
uint32_t get_ucr3();

static void read_from_elf(void *dest, size_t offset, size_t size) {
#ifdef HAS_DEVICE
    ide_read(dest, offset, size);
#else
    ramdisk_read(dest, offset, size);
#endif
}

static uint32_t alloc_one_clean_page(uint32_t va) {
    uint32_t pa = mm_malloc(va, PAGE_SIZE);
    memset(pa_to_va(pa), 0, PAGE_SIZE);
    return pa;
}

static void load_segment_from_elf(unsigned destpos, size_t memsz, size_t elfoff, size_t filesz) {
    int offset = destpos & 0xfff;
    memsz += offset;
    destpos = destpos & 0xfffff000;
    uint8_t *dest;    
    int cur_size;
    while (filesz) {
        cur_size = (PAGE_SIZE - offset) < filesz ? (PAGE_SIZE - offset) : filesz;
        dest = pa_to_va(alloc_one_clean_page(destpos)); // new page should zero-filled
        read_from_elf(dest + offset, elfoff, cur_size);
        offset = 0;
        elfoff += cur_size;
        destpos += PAGE_SIZE;
        memsz -= cur_size;
        filesz -= cur_size;
    }
    while (memsz > 0) {
        cur_size = PAGE_SIZE < memsz ? PAGE_SIZE : memsz;
        alloc_one_clean_page(destpos);
        destpos += PAGE_SIZE;
        memsz -= cur_size;
    }
}

uint32_t loader() {
    uint8_t buf[4096];
#ifdef HAS_DEVICE
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
#else
	ramdisk_read(buf, ELF_OFFSET_IN_DISK, 4096);
#endif
    int i;

	const uint32_t elf_magic = 0x464c457f;
	uint32_t *p_magic = (void *)buf;
	nemu_assert(*p_magic == elf_magic);

    static Elf32_Ehdr ehdr;
    static Elf32_Phdr phdr;
    
    read_from_elf(&ehdr, 0, sizeof(ehdr));
    nemu_assert(ehdr.e_phentsize == sizeof(phdr));
    
    extern uint32_t brk;
	
	for(i = 0; i < ehdr.e_phnum; i++) {
	    read_from_elf(&phdr, ehdr.e_phoff + ehdr.e_phentsize * i, ehdr.e_phentsize);
		if (phdr.p_type == PT_LOAD) {
			load_segment_from_elf(phdr.p_vaddr, phdr.p_memsz, phdr.p_offset, phdr.p_filesz);
#ifdef IA32_PAGE
			uint32_t new_brk = (phdr.p_vaddr + phdr.p_memsz - 1) & 0xfffff000;
			if(brk < new_brk) { brk = new_brk; }
#endif
		}
	}   
	volatile uint32_t entry = ehdr.e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
