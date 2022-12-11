#ifndef _PAGING_H
#define _PAGING_H

#include "../types.h"

#define KERNEL_ADDR 0x400000 //4MB - 8MB
#define VIDEO_MEM_ADDR 0xB8000 //4kB within 0-4MB
#define NUM_ENTRIES 1024
#define FOUR_MB_BLOCK NUM_ENTRIES*4 //4096
#define KB_ADDR_OFF 12 // to extract bit range 31:12
#define MB_ADDR_OFF 22 // to extract bit range 31:22
#define PAGE_MULT 4 // page multiplier, multiply by 4 since each page is 4kB

void init_paging();
void init_pd();
void init_pt();

#endif 
