# nap_parser

This library provides means to parse various user inputs.

- Positive Integers in decimal and hexadecimal format
- MAC-Address
- IPv4-Address
- Key,Value pairs
- Lines 

## Simple parsing functions

The simple parsing functions all return a `bool` indicating success or failure of the parsing.

All simple parsing functions put the output to the location provided by the caller. (see `out` parameter in each function declaration)

If only validation is needed, `NULL` can be safely passed instead of an actual memory location.

### `bool nap_parser__parseDecimal(const char *string, unsigned long *out)`

Parses a positive decimal integer string.

**Notice**

⚠️  Negative integer strings are **not** supported.


---

### `bool nap_parser__parseHexadecimal(const char *string, unsigned long *out)`

Parses a positive hexadecimal integer string.

**Notice**

⚠️  Negative integer strings are **not** supported.

---

### `bool nap_parser__parseMACAddress(const char *string, uint8_t *out)`

Parses a MAC-Address in the format of `xx:xx:xx:xx:xx:xx`.

**Notice**

⚠️  `out`, if specified, must have space for `6` elements of `uint8_t`.

---

### `bool nap_parser__parseIPv4Address(const char *string, uint8_t *out)`

Parses an IPv4-Address in the format of `xxx.xxx.xxx.xxx`.

**Notice**

⚠️  `out`, if specified, must have space for `4` elements of `uint8_t`.

---

### `bool nap_parser__parseKeyValue(const char *string, char *key, size_t key_len, char *value, size_t value_len)`

Parses a key-value pair in the format of `key,value`.

- `char *key` pointer to a memory location than can hold up to `key_len` bytes.
- `char *value` pointer to a memory location than can hold up to `value_len` bytes.

**Notice**

⚠️  A `key_len` of, for example, `12` means the key can be `11` characters long at maximum.

⚠️  A `value_len` of, for example, `12` means the value can be `11` characters long at maximum.

⚠️ Thus `key_len` and `value_len` (if `key` resp. `value` is not `NULL`) must be at least `2`.

## LineReader

To read a string line by line a `struct` context is needed:

```c
typedef struct {
	const char *string;
	size_t string_length;
	size_t line_size;
	size_t offset;
	char *line;
} nap_parser__LineReaderContext;
```

A context can be created with `nap_parser__createLineReaderContext`.

### `nap_parser__LineReaderContext nap_parser__createLineReaderContext(const char *string, size_t line_size)`

Creates a new line parser context. 

---

### `const char *nap_parser__readLine(nap_parser__LineReaderContext ctx)`

Reads a line from the context input string.

Returns `NULL` if no more lines are left to read.

**Notice**

⚠️  Do not `free()` the returned line pointer. 

⚠️  If you want to use the line later in the program (after the context is destroyed) then you'll have to **copy** the line with something like `strdup()`.

⚠️  Subsequent calls overwrite the internal line reference.

---

### `void nap_parser__destroyLineReaderContext(nap_parser__LineReaderContext ctx)`

Destroys resp. frees the associated heap memory used in the context.

Call this function once you're done reading / processing the lines.

---

### Example 

```c
// This is the string we want to read lines from
const char *string = "Hello\nWorld";
// This variable holds the current line
const char *line;

nap_parser__LineReaderContext ctx = nap_parser__createLineParserContext(string, 128);

while ((line = nap_parser__readLine(ctx)) {
	// Do something with `line`
	printf("Read line: %s\n", line);
}

// Destroy the context
nap_parser__destroyLineReaderContext(ctx);
```

# Testing

To test this library, `valgrind` and the `gcc` compiler are needed.

Run tests with `./test.sh` with the **WORKING DIRECTORY** being the project root.
