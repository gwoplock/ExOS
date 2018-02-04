#include "StrLen.h"

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
/**
 * Get string length
 * @param string
 * @return length
 */
size_t strlen(const char* str) {
	size_t _length = 0;
	while (str[_length])
		_length++;
	return _length;
}
#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif