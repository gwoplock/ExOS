/**
 * Floppy.cpp
 *
 * Created: Sept 12, 2017
 *
 * Author: Oskari
 */

#include "drivers/CMOS/CMOS.h"
#include "drivers/floppy/Floppy.h"

/**
 * Get the types of floppy drives
 * @return struct with the drive types
 */
fdtypes_t getDriveTypes ( ) {
    uint8_t drives = readCMOS (0x10);
    return (fdtypes_t) {
        .master = (drives >> 4) & 0x0F,
        .slave = drives & 0x0F
    };
}

/**
 * Set DMA channel 2 to transfer data from memory address 0x1000 to 0x23FF
 * Pagin must map this memory elsewhere and also never page to disk
 * The counter is 0x23FF which is the length of a track on 1.44M floppy - 1
 * (with 512 byte sectors)
 * Transfer length is counter + 1
 */
void initFloppyDMA ( ) {
    outb (0x0A, 0x06);  // Mask DMA channels 2 and 0
                        // The following is out of order to avoid extra delays
                        // from outb'ing the same port twice in a row
    outb (0x0C, 0xFF);  // Reset master flip flop
    outb (0x04, 0x00);  // Set address low byte to 0
    outb (0x05, 0x23);  // Set counter high byte to 0x23
    outb (0x04, 0x10);  // Set address high byte to 0x10
    outb (0x05, 0xFF);  // Set counter low byte to 0xFF
    outb (0x81, 0x00);  // Set external page register to 0
    outb (0x0A, 0x02);  // Unmask channel 2
}

/**
 * TODO:
 * TEST:
 *  demand transfer if "advanced drive" detected
 *  read the end of the ISA DMA article for for more info
 */

/**
 * Prepare the drive for DMA read
 */
void prepareDMARead ( ) {
    outb (0x0A, 0x06);  // Mask DMA channels 2 and 0
    outb (0x0B, 0x56);  // 01 0 1 01 10
                        // single transfer, address inc, autoinit, read, ch2
    outb (0x0A, 0x02);  // Unmask channel 2
}

/**
 * Prepare the drive for DMA write
 */
void prepareDMAWrite ( ) {
    outb (0x0A, 0x06);  // Mask DMA channels 2 and 0
    outb (0x0B, 0x5A);  // 01 0 1 10 10
                        // single transfer, address inc, autoinit, write, ch2
    outb (0x0A, 0x02);  // Unmask channel 2
}
