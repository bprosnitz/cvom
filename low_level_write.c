#include "low_level_write.h"

#include <string.h>

static inline uint64_t int_to_uint(int64_t ival) {
	if (ival < 0) {
		return (uint64_t)(((~ival) << 1) | 1);
	} else {
		return (uint64_t)(ival << 1);
	}
}

static inline uint64_t reverse_byte_order(uint64_t uval) {
	return (uval&0xff)<<56 |
 	(uval&0xff00)<<40 |
	(uval&0xff0000)<<24 |
	(uval&0xff000000)<<8 |
    	(uval&0xff00000000)>>8 |
	(uval&0xff0000000000)>>24 |
	(uval&0xff000000000000)>>40 |
	(uval&0xff00000000000000)>>56;
}

// PRECONDITION: At least 9 bytes must be available in buf.
// OUTPUT: Number of bytes written.
int write_uint(encbuf *buf, uint64_t uval) {
	if (uval <= 0x7f) {
		encbuf_write_one_byte(buf, (uint8_t)uval);
		return 1;
	} else {
		// TODO(bprosnitz) Consider using bit-twiddling to skip the
		// branches when counting bytes.
		uint8_t count;
		if (uval <= 0xff) {
			count = 1;
		} else if (uval <= 0xffff) {
			count = 2;
		} else if (uval <= 0xffffff) {
			count = 3;
		} else if (uval <= 0xffffffff) {
			count = 4;
		} else if (uval <= 0xffffffffff) {
			count = 5;
		} else if (uval <= 0xffffffffffff) {
			count = 6;
		} else if (uval <= 0xffffffffffffff) {
			count = 7;
		} else if (uval <= 0xffffffffffffffff) {
			count = 8;
		}
		uint8_t *data = encbuf_grow(buf, count+1);
		*data = 0xff - count;
		*((uint64_t*)(data+1)) = uval;
		return count + 1;
	}
}

int write_int(encbuf *buf, int64_t ival) {
	return write_uint(buf, int_to_uint(ival));
}

int write_float(encbuf *buf, double fval) {
	uint64_t uval = *(uint64_t*)(&fval);
	return write_uint(buf, reverse_byte_order(uval));
}

int write_bool(encbuf *buf, uint8_t bool) {
	return write_uint(buf, bool);
}

int write_bytes(encbuf *buf, uint8_t *in_bytes, uint64_t len) {
	int len_byte_count = write_uint(buf, len);
	encbuf_write(buf, in_bytes, len);
	return len_byte_count + (int)len;
}
