#include "encoder.h"

#include "low_level_write.h"

encoder* new_encoder() {
  encoder *e = (encoder*)malloc(sizeof(encoder));
  e->tid_stack = malloc(sizeof(uint64_t));
  e->num_tids = 1;
  e->buf = new_encbuf();
  return e;
}

void start(encoder *e, uint64_t tid) {
  e->tid_stack[0] = tid;
}
void finish(encoder *e) {

}
void start_any(encoder *e, uint64_t tid) {
  e->num_tids++;
  uint64_t* newstack = malloc(e->num_tids);
  memcpy(newstack, e->tid_stack, sizeof(uint64_t)*(e->num_tids-1));
  newstack[num_tids-1] = tid;
  e->tid_stack = newstack;
}
void finish_any(encoder *e) {
  e->num_tids--;
}

void from_bool(encoder *e, uint8_t bval) {
  write_bool(e->buf, bval);
}
void from_uint(encoder *e, uint64_t uval) {
  write_uint(e->buf, uval);
}
void from_int(encoder *e, int64_t ival) {
  write_int(e->buf, ival);
}
void from_float(encoder *e, double fval) {
  write_float(e->buf, fval);
}
void from_bytes(encoder *e, uint8_t *data, uint64_t len) {
  write_bytes(e->buf, data, len);
}
void from_string(encoder *e, uint8_t *data, uint64_t len) {
  write_bytes(e->buf, data, len);
}
void from_enum_label(encoder *e, uint64_t index) {
  write_uint(e->buf, index);
}

void start_list(encoder *e, uint64_t len) {
  write_uint(e->buf, len);
}
void finish_list(encoder *e) {
}
void start_set(encoder *e, uint64_t len) {
  write_uint(e->buf, len);
}
void finish_set(encoder *e) {}
void start_map(encoder *e, uint64_t) {
  write_uint(e->buf, len);
}
void finish_map(encoder *e) {}
void start_fields(encoder *e) {}
void finish_fields(encoder *e) {}

void start_elem(encoder *e, uint64_t index) {}
void finish_elem(encoder *e) {}

void start_key(encoder *e) {}
void finish_key(encoder *e) {}

void start_field(encoder *e, uint64_t field_index) {
  write_uint(e->buf, field_index);
}
void finish_key_start_field(encoder *e) {}
void finish_field(encoder *e) {}
