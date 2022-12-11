#include "paging.h"
#include "../lib.h"
#include "../x86_desc.h"

/* This is a 4kb page for page table */
pte_t dma_table[1024] __attribute__ ((aligned (FOUR_MB_BLOCK)));

/* This is a 4kb page for page directory */
pde_t page_dir[1024] __attribute__ ((aligned (FOUR_MB_BLOCK)));


void init_paging(){

    init_pd();
    init_pt();

    /* set paging settings */
    // page extension bit in cr4, cr3 gets pdbr, paging enabled in cr0 MSB
    asm volatile ("                     \n\
        movl %%cr4, %%eax               \n\
        orl $0x00000010, %%eax          \n\
        movl %%eax, %%cr4               \n\
        movl %0, %%eax                  \n\
        andl $0xFFFFFC00, %%eax         \n\
        movl %%eax, %%cr3               \n\
        movl %%cr0, %%eax               \n\
        orl $0x80000000, %%eax          \n\
        movl %%eax, %%cr0               \n\
        "
        : 
        : "r" (page_dir)
        : "%eax", "cc"
    );
}

void init_pd() {
    unsigned short pde_idx;

    for (pde_idx = 0; pde_idx < NUM_ENTRIES; pde_idx++) { //init page directory entries: all zeros excepted pde_mb is page_size 1
        page_dir[pde_idx].pde_mb.present = 0;
        page_dir[pde_idx].pde_mb.read_write = 0;
        page_dir[pde_idx].pde_mb.user_supervisor = 0;
        page_dir[pde_idx].pde_mb.write_through = 0; 
        page_dir[pde_idx].pde_mb.cache_disable = 0;
        page_dir[pde_idx].pde_mb.accessed = 0; 
        page_dir[pde_idx].pde_mb.dirty = 0; 
        page_dir[pde_idx].pde_mb.page_size = 1; //4 mB, points to page next
        page_dir[pde_idx].pde_mb.global = 0; 
        page_dir[pde_idx].pde_mb.att_table = 0; 
        page_dir[pde_idx].pde_mb.addr_39_32 = 0;
        page_dir[pde_idx].pde_mb.rsvd = 0;
        page_dir[pde_idx].pde_mb.addr_31_22 = 0;

        page_dir[pde_idx].pde_kb.present = 0;
        page_dir[pde_idx].pde_kb.read_write = 0;
        page_dir[pde_idx].pde_kb.user_supervisor = 0; 
        page_dir[pde_idx].pde_kb.write_through = 0; 
        page_dir[pde_idx].pde_kb.cache_disable = 0; 
        page_dir[pde_idx].pde_kb.accessed = 0; 
        page_dir[pde_idx].pde_kb.page_size = 0; 
        page_dir[pde_idx].pde_kb.addr_31_12 = 0;
    }

    //first entry for 4kb video mem page
    pde_idx = 0;
    page_dir[pde_idx].pde_kb.present = 1; // now present
    page_dir[pde_idx].pde_kb.read_write = 1; // video mem write enabled
    page_dir[pde_idx].pde_kb.user_supervisor = 0;
    page_dir[pde_idx].pde_kb.write_through = 0; 
    page_dir[pde_idx].pde_kb.cache_disable = 0; 
    page_dir[pde_idx].pde_kb.accessed = 0; 
    page_dir[pde_idx].pde_kb.page_size = 0; 
    page_dir[pde_idx].pde_kb.addr_31_12 = (unsigned int) dma_table >> KB_ADDR_OFF;

    //second entry for 4mB kernel page    
    pde_idx = 1;
    page_dir[pde_idx].pde_mb.present = 1; //now present
    page_dir[pde_idx].pde_mb.read_write = 0;
    page_dir[pde_idx].pde_mb.user_supervisor = 0; 
    page_dir[pde_idx].pde_mb.write_through = 0;
    page_dir[pde_idx].pde_mb.cache_disable = 0;
    page_dir[pde_idx].pde_mb.accessed = 0;
    page_dir[pde_idx].pde_mb.dirty = 0; // page is written
    page_dir[pde_idx].pde_mb.page_size = 1; //4 mB, points to page next
    page_dir[pde_idx].pde_mb.global = 1; // global used for kernel pages
    page_dir[pde_idx].pde_mb.att_table = 0; 
    page_dir[pde_idx].pde_mb.addr_39_32 = 0;
    page_dir[pde_idx].pde_mb.rsvd = 0;
    page_dir[pde_idx].pde_mb.addr_31_22 = KERNEL_ADDR >> MB_ADDR_OFF;
}


void init_pt() {
    unsigned short pte_idx;

    for (pte_idx = 0; pte_idx < NUM_ENTRIES; pte_idx++) {
        dma_table[pte_idx].present = 0;
        dma_table[pte_idx].read_write = 0;
        dma_table[pte_idx].user_supervisor = 0;
        dma_table[pte_idx].write_through = 0;
        dma_table[pte_idx].cache_disable = 0;
        dma_table[pte_idx].accessed = 0;
        dma_table[pte_idx].dirty = 0;
        dma_table[pte_idx].att_table = 0;
        dma_table[pte_idx].global = 0;
        dma_table[pte_idx].available = 0;
        dma_table[pte_idx].addr_31_12 = pte_idx*PAGE_MULT >> KB_ADDR_OFF;
    }

    pte_idx = VIDEO_MEM_ADDR >> KB_ADDR_OFF;
    dma_table[pte_idx].present = 1; //now present
    dma_table[pte_idx].read_write = 1; //video mem write enabled
    dma_table[pte_idx].user_supervisor = 0; 
    dma_table[pte_idx].write_through = 0; 
    dma_table[pte_idx].cache_disable = 0; 
    dma_table[pte_idx].accessed = 0; 
    dma_table[pte_idx].dirty = 0; 
    dma_table[pte_idx].att_table = 0; 
    dma_table[pte_idx].global = 0;
    dma_table[pte_idx].addr_31_12 = VIDEO_MEM_ADDR >> KB_ADDR_OFF;
}
