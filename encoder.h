#ifndef ENCODER_H
#define ENCODER_H

#include "encbuf.h"

typedef struct {
  uint64_t* tid_stack;
  uint64_t num_tids;
  encbuf *buf;
} encoder;

encoder* new_encoder();

void start(encoder *e, uint64_t tid);
void finish(encoder *e);
void start_any(encoder *e, uint64_t tid);
void finish_any(encoder *e);

void from_bool(encoder *e, uint8_t bval);
void from_uint(encoder *e, uint64_t uval);
void from_int(encoder *e, int64_t ival);
void from_float(encoder *e, double fval);
void from_bytes(encoder *e, uint8_t *data, uint64_t len);
void from_string(encoder *e, uint8_t *data, uint64_t len);
void from_enum_label(encoder *e, uint64_t index);

void start_list(encoder *e, uint64_t len);
void finish_list(encoder *e);
void start_set(encoder *e, uint64_t len);
void finish_set(encoder *e);
void start_map(encoder *e, uint64_t);
void finish_map(encoder *e);
void start_fields(encoder *e);
void finish_fields(encoder *e);

void start_elem(encoder *e, uint64_t index);
void finish_elem(encoder *e);

void start_key(encoder *e);
void finish_key(encoder *e);

void start_field(encoder *e, uint64_t field_index);
void finish_key_start_field(encoder *e);
void finish_field(encoder *e);

#endif 
