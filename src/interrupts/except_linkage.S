#define ASM 1


# Make linkages available in other files
.globl except0_linkage
.globl except1_linkage
.globl except2_linkage
.globl except3_linkage
.globl except4_linkage
.globl except5_linkage
.globl except6_linkage
.globl except7_linkage
.globl except8_linkage
.globl except9_linkage
.globl except10_linkage
.globl except11_linkage
.globl except12_linkage
.globl except13_linkage
.globl except14_linkage
# No Exception 15
.globl except16_linkage
.globl except17_linkage
.globl except18_linkage
.globl except19_linkage

.globl zero_divide_handle
.globl debug_handle
.globl nmi_handle
.globl breakpoint_handle
.globl overflow_handle
.globl bound_handle
.globl invalid_op_handle
.globl device_not_avail_handle
.globl double_handle
.globl cso_handle
.globl inval_tss_handle
.globl seg_not_pres_handle
.globl stack_fault_handle
.globl gen_protect_handle
.globl page_fault_handle
.globl float_error_handle
.globl align_check_handle
.globl machine_check_handle
.globl simd_fp_handle


exception_jumptable: .long zero_divide_handle, debug_handle, nmi_handle, breakpoint_handle, overflow_handle, bound_handle, invalid_op_handle, \
                           device_not_avail_handle, double_handle, cso_handle, inval_tss_handle, seg_not_pres_handle, stack_fault_handle, \
                           gen_protect_handle, page_fault_handle, float_error_handle, align_check_handle, machine_check_handle, simd_fp_handle


# Macro to create Assembly Linkage functions for different exception interrupts
# These functions push the interrupt vector onto the stack so that the general
# exception handler can jump to the right exception handler. It also protects
# all of the registers.
#define EXCEPT_ASM_LINKAGE(name, idx)           \
    name:                                       \
        pushal;                                 \
        pushfl;                                 \
        movl $idx, %eax;                        \
        call *exception_jumptable(, %eax, 4);   \
        addl $4, %esp;                          \
        popfl;                                  \
        popal;                                  \
        iret;


# Generate assembly linkage functions
EXCEPT_ASM_LINKAGE(except0_linkage, 0)
EXCEPT_ASM_LINKAGE(except1_linkage, 1)
EXCEPT_ASM_LINKAGE(except2_linkage, 2)
EXCEPT_ASM_LINKAGE(except3_linkage, 3)
EXCEPT_ASM_LINKAGE(except4_linkage, 4)
EXCEPT_ASM_LINKAGE(except5_linkage, 5)
EXCEPT_ASM_LINKAGE(except6_linkage, 6)
EXCEPT_ASM_LINKAGE(except7_linkage, 7)
EXCEPT_ASM_LINKAGE(except8_linkage, 8)
EXCEPT_ASM_LINKAGE(except9_linkage, 9)
EXCEPT_ASM_LINKAGE(except10_linkage, 10)
EXCEPT_ASM_LINKAGE(except11_linkage, 11)
EXCEPT_ASM_LINKAGE(except12_linkage, 12)
EXCEPT_ASM_LINKAGE(except13_linkage, 13)
EXCEPT_ASM_LINKAGE(except14_linkage, 14)
# No Exception 15
EXCEPT_ASM_LINKAGE(except16_linkage, 16)
EXCEPT_ASM_LINKAGE(except17_linkage, 17)
EXCEPT_ASM_LINKAGE(except18_linkage, 18)
EXCEPT_ASM_LINKAGE(except19_linkage, 19)
