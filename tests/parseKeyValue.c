#include "test.h"
#include <string.h>

TESTS_BEGIN

TEST_CASE("It should work properly") {
	char key[32]; char value[32];

	assert(nap_parser__parseKeyValue("abc,def", key, 32, value, 32));
	assert(strcmp(key, "abc") == 0);
	assert(strcmp(value, "def") == 0);
}

TEST_CASE("It should truncate values properly") {
	char key[4]; char value[4];

	assert(nap_parser__parseKeyValue("hello,world", key, 4, value, 4));
	assert(strcmp(key, "hel") == 0);
	assert(strcmp(value, "wor") == 0);
}

TEST_CASE("It should work without output") {
	//assert(nap_parser__parseKeyValue("abc,def", NULL, 0, NULL, 0));
}

TEST_CASE("It should work with multiple commas") {
	char key[32]; char value[32];

	assert(nap_parser__parseKeyValue("abc,def,123", key, 32, value, 32));
	assert(strcmp(key, "abc") == 0);
	assert(strcmp(value, "def,123") == 0);
}

TEST_CASE("It should return false for invalid formatted strings") {
	// empty string
	assert(!nap_parser__parseKeyValue("", NULL, 0, NULL, 0));
	// no comma separator
	assert(!nap_parser__parseKeyValue("abc", NULL, 0, NULL, 0));
}

TESTS_END
