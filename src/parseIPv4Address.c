#include "internal.h"
#include <string.h>

bool nap_parser__parseIPv4Address(const char *string, uint8_t *out) {
	// Check occurrences of .
	if (nap_parser_internal__countOccurrences(string, '.') != 3) {
		return false;
	}

	// Max-length of a valid IPv4-Address is 15:
	// strlen("255.255.255.255") == 15
	if (strlen(string) > 32) return false;

	char copy[32];
	strncpy(copy, string, sizeof(copy));
	copy[31] = 0;

	char *saveptr;
	char *octet = strtok_r(copy, ".", &saveptr);
	int i = 0;

	while (octet) {
		// Octet is too long (max. 3 characters)
		if (strlen(octet) > 3) {
			return false;
		}

		// Parse octet
		unsigned long value;

		if (!nap_parser_internal__parseIntegerString(octet, &value, false)) {
			return false;
		}

		// Out of range
		if (value > 255) return false;

		if (out) {
			out[i] = value;
			++i;
		}

		octet = strtok_r(NULL, ".", &saveptr);
	}

	return true;
}
