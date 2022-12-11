#include "except_handle.h"
#include "../lib.h"


#define except_handle_gen(err_name, func_name)   \
    void func_name(){                            \
        reset_screen();                          \
        printf(""#err_name"\n System Halting!"); \
        asm volatile ("hlt;"); }


except_handle_gen(Divide by Zero Exception, zero_divide_handle);
except_handle_gen(Debug Exception, debug_handle);
except_handle_gen(Non-Maskable Interrupt, nmi_handle);
except_handle_gen(Breakpoint Exception, breakpoint_handle);
except_handle_gen(Overflow Exception, overflow_handle);
except_handle_gen(Bound Range Exceeded Exception, bound_handle);
except_handle_gen(Invalid Opcode Exception, invalid_op_handle);
except_handle_gen(Device Not Available Exception, device_not_avail_handle);
except_handle_gen(Double Fault Exception, double_handle);
except_handle_gen(Coprocessor Segment Overrun, cso_handle);
except_handle_gen(Invalid TSS Exception, inval_tss_handle);
except_handle_gen(Segment Not Present, seg_not_pres_handle);
except_handle_gen(Stack Fault Exception, stack_fault_handle);
except_handle_gen(General Protection Exception, gen_protect_handle);
except_handle_gen(Page Fault Exception, page_fault_handle);
// NO VECTOR 15
except_handle_gen(x87 FPU Floating-Point Error, float_error_handle);
except_handle_gen(Alignment Check Exception, align_check_handle);
except_handle_gen(Machine-Check Exception, machine_check_handle);
except_handle_gen(SIMD Floating-Point Exception, simd_fp_handle);
