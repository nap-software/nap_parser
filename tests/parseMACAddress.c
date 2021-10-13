#include "test.h"

TESTS_BEGIN

TEST_CASE("It should work properly") {
	uint8_t out[6];

	assert(nap_parser__parseMACAddress("11:22:33:44:55:66", out));
	assert(out[0] == 0x11);
	assert(out[1] == 0x22);
	assert(out[2] == 0x33);
	assert(out[3] == 0x44);
	assert(out[4] == 0x55);
	assert(out[5] == 0x66);
}

TEST_CASE("It should work without output") {
	assert(nap_parser__parseMACAddress("11:22:33:44:55:66", NULL));
}

TEST_CASE("It should return false for invalid formatted addresses") {
	// 1 octet missing
	assert(!nap_parser__parseMACAddress("11:22:33:44:55", NULL));
	// All octets present, but one is too long
	assert(!nap_parser__parseMACAddress("11:22:33:44:555:66", NULL));
	// Too many octets
	assert(!nap_parser__parseMACAddress("11:22:33:44:55:66:77", NULL));
	// Invalid format 1
	assert(!nap_parser__parseMACAddress("11:22:33:44:55:66:", NULL));
	// Invalid characters inside octet
	assert(!nap_parser__parseMACAddress("11:22:33:4u:55:66", NULL));
}

TESTS_END
