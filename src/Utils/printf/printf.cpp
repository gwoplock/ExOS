/* stdarg.h is for variadics */
#include <stdarg.h>
#include "../../drivers/Console.h"
#include "../printf/printf.h"
/**
 * A very ugly printf. Must be fixed in the future.
 * @param format string
 * @param arguments to the format (will be converted live)
 */
void printf (const char *format, ...) {
    char in_format = 0;
    va_list args;

    va_start(args, format);

    /* Loop through the format string */
    while (*format) {
        /* Test for the delimiter */
        if (!in_format && *format == '%') {
            in_format = 1;
        } else if (in_format && *format != 0) {
            switch (*format) {
                case 'd':
                    writeInt(va_arg(args, uint32_t));
                    in_format = 0;
                    break;
                case 'c':
                    terminalPutChar(va_arg(args, uint32_t));
                    in_format = 0;
                    break;
                default:
                    in_format = 0;
                    break;
            }
        } else {
            terminalPutChar(*format);
        }

        format++;
    }

    va_end(args);
}
