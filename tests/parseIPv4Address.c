#include "test.h"

TESTS_BEGIN

TEST_CASE("It should work properly") {
	uint8_t out[4];

	assert(nap_parser__parseIPv4Address("123.25.54.3", out));
	assert(out[0] == 123);
	assert(out[1] == 25);
	assert(out[2] == 54);
	assert(out[3] == 3);
}

TEST_CASE("It should work without output") {
	assert(nap_parser__parseIPv4Address("123.25.54.3", NULL));
}

TEST_CASE("It should return false for invalid formatted addresses") {
	// 1 octet missing
	assert(!nap_parser__parseIPv4Address("1.2.3", NULL));
	// All octets present, but one is too long
	assert(!nap_parser__parseIPv4Address("1.4232.2.3", NULL));
	// All octets present, but one is too high
	assert(!nap_parser__parseIPv4Address("1.432.2.3", NULL));
	// Too many octets
	assert(!nap_parser__parseIPv4Address("1.2.3.4.5", NULL));
	// Invalid format 1
	assert(!nap_parser__parseIPv4Address("1.2.3.4.5.", NULL));
	// Invalid characters inside octet
	assert(!nap_parser__parseIPv4Address("1.2.3a.4", NULL));
}

TESTS_END
