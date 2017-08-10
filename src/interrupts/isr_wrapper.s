.intel_syntax noprefix
.align   8

 
isr_wrapper:
 	//movb  $0x41 , 0xB8000
	pushad;
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    push eax
    call isr_handler
    pop eax
    popad;
    iret
    
irq_wrapper:
 	//movb  $0x41 , 0xB8000
	pushad;
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    push eax
    call irq_handler
    pop eax
    popad;
    iret
    
    
   
.att_syntax noprefix

.globl isr_0
.globl isr_1
.globl isr_2
.globl isr_3
.globl isr_4
.globl isr_5
.globl isr_6
.globl isr_7
.globl isr_8
.globl isr_9
.globl isr_10
.globl isr_11
.globl isr_12
.globl isr_13
.globl isr_14
.globl isr_15
.globl isr_16
.globl isr_17
.globl isr_18



isr_0:
	mov $0, %eax
	jmp isr_wrapper
	
isr_1:
	xchgw %bx, %bx
	mov $1, %eax
	jmp isr_wrapper
	
isr_2:
	xchgw %bx, %bx
	mov $2, %eax
	jmp isr_wrapper
	
isr_3:
	mov $3, %eax
	jmp isr_wrapper
	
isr_4:
	mov $4, %eax
	jmp isr_wrapper
	
isr_5:
	mov $5, %eax
	jmp isr_wrapper
	
isr_6:
	mov $6, %eax
	jmp isr_wrapper
	
isr_7:
	mov $7, %eax
	jmp isr_wrapper
	
isr_8:
	mov $8, %eax
	jmp isr_wrapper
	
isr_9:
	mov $9, %eax
	jmp isr_wrapper
	
isr_10:
	mov $10, %eax
	jmp isr_wrapper
	
isr_11:
	mov $11, %eax
	jmp isr_wrapper
	
isr_12:
	mov $12, %eax
	jmp isr_wrapper
	
isr_13:
	mov $13, %eax
	jmp isr_wrapper
	
isr_14:
	mov $14, %eax
	jmp isr_wrapper
	
isr_15:
	mov $15, %eax
	jmp isr_wrapper
	
isr_16:
	mov $16, %eax
	jmp isr_wrapper
	
isr_17:
	mov $17, %eax
	jmp isr_wrapper
	
isr_18:
	mov $18, %eax
	jmp isr_wrapper
	
	
	
	
.globl irq_0
.globl irq_1
.globl irq_2
.globl irq_3
.globl irq_4
.globl irq_5
.globl irq_6
.globl irq_7
.globl irq_8
.globl irq_9
.globl irq_10
.globl irq_11
.globl irq_12
.globl irq_13
.globl irq_14
.globl irq_15
	
	
	
	
irq_0:
	mov $0, %eax
	jmp irq_wrapper
	
irq_1:
	mov $1, %eax
	jmp irq_wrapper
	
irq_2:
	mov $2, %eax
	jmp irq_wrapper
	
irq_3:
	mov $3, %eax
	jmp irq_wrapper
	
irq_4:
	mov $4, %eax
	jmp irq_wrapper
	
irq_5:
	mov $5, %eax
	jmp irq_wrapper
	
irq_6:
	mov $6, %eax
	jmp irq_wrapper
	
irq_7:
	mov $7, %eax
	jmp irq_wrapper
	
irq_8:
	mov $8, %eax
	jmp irq_wrapper
	
irq_9:
	mov $9, %eax
	jmp irq_wrapper
	
irq_10:
	mov $10, %eax
	jmp irq_wrapper
	
irq_11:
	mov $11, %eax
	jmp irq_wrapper
	
irq_12:
	mov $12, %eax
	jmp irq_wrapper
	
irq_13:
	mov $13, %eax
	jmp irq_wrapper
	
irq_14:
	mov $14, %eax
	jmp irq_wrapper
	
irq_15:
	mov $15, %eax
	jmp irq_wrapper
	
.globl sysCallAsmHandler

sysCallAsmHandler:
	call sysCallHandler
    iret

	
	
	
	
	
	