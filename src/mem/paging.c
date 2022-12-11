#include "paging.h"
#include "../lib.h"
#include "../x86_desc.h"


/* This is a 4kb page for page table */
pte_t dma_page_table[NUM_ENTRIES] __attribute__ ((aligned (FOUR_MB_BLOCK)));

/* This is a 4kb page for page directory */
pde_t main_page_dir[NUM_ENTRIES] __attribute__ ((aligned (FOUR_MB_BLOCK)));


/* void init_paging()
 * 
 * Calls all intilizations for paging and sets control registers for enabling paging
 * Inputs: None
 * Outputs: None
 * Side Effects: Sets control registers for paging
 */
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
        : "r" (main_page_dir)
        : "%eax", "cc"
    );
}


/* void init_pd()
 * 
 * Initializes paging directories to correct values for video memory
 * and kernel, intializes remaining directory entries to 0
 * Inputs: None
 * Outputs: None
 * Side Effects: Sets values for paging directory entries
 */
void init_pd() {
    unsigned short pde_idx;

    for (pde_idx = 0; pde_idx < NUM_ENTRIES; pde_idx++) { //init page directory entries: all zeros excepted pde_mb is page_size 1
        main_page_dir[pde_idx].pde_mb.present = PAGE_NOT_PRESENT;
        main_page_dir[pde_idx].pde_mb.read_write = PAGE_NOT_WRITABLE;
        main_page_dir[pde_idx].pde_mb.user_supervisor = 0;
        main_page_dir[pde_idx].pde_mb.write_through = 0;
        main_page_dir[pde_idx].pde_mb.cache_disable = 0;
        main_page_dir[pde_idx].pde_mb.accessed = 0; 
        main_page_dir[pde_idx].pde_mb.dirty = 0; 
        main_page_dir[pde_idx].pde_mb.page_size = 1; //4 mB, points to page next
        main_page_dir[pde_idx].pde_mb.global = 0; 
        main_page_dir[pde_idx].pde_mb.att_table = 0; 
        main_page_dir[pde_idx].pde_mb.addr_39_32 = 0;
        main_page_dir[pde_idx].pde_mb.rsvd = 0;
        main_page_dir[pde_idx].pde_mb.addr_31_22 = 0;

        // main_page_dir[pde_idx].pde_kb.present = 0;
        // main_page_dir[pde_idx].pde_kb.read_write = 0;
        // main_page_dir[pde_idx].pde_kb.user_supervisor = 0; 
        // main_page_dir[pde_idx].pde_kb.write_through = 0; 
        // main_page_dir[pde_idx].pde_kb.cache_disable = 0; 
        // main_page_dir[pde_idx].pde_kb.accessed = 0; 
        // main_page_dir[pde_idx].pde_kb.page_size = 0; 
        // main_page_dir[pde_idx].pde_kb.addr_31_12 = 0;
    }

    // Directory entry for 4kb video mem page
    pde_idx = 0;
    main_page_dir[pde_idx].pde_kb.present = PAGE_PRESENT; // now present
    main_page_dir[pde_idx].pde_kb.read_write = PAGE_WRITABLE; // video mem write enabled
    main_page_dir[pde_idx].pde_kb.user_supervisor = 0;
    main_page_dir[pde_idx].pde_kb.write_through = 0; 
    main_page_dir[pde_idx].pde_kb.cache_disable = 0; 
    main_page_dir[pde_idx].pde_kb.accessed = 0; 
    main_page_dir[pde_idx].pde_kb.page_size = 0; 
    main_page_dir[pde_idx].pde_kb.addr_31_12 = (((unsigned int)(dma_page_table)) >> KB_ADDR_OFF);

    // Directory entry for 4mB kernel page    
    pde_idx = 1;
    main_page_dir[pde_idx].pde_mb.present = PAGE_PRESENT; //now present
    main_page_dir[pde_idx].pde_mb.read_write = PAGE_NOT_WRITABLE;
    main_page_dir[pde_idx].pde_mb.user_supervisor = 0; 
    main_page_dir[pde_idx].pde_mb.write_through = 0;
    main_page_dir[pde_idx].pde_mb.cache_disable = 0;
    main_page_dir[pde_idx].pde_mb.accessed = 0;
    main_page_dir[pde_idx].pde_mb.dirty = 0; 
    main_page_dir[pde_idx].pde_mb.page_size = 1; //4 mB, points to page next
    main_page_dir[pde_idx].pde_mb.global = 1; // global used for kernel pages
    main_page_dir[pde_idx].pde_mb.att_table = 0; 
    main_page_dir[pde_idx].pde_mb.addr_39_32 = 0;
    main_page_dir[pde_idx].pde_mb.rsvd = 0;
    main_page_dir[pde_idx].pde_mb.addr_31_22 = (KERNEL_ADDR >> MB_ADDR_OFF);
}

/* void init_pt()
 * 
 * Initializes paging table to correct values for video memory
 * and kernel, intializes remaining directory entries to 0
 * Inputs: None
 * Outputs: None
 * Side Effects: Sets values for paging table entries
 */
void init_pt() {
    unsigned short pte_idx;

    for (pte_idx = 0; pte_idx < NUM_ENTRIES; pte_idx++) {
        dma_page_table[pte_idx].present = PAGE_NOT_PRESENT;
        dma_page_table[pte_idx].read_write = PAGE_NOT_WRITABLE;
        dma_page_table[pte_idx].user_supervisor = 0;
        dma_page_table[pte_idx].write_through = 0;
        dma_page_table[pte_idx].cache_disable = 0;
        dma_page_table[pte_idx].accessed = 0;
        dma_page_table[pte_idx].dirty = 0;
        dma_page_table[pte_idx].att_table = 0;
        dma_page_table[pte_idx].global = 0;
        dma_page_table[pte_idx].available = 0;
        dma_page_table[pte_idx].addr_31_12 = (pte_idx*PAGE_MULT >> KB_ADDR_OFF);
    }

    pte_idx = VIDEO_MEM_ADDR >> KB_ADDR_OFF;
    dma_page_table[pte_idx].present = PAGE_PRESENT;
    dma_page_table[pte_idx].read_write = PAGE_WRITABLE;
    dma_page_table[pte_idx].user_supervisor = 0; 
    dma_page_table[pte_idx].write_through = 0; 
    dma_page_table[pte_idx].cache_disable = 0; 
    dma_page_table[pte_idx].accessed = 0; 
    dma_page_table[pte_idx].dirty = 0; 
    dma_page_table[pte_idx].att_table = 0; 
    dma_page_table[pte_idx].global = 0;
    dma_page_table[pte_idx].addr_31_12 = (VIDEO_MEM_ADDR >> KB_ADDR_OFF);
}
