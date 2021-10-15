#include "test.h"

TESTS_BEGIN

TEST_CASE("It should work properly") {
	const char *input = "hello\nworld\n";
	nap_parser__LineReaderContext ctx;

	ctx = nap_parser__createLineReaderContext(input, 128);

	assert(
		strcmp(
			"hello",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(
		strcmp(
			"world",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(!nap_parser__readLine(&ctx));
	nap_parser__destroyLineReaderContext(ctx);
}

TEST_CASE("It should work with a string that does not end with a new line") {
	const char *input = "hello\nabc";
	nap_parser__LineReaderContext ctx;

	ctx = nap_parser__createLineReaderContext(input, 128);

	assert(
		strcmp(
			"hello",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(
		strcmp(
			"abc",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(!nap_parser__readLine(&ctx));
	nap_parser__destroyLineReaderContext(ctx);
}

TEST_CASE("It should truncate properly") {
	const char *input = "hello\nworld";
	nap_parser__LineReaderContext ctx;

	ctx = nap_parser__createLineReaderContext(input, 3);

	assert(
		strcmp(
			"he",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(
		strcmp(
			"wo",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(!nap_parser__readLine(&ctx));
	nap_parser__destroyLineReaderContext(ctx);
}

TEST_CASE("It should work with empty lines in between (bug #1)") {
	const char *input = "hello\n\n\nworld";
	nap_parser__LineReaderContext ctx;

	ctx = nap_parser__createLineReaderContext(input, 128);

	assert(
		strcmp(
			"hello",
			nap_parser__readLine(&ctx)
		) == 0
	);
	assert(!strlen(nap_parser__readLine(&ctx)));
	assert(!strlen(nap_parser__readLine(&ctx)));
	assert(
		strcmp(
			"world",
			nap_parser__readLine(&ctx)
		) == 0
	);

	assert(!nap_parser__readLine(&ctx));
	nap_parser__destroyLineReaderContext(ctx);
}

TESTS_END
