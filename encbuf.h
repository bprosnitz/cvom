
typedef struct {
	uint8_t* beg; // beginning of allocated block
	uint8_t* cur; // current position
	uint64_t alloc_len; // length allocated
} encbuf;

encbuf * new_encbuf();

uint8_t* encbuf_grow(encbuf *buf, uint64_t n);
void encbuf_write_one_byte(encbuf *buf, uint8_t c);
void encbuf_write(encbuf *buf, uint8_t *in_bytes, uint64_t len);
