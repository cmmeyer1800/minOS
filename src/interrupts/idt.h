#ifndef _IDT_H
#define _IDT_H

#include "../types.h"

void except0_linkage(void);
void except1_linkage(void);
void except2_linkage(void);
void except3_linkage(void);
void except4_linkage(void);
void except5_linkage(void);
void except6_linkage(void);
void except7_linkage(void);
void except8_linkage(void);
void except9_linkage(void);
void except10_linkage(void);
void except11_linkage(void);
void except12_linkage(void);
void except13_linkage(void);
void except14_linkage(void);
void except15_linkage(void);
void except16_linkage(void);
void except17_linkage(void);
void except18_linkage(void);
void except19_linkage(void);

void build_idt_entry(uint8_t vector, void* isr);
void init_idt(void);

#endif
