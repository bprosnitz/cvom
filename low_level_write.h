#include<stdint.h>

#include "encbuf.h"

int write_uint(encbuf *buf, uint64_t uval);
int write_int(encbuf *buf, uint64_t ival);
int write_float(encbuf *buf, double fval);
int write_bool(encbuf *buf, uint8_t bool);
int write_bytes(encbuf *buf, uint8_t *in_bytes, uint64_t len);
