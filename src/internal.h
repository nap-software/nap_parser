#include "nap_parser.h"
#include <string.h> // strtok_r()

bool nap_parser_internal__parseIntegerString(const char *string, unsigned long *out, bool isHex);
size_t nap_parser_internal__countOccurrences(const char *string, char ch);
