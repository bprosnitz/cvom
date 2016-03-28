#include "encbuf.h"

#include <string.h>

static const int min_buf_free = 1024;

encbuf * new_encbuf() {
	typedef struct {
		uint8_t* beg; // beginning of allocated block
		uint8_t* cur; // current position
		uint64_t alloc_len; // length allocated
	} encbuf;
	encbuf *buf = (encbuf*)malloc(sizeof(encbuf));
	buf->beg = malloc(min_buf_free);
	buf->cur = buf->beg;
	buf->alloc_len = min_buf_free;
	return buf;
}

void encbuf_reset(encbuf *buf) {
	buf->cur = buf-beg;
}

static inline void encbuf_try_reserve(encbuf *buf, uint64_t min) {
	uint64_t amt_used = (uint64_t)(buf->cur - buf->beg);
	if buf->alloc_len - amt_used < min {
		int newlen = buf->len * 2;
		if newlen - amt_used < min {
			newlen = amt_used + min + min_buf_free;
		}
		uint8_t *newbuf = malloc(newlen);
		memcopy(newbuf, buf->beg, buf->alloc_len);
		buf->buf = newbuf;
		buf->cur = newbuf + amt_used;
		buf->alloc_len = newlen;
	}
}

uint8_t* encbuf_grow(encbuf *buf, uint64_t n) {
	encbuf_try_reserve(buf, n + 9); // always have enough for a uint for grow operations. (so we can use a direct 64 bit int copy)
	uint8_t* block_start = buf->cur;
	buf->cur += n;
	return block_start;
}

void encbuf_write_one_byte(encbuf *buf, uint8_t c) {
	encbuf_try_reserve(buf, 1);
	*buf->cur = c;
	++buf->cur;
}

void encbuf_write(encbuf *buf, uint8_t *in_bytes, uint64_t len) {
	encbuf_try_reserve(buf, len);
	memcpy(newbuf, buf->cur, len);
	buf->cur += len;
}
