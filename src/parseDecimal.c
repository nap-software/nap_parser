#include "internal.h"

bool nap_parser__parseDecimal(const char *string, unsigned long *out) {
	return nap_parser_internal__parseIntegerString(string, out, false);
}
