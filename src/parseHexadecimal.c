#include "internal.h"

bool nap_parser__parseHexadecimal(const char *string, unsigned long *out) {
	return nap_parser_internal__parseIntegerString(string, out, true);
}
