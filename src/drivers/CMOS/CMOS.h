/**
 * CMOS.h
 *
 * Created: Sep 12, 2017
 *
 * Author: Oskari
 */

#ifndef CMOS_H_
#define CMOS_H_

#include "Global.h"

//NMI disabled flag
const uint8_t NMI_DISABLED = 0;

/**
 * Floppy type descriptors
 * Stored in CMOS register 0x10
 * High nybble, master
 * Low nybble, slave
 */
const uint8_t NO_DRIVE   = 0x00;
const uint8_t _360KB525  = 0x01;    // 360KB 5.25 inch
const uint8_t _1200KB525 = 0x02;    // 1.2MB 5.25 inch
const uint8_t _720KB35   = 0x03;    // 720KB 3.5 inch
const uint8_t _1440KB35  = 0x04;    // 1.44MB 3.5 inch
const uint8_t _2880KB35  = 0x05;    // 2.88MB 3.5 inch

/**
 * Select a CMOS register
 * @param CMOS register
 */
inline void selectCMOS (uint8_t reg) {
    outb (0x70, (NMI_DISABLED << 7) | reg);
}
/**
 * Read from the CMOS register
 * @param register to read
 * @return result
 */
inline uint8_t readCMOS (uint8_t reg) {
    selectCMOS (reg);
    return inb (0x71);
}
/**
 * Write to the CMOS register
 * !!!NOT RECOMMENDED FOR USE!!!
 * @param register to write to
 * @param byte to write
 */
inline uint8_t writeCMOS (uint8_t reg, uint8_t val) {
    selectCMOS (reg);
    outb (0x71, val);
}

#endif
