#include "internal.h"

size_t nap_parser_internal__countOccurrences(const char *string, char ch) {
	size_t num = 0;

	for (size_t i = 0, len = strlen(string); i < len; ++i) {
		if (string[i] == ch) ++num;
	}

	return num;
}
