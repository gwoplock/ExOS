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
