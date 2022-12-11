#ifndef _EXCEPT_HANDLE_H
#define _EXCEPT_HANDLE_H

#include "../types.h"

// Exception Handlers
void zero_divide_handle(void);
void debug_handle(void);
void nmi_handle(void);
void breakpoint_handle(void);
void overflow_handle(void);
void bound_handle(void);
void invalid_op_handle(void);
void device_not_avail_handle(void);
void double_handle(void);
void cso_handle(void);
void inval_tss_handle(void);
void seg_not_pres_handle(void);
void stack_fault_handle(void);
void gen_protect_handle(void);
void page_fault_handle(void);
void float_error_handle(void);
void align_check_handle(void);
void machine_check_handle(void);
void simd_fp_handle(void);


#endif
