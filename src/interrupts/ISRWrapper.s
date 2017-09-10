.intel_syntax noprefix
.align   8
 
ISRWrapper:
 	//movb  $0x41 , 0xB8000
	pushad;
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    push eax
    call ISRHandler
    pop eax
    popad;
    iret
    
IRQWrapper:
 	//movb  $0x41 , 0xB8000
	pushad;
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    push eax
    call IRQHandler
    pop eax
    popad;
    iret
   
.att_syntax noprefix

.globl ISR0
.globl ISR1
.globl ISR2
.globl ISR3
.globl ISR4
.globl ISR5
.globl ISR6
.globl ISR7
.globl ISR8
.globl ISR9
.globl ISR10
.globl ISR11
.globl ISR12
.globl ISR13
.globl ISR14
.globl ISR15
.globl ISR16
.globl ISR17
.globl ISR18

ISR0:
	mov $0, %eax
	jmp ISRWrapper
	
ISR1:
	xchgw %bx, %bx
	mov $1, %eax
	jmp ISRWrapper
	
ISR2:
	xchgw %bx, %bx
	mov $2, %eax
	jmp ISRWrapper
	
ISR3:
	mov $3, %eax
	jmp ISRWrapper
	
ISR4:
	mov $4, %eax
	jmp ISRWrapper
	
ISR5:
	mov $5, %eax
	jmp ISRWrapper
	
ISR6:
	mov $6, %eax
	jmp ISRWrapper
	
ISR7:
	mov $7, %eax
	jmp ISRWrapper
	
ISR8:
	mov $8, %eax
	jmp ISRWrapper
	
ISR9:
	mov $9, %eax
	jmp ISRWrapper
	
ISR10:
	mov $10, %eax
	jmp ISRWrapper
	
ISR11:
	mov $11, %eax
	jmp ISRWrapper
	
ISR12:
	mov $12, %eax
	jmp ISRWrapper
	
ISR13:
	mov $13, %eax
	jmp ISRWrapper
	
ISR14:
	mov $14, %eax
	jmp ISRWrapper
	
ISR15:
	mov $15, %eax
	jmp ISRWrapper
	
ISR16:
	mov $16, %eax
	jmp ISRWrapper
	
ISR17:
	mov $17, %eax
	jmp ISRWrapper
	
ISR18:
	mov $18, %eax
	jmp ISRWrapper
	
.globl IRQ0
.globl IRQ1
.globl IRQ2
.globl IRQ3
.globl IRQ4
.globl IRQ5
.globl IRQ6
.globl IRQ7
.globl IRQ8
.globl IRQ9
.globl IRQ10
.globl IRQ11
.globl IRQ12
.globl IRQ13
.globl IRQ14
.globl IRQ15
	
IRQ0:
	mov $0, %eax
	jmp IRQWrapper
	
IRQ1:
	mov $1, %eax
	jmp IRQWrapper
	
IRQ2:
	mov $2, %eax
	jmp IRQWrapper
	
IRQ3:
	mov $3, %eax
	jmp IRQWrapper
	
IRQ4:
	mov $4, %eax
	jmp IRQWrapper
	
IRQ5:
	mov $5, %eax
	jmp IRQWrapper
	
IRQ6:
	mov $6, %eax
	jmp IRQWrapper
	
IRQ7:
	mov $7, %eax
	jmp IRQWrapper
	
IRQ8:
	mov $8, %eax
	jmp IRQWrapper
	
IRQ9:
	mov $9, %eax
	jmp IRQWrapper
	
IRQ10:
	mov $10, %eax
	jmp IRQWrapper
	
IRQ11:
	mov $11, %eax
	jmp IRQWrapper
	
IRQ12:
	mov $12, %eax
	jmp IRQWrapper
	
IRQ13:
	mov $13, %eax
	jmp IRQWrapper
	
IRQ14:
	mov $14, %eax
	jmp IRQWrapper
	
IRQ15:
	mov $15, %eax
	jmp IRQWrapper
