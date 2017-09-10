/*
 * InterruptDescriptorTable.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "InterruptDescriptorTable.h"

//TODO comment what each interrupt is
InterruptDescriptorTable::InterruptDescriptorTable( ) {
	//encode each interrupt used with the proper function location and type
	_idt[0] = encode((uint32_t) (unsigned) &ISR0, (uint16_t) 0x08);
	_idt[1] = encode((uint32_t) (unsigned) &ISR1, (uint16_t) 0x08);
	_idt[2] = encode((uint32_t) (unsigned) &ISR2, (uint16_t) 0x08);
	_idt[3] = encode((uint32_t) (unsigned) &ISR3, (uint16_t) 0x08);
	_idt[4] = encode((uint32_t) (unsigned) &ISR4, (uint16_t) 0x08);
	_idt[5] = encode((uint32_t) (unsigned) &ISR5, (uint16_t) 0x08);
	_idt[6] = encode((uint32_t) (unsigned) &ISR6, (uint16_t) 0x08);
	_idt[7] = encode((uint32_t) (unsigned) &ISR7, (uint16_t) 0x08);
	_idt[8] = encode((uint32_t) (unsigned) &ISR8, (uint16_t) 0x08);
	_idt[9] = encode((uint32_t) (unsigned) &ISR9, (uint16_t) 0x08);
	_idt[10] = encode((uint32_t) (unsigned) &ISR10, (uint16_t) 0x08);
	_idt[11] = encode((uint32_t) (unsigned) &ISR11, (uint16_t) 0x08);
	_idt[12] = encode((uint32_t) (unsigned) &ISR12, (uint16_t) 0x08);
	_idt[13] = encode((uint32_t) (unsigned) &ISR13, (uint16_t) 0x08);
	_idt[14] = encode((uint32_t) (unsigned) &ISR14, (uint16_t) 0x08);
	_idt[15] = encode((uint32_t) (unsigned) &ISR15, (uint16_t) 0x08);
	_idt[16] = encode((uint32_t) (unsigned) &ISR16, (uint16_t) 0x08);
	_idt[17] = encode((uint32_t) (unsigned) &ISR17, (uint16_t) 0x08);
	_idt[18] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[19] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[20] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[21] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[22] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[23] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[24] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[25] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[26] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[27] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[28] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[29] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[30] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[31] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[32] = encode((uint32_t) (unsigned) &IRQ0, (uint16_t) 0x08);
	_idt[33] = encode((uint32_t) (unsigned) &IRQ1, (uint16_t) 0x08);
	_idt[34] = encode((uint32_t) (unsigned) &IRQ2, (uint16_t) 0x08);
	_idt[35] = encode((uint32_t) (unsigned) &IRQ3, (uint16_t) 0x08);
	_idt[36] = encode((uint32_t) (unsigned) &IRQ4, (uint16_t) 0x08);
	_idt[37] = encode((uint32_t) (unsigned) &IRQ5, (uint16_t) 0x08);
	_idt[38] = encode((uint32_t) (unsigned) &IRQ6, (uint16_t) 0x08);
	_idt[39] = encode((uint32_t) (unsigned) &IRQ7, (uint16_t) 0x08);
	_idt[40] = encode((uint32_t) (unsigned) &IRQ8, (uint16_t) 0x08);
	_idt[41] = encode((uint32_t) (unsigned) &IRQ9, (uint16_t) 0x08);
	_idt[42] = encode((uint32_t) (unsigned) &IRQ10, (uint16_t) 0x08);
	_idt[43] = encode((uint32_t) (unsigned) &IRQ11, (uint16_t) 0x08);
	_idt[44] = encode((uint32_t) (unsigned) &IRQ12, (uint16_t) 0x08);
	_idt[45] = encode((uint32_t) (unsigned) &IRQ13, (uint16_t) 0x08);
	_idt[46] = encode((uint32_t) (unsigned) &IRQ14, (uint16_t) 0x08);
	_idt[47] = encode((uint32_t) (unsigned) &IRQ15, (uint16_t) 0x08);
	size = 225;
}
/**
 *
 * @param really a funct pointer to the **ASM** interrupt handleer
 * @param selector that the code should run in
 * @return encoded entry for the IDT
 */
IdtEntry InterruptDescriptorTable::encode(uint32_t offset, uint16_t selector) {
	//make our selfs something to put this shit in
	IdtEntry toReturn;
	//probably not necissary but one can never be too careful
	toReturn.zero = 0;
	//get the upper 1/2 of the offset
	toReturn.offset1 = offset & 0x0000FFFF;
	//what segment this should run in. (bullshit)
	toReturn.selector = selector;
	//how selector should be done
	/*toReturn.type_attr = (1 << 7);
	 toReturn.type_attr |= (dpl << 6);
	 toReturn.type_attr |= (s << 4);
	 toReturn.type_attr |= type;*/
	//what type of gate we are dealing with. (more bullshit, if im loading it with LIDT it should know its an idt)
	toReturn.typeAttr = 0x8E;
	//other bit of the offset
	toReturn.offset2 = (offset & 0xFFFF0000) >> 16;
	//send it back
	return toReturn;
}
//TODO comment what each interrupt is
void InterruptDescriptorTable::build( ) {
	//encode each interrupt used with the proper function location and type
	_idt[0] = encode((uint32_t) (unsigned) &ISR0, (uint16_t) 0x08);
	_idt[1] = encode((uint32_t) (unsigned) &ISR1, (uint16_t) 0x08);
	_idt[2] = encode((uint32_t) (unsigned) &ISR2, (uint16_t) 0x08);
	_idt[3] = encode((uint32_t) (unsigned) &ISR3, (uint16_t) 0x08);
	_idt[4] = encode((uint32_t) (unsigned) &ISR4, (uint16_t) 0x08);
	_idt[5] = encode((uint32_t) (unsigned) &ISR5, (uint16_t) 0x08);
	_idt[6] = encode((uint32_t) (unsigned) &ISR6, (uint16_t) 0x08);
	_idt[7] = encode((uint32_t) (unsigned) &ISR7, (uint16_t) 0x08);
	_idt[8] = encode((uint32_t) (unsigned) &ISR8, (uint16_t) 0x08);
	_idt[9] = encode((uint32_t) (unsigned) &ISR9, (uint16_t) 0x08);
	_idt[10] = encode((uint32_t) (unsigned) &ISR10, (uint16_t) 0x08);
	_idt[11] = encode((uint32_t) (unsigned) &ISR11, (uint16_t) 0x08);
	_idt[12] = encode((uint32_t) (unsigned) &ISR12, (uint16_t) 0x08);
	_idt[13] = encode((uint32_t) (unsigned) &ISR13, (uint16_t) 0x08);
	_idt[14] = encode((uint32_t) (unsigned) &ISR14, (uint16_t) 0x08);
	_idt[15] = encode((uint32_t) (unsigned) &ISR15, (uint16_t) 0x08);
	_idt[16] = encode((uint32_t) (unsigned) &ISR16, (uint16_t) 0x08);
	_idt[17] = encode((uint32_t) (unsigned) &ISR17, (uint16_t) 0x08);
	_idt[18] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[19] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[20] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[21] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[22] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[23] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[24] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[25] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[26] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[27] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[28] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[29] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[30] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[31] = encode((uint32_t) (unsigned) &ISR18, (uint16_t) 0x08);
	_idt[32] = encode((uint32_t) (unsigned) &IRQ0, (uint16_t) 0x08);
	_idt[33] = encode((uint32_t) (unsigned) &IRQ1, (uint16_t) 0x08);
	_idt[34] = encode((uint32_t) (unsigned) &IRQ2, (uint16_t) 0x08);
	_idt[35] = encode((uint32_t) (unsigned) &IRQ3, (uint16_t) 0x08);
	_idt[36] = encode((uint32_t) (unsigned) &IRQ4, (uint16_t) 0x08);
	_idt[37] = encode((uint32_t) (unsigned) &IRQ5, (uint16_t) 0x08);
	_idt[38] = encode((uint32_t) (unsigned) &IRQ6, (uint16_t) 0x08);
	_idt[39] = encode((uint32_t) (unsigned) &IRQ7, (uint16_t) 0x08);
	_idt[40] = encode((uint32_t) (unsigned) &IRQ8, (uint16_t) 0x08);
	_idt[41] = encode((uint32_t) (unsigned) &IRQ9, (uint16_t) 0x08);
	_idt[42] = encode((uint32_t) (unsigned) &IRQ10, (uint16_t) 0x08);
	_idt[43] = encode((uint32_t) (unsigned) &IRQ11, (uint16_t) 0x08);
	_idt[44] = encode((uint32_t) (unsigned) &IRQ12, (uint16_t) 0x08);
	_idt[45] = encode((uint32_t) (unsigned) &IRQ13, (uint16_t) 0x08);
	_idt[46] = encode((uint32_t) (unsigned) &IRQ14, (uint16_t) 0x08);
	_idt[47] = encode((uint32_t) (unsigned) &IRQ15, (uint16_t) 0x08);
	size = 48;
}

