#include "test.h"

TESTS_BEGIN

TEST_CASE("It should work properly") {
	assert(
		strcmp(
			"0.0.1",
			nap_parser__version()
		) == 0
	);
}

TESTS_END
