#include "internal.h"
#include <string.h>

bool nap_parser__parseMACAddress(const char *string, uint8_t *out) {
	// Check occurrences of :
	if (nap_parser_internal__countOccurrences(string, ':') != 5) {
		return false;
	}

	// Max-length of a valid MAC-Address is 17:
	// strlen("ff:ff:ff:ff:ff:ff") == 17
	if (strlen(string) > 32) return false;

	char copy[32];
	strncpy(copy, string, sizeof(copy));
	copy[31] = 0;

	char *saveptr;
	char *octet = strtok_r(copy, ":", &saveptr);
	int i = 0;

	while (octet) {
		// Octet is too long (max. 2 characters)
		if (strlen(octet) > 2) {
			return false;
		}

		// Parse octet
		unsigned long value;

		if (!nap_parser_internal__parseIntegerString(octet, &value, true)) {
			return false;
		}

		if (out) {
			out[i] = value;
			++i;
		}

		octet = strtok_r(NULL, ":", &saveptr);
	}

	return true;
}
