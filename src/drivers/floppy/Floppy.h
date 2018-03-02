/**
 * Floppy.h
 *
 * Created: Sept 11, 2017
 *
 * Author: Oskari
 */

#ifndef FLOPPY_H_
#define FLOPPY_H_

#include "../../Global.h"

/**
 * Struct that contains the Floppy types
 */
typedef struct {
    uint8_t master;
    uint8_t slave;
} fdtypes_t;

/**
 * Struct that contains a CHS address
 */
typedef struct {
    uint16_t cyl;
    uint16_t head;
    uint16_t sect;
} chs_t;

/**
 * The floppy registers:
 * Read/Write, Name
 * RO  Status register A
 * RO  Status register B
 *     Digital output regster
 *     Tape drive register
 * RO  Main status regiser
 * WO  Datarate select register
 *     Data FIFO
 * RO  Digital input register
 * WO  Configuration control register
 */
const uint16_t STATUS_REGISTER_A = 0x3F0;
const uint16_t STATUS_REGISTER_B = 0x3F1;
const uint16_t DIGITAL_OUTPUT_REGISTER = 0x3F2;
const uint16_t TAPE_DRIVE_REGISTER = 0x3F3;
const uint16_t MAIN_STATUS_REGISTER = 0x3F4;
const uint16_t DATARATE_SELECT_REGISTER = 0x3F4;
const uint16_t DATA_FIFO = 0x3F5;
const uint16_t DIGITAL_INPUT_REGISTER = 0x3F7;
const uint16_t CONFIGURATION_CONTROL_REGISTER = 0x3F7;

/**
 * Floppy commands
 */
const uint8_t READ_TRACK = 2;           //   Generates IRQ6
const uint8_t SPECIFY = 3;              // * Set drive parameters
const uint8_t SENSE_DRIVE_STATUS = 4;
const uint8_t WRITE_DATA = 5;           // * Write to disk
const uint8_t READ_DATA = 6;            // * Read from disk
const uint8_t RECALIBRATE = 7;          // * Seek to cylinder 0
const uint8_t SENSE_INTERRUPT = 8;      // * Ack IRQ6, get status of last cmd
const uint8_t WRITE_DELETED_DATA = 9;
const uint8_t READ_ID = 10;             //   Generates IRQ6
const uint8_t READ_DELETED_DATA = 12;
const uint8_t FORMAT_TRACK = 13;        // *
const uint8_t SEEK = 15;                // * Seek to cylinder X
const uint8_t VERSION = 16;             // * Used during init, once
const uint8_t SCAN_EQUAL = 17;
const uint8_t PERPENDICULAR_MODE = 18;  // * Used during init, once, maybe
const uint8_t CONFIGURE = 19;           // * Set controller parameters
const uint8_t LOCK = 20;                // * Protect parameterss from reset
const uint8_t VERIFY = 22
const uint8_t SCAN_LOW_OR_EQUAL = 25;
const uint8_t SCAN_HIGH_OR_EQUAL = 29;

/**
 * 1.44M floppy constants
 * 80 cylinders, 2 head (sides), 18 sectors per track
 */
const uint16_t SPT = 18;    // Sectors per track
const uint16_t HPC = 2;     // Heads per cylinder

/**
 * Converts CHS to LBA
 * @param cylinder number
 * @param head number
 * @param sector number
 * @return LBA format (logical base address)
 */
inline uint32_t CHSToLBA (uint16_t cyl, uint16_t head, uint16_t sect) {
    return (uint32_t) (((cyl * HPC + head) * SPT) + sect - 1);
}

/**
 * Converts LBA to CHS
 * @param logical base address
 * @return strut containing cyl, head, sect
 */
inline chs_t LBAToCHS (uint32_t lba) {
    return (chs_t) {
        .cyl = lba / (2 * SPT),
        .head = (lba % (2 * SPT)) / SPT,
        .sect = (lba % (2 * SPT)) % SPT + 1
    };
}

/**
 * Get the types of floppy drives
 * @return struct with the drive types
 */
fdtypes_t getDriveTypes ( );

/**
 * Set DMA channel 2 to transfer data from memory address 0x1000 to 0x23FF
 * Pagin must map this memory elsewhere and also never page to disk
 * The counter is 0x23FF which is the length of a track on 1.44M floppy - 1
 * (with 512 byte sectors)
 * Transfer length is counter + 1
 */
void initFloppyDMA ( );

/**
 * Prepare the drive for DMA read
 */
void prepareDMARead ( );

/**
 * Prepare the drive for DMA write
 */
void prepareDMAWrite ( );

#endif
