#include "idt.h"
#include "../x86_desc.h"
#include "../lib.h"


/* void build_idt_entry(uint8_t vector, void* isr)
 * Description: Create an individual IDT entry
 * Inputs: None
 * Return Value: None
 * Side Effects: Changes memory in the IDT table
 */
void build_idt_entry(uint8_t vector, void* isr) {
    SET_IDT_ENTRY(idt[vector], isr); // Set the offset fields to the function address (isr)
    idt[vector].seg_selector = KERNEL_CS; // third byte in GDT
    idt[vector].present = 0x1; // Interrupts are present thus 1
    idt[vector].dpl = 0x0; // privilege level 0 (kernel) for exp and ints
    idt[vector].reserved0 = 0x0; // | Defined by x86 intel manual
    idt[vector].reserved1 = 0x1; // |
    idt[vector].reserved2 = 0x1; // |
    idt[vector].reserved3 = 0x0; // V
    idt[vector].reserved4 = 0x0; //---
    idt[vector].size = 0x1; // 32 bit descriptors = 1, 16 bit = 0
}


/* extern void init_idt()
 * Description: Initialize the IDT
 * Inputs: None
 * Return Value: None
 * Side Effects: Changes memory in the IDT table
 */
void init_idt(void){
    // Build and fill the IDT with the following handlers
    build_idt_entry(0, except0_linkage);
    build_idt_entry(1, except1_linkage);
    build_idt_entry(2, except2_linkage);
    build_idt_entry(3, except3_linkage);
    build_idt_entry(4, except4_linkage);
    build_idt_entry(5, except5_linkage);
    build_idt_entry(6, except6_linkage);
    build_idt_entry(7, except7_linkage);
    build_idt_entry(8, except8_linkage);
    build_idt_entry(9, except9_linkage);
    build_idt_entry(10, except10_linkage);
    build_idt_entry(11, except11_linkage);
    build_idt_entry(12, except12_linkage);
    build_idt_entry(13, except13_linkage);
    build_idt_entry(14, except14_linkage);
    // No Exception 15
    build_idt_entry(16, except16_linkage);
    build_idt_entry(17, except17_linkage);
    build_idt_entry(18, except18_linkage);
    build_idt_entry(19, except19_linkage);

    build_idt_entry(32, except19_linkage);
    build_idt_entry(33, except19_linkage);
    build_idt_entry(40, except19_linkage);

    // Load the IDTR with the location of the IDT
    lidt(idt_desc_ptr);
}
