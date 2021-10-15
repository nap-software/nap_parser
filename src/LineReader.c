#include "internal.h"

nap_parser__LineReaderContext nap_parser__createLineReaderContext(
	const char *string, size_t line_size
) {
	nap_parser__LineReaderContext ctx;

	ctx.string = string;
	// cache length of input string
	ctx.string_length = strlen(string);
	// cast if C++ compiler is used
	ctx.line = (char *)malloc(line_size);
	ctx.line_size = line_size;
	ctx.offset = 0;

	return ctx;
}

static int _readNextCharacter(nap_parser__LineReaderContext *ctx) {
	// End of string check
	if (ctx->offset >= ctx->string_length) return -1;

	int ch = ctx->string[ctx->offset];
	ctx->offset++;

	return ch;
}

const char *nap_parser__readLine(nap_parser__LineReaderContext *ctx) {
	// malloc() has failed
	if (!ctx->line) return NULL;

	int ch, pos = 0;

	// ASCII characters are never negative
	while ((ch = _readNextCharacter(ctx)) != -1) {
		bool shouldWrite = (ctx->line_size > pos);

		if (ch == '\n') {
			// Terminate line
			if (shouldWrite) ctx->line[pos] = 0;
			++pos;
			break;
		}

		if (shouldWrite) ctx->line[pos] = ch;
		++pos;
	}

	// Nothing has been read
	if (pos == 0) return NULL;

	// Handle last line of string
	if (ctx->line_size > pos) {
		ctx->line[pos] = 0;
	}

	// Always terminate line
	ctx->line[ctx->line_size - 1] = 0;

	return ctx->line;
}

void nap_parser__destroyLineReaderContext(nap_parser__LineReaderContext ctx) {
	free(ctx.line);
}
