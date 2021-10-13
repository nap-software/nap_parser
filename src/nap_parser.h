#if !defined(NAP_PARSER_h)
	#define NAP_PARSER_h

	#include <stdbool.h> // bool
	#include <stdint.h> // uint8_t
	#include <stdlib.h> // size_t

	bool nap_parser__parseDecimal(const char *string, unsigned long *out);
	bool nap_parser__parseHexadecimal(const char *string, unsigned long *out);
	bool nap_parser__parseMACAddress(const char *string, uint8_t *out);
	bool nap_parser__parseIPv4Address(const char *string, uint8_t *out);
	bool nap_parser__parseKeyValue(const char *string, char *key, size_t key_len, char *value, size_t value_len);

	typedef struct {
		// Reference to input string
		const char *string;
		// Length of string (cached)
		size_t string_length;
		// Max line size
		size_t line_size;
		// Current offset
		size_t offset;
		// Current line (allocated on the heap)
		char *line;
	} nap_parser__LineReaderContext;

	nap_parser__LineReaderContext nap_parser__createLineReaderContext(
		const char *string, size_t line_size
	);
	const char *nap_parser__readLine(nap_parser__LineReaderContext *ctx);
	void nap_parser__destroyLineReaderContext(nap_parser__LineReaderContext ctx);
#endif
