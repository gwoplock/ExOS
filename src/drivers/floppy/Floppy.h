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
 * OR the values together for a DOR command
 * DOR format:
 *  Bits 0-1:
 *      00 - Drive 0
 *      01 - Drive 1
 *      10 - Drive 2
 *      11 - Drive 3
 *  Bit 2:
 *      0 - Reset controller
 *      1 - Controller enabled
 *  Bit 3:
 *      0 - IRQ channel
 *      1 - DMA mode
 *  Bits 4-7 (bit 4, drive 0 -> bit 7, drive 3):
 *      0 - Stop motor
 *      1 - Start motor
 */
const uint8_t DOR_DRIVE0 = 0x00;    // 0000 00|00|
const uint8_t DOR_DRIVE1 = 0x01;    // 0000 00|01|
const uint8_t DOR_DRIVE2 = 0x02;    // 0000 00|10|
const uint8_t DOR_DRIVE3 = 0x03;    // 0000 00|11|
const uint8_t DOR_ENABLE = 0x04;    // 0000 0|1|00
const uint8_t DOR_DMA    = 0x08;    // 0000 |1|000
const uint8_t DOR_MOTOR0 = 0x10;    // 000|1| 0000
const uint8_t DOR_MOTOR1 = 0x20;    // 00|1|0 0000
const uint8_t DOR_MOTOR2 = 0x40;    // 0|1|00 0000
const uint8_t DOR_MOTOR3 = 0x80;    // |1|000 0000

/**
 * MSR format:
 *  Bit 0 Drive0
 *  Bit 1 Drive1
 *  Bit 2 Drive2
 *  Bit 3 Drive3:
 *      0 - Not busy in seek mode
 *      1 - Busy
 *  Bit 4:
 *      0 - FDC not busy
 *      1 - FDC busy with read/write
 *  Bit 5:
 *      0 - FDC in DMA mode
 *      1 - FDC in non-DMA mode
 *  Bit 6 (direction of transfer):
 *      0 - Expecting data from CPU
 *      1 - Has data for CPU
 *  Bit 7:
 *      0 - Data register not ready for transfer
 *      1 - Data register ready
 */
const uint8_t MSR_DRIVE0_SEEK = 0x01;   // 0000 000|1|
const uint8_t MSR_DRIVE1_SEEK = 0x02;   // 0000 00|1|0
const uint8_t MSR_DRIVE2_SEEK = 0x04;   // 0000 0|1|00
const uint8_t MSR_DRIVE3_SEEK = 0x08;   // 0000 |1|000
const uint8_8 MSR_FDC_BUSY    = 0x10;   // 000|1| 0000
const uint8_t MSR_FDC_DMA     = 0x20;   // 00|1|0 0000
const uint8_t MSR_DIRECTION   = 0x40;   // 0|1|00 0000
const uint8_t MSR_DATA_READY  = 0x80;   // |1|000 0000

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
