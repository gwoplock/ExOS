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
 * Struct that contains a CHS address
 */
typedef struct {
    uint16_t cyl;
    uint16_t head;
    uint16_t sect;
} chs_t;

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

#endif
