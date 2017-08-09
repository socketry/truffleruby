#include "ruby.h"
#include "rubyspec.h"

#include <string.h>
#include <stdarg.h>

#ifdef HAVE_RB_ST
#include <ruby/st.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_RB_ST
VALUE st_spec_st_init_numtable(VALUE self) {
  st_table *tbl = st_init_numtable();
  int entries = tbl->num_entries;
  st_free_table(tbl);
  return INT2FIX(entries);
}

VALUE st_spec_st_init_numtable_with_size(VALUE self) {
  st_table *tbl = st_init_numtable_with_size(128);
  int entries = tbl->num_entries;
  st_free_table(tbl);
  return INT2FIX(entries);
}

VALUE st_spec_st_insert(VALUE self) {
  st_table *tbl = st_init_numtable_with_size(128);
  st_insert(tbl, 1, 1);
  int entries = tbl->num_entries;
  st_free_table(tbl);
  return INT2FIX(entries);
}

static int sum(st_data_t key, st_data_t value, st_data_t arg) {
  *(int*)arg += value;
  return ST_CONTINUE;
}

VALUE st_spec_st_foreach(VALUE self) {
  st_table *tbl = st_init_numtable_with_size(128);
  st_insert(tbl, 1, 3);
  st_insert(tbl, 2, 4);
  int total = 0;
  st_foreach(tbl, sum, (st_data_t)&total);
  st_free_table(tbl);
  return INT2FIX(total);
}

VALUE st_spec_st_lookup(VALUE self) {
  st_table *tbl = st_init_numtable_with_size(128);
  st_insert(tbl, 7, 42);
  st_insert(tbl, 2, 4);
  st_data_t result = (st_data_t)0;
  st_lookup(tbl, (st_data_t)7, &result);
  st_free_table(tbl);
  return INT2FIX(result);
}

#endif

void Init_st_spec(void) {
  VALUE cls;
  cls = rb_define_class("CApiStSpecs", rb_cObject);

#ifdef HAVE_RB_ST
  rb_define_method(cls, "st_init_numtable", st_spec_st_init_numtable, 0);
  rb_define_method(cls, "st_init_numtable_with_size", st_spec_st_init_numtable_with_size, 0);
  rb_define_method(cls, "st_insert", st_spec_st_insert, 0);
  rb_define_method(cls, "st_foreach", st_spec_st_foreach, 0);
  rb_define_method(cls, "st_lookup", st_spec_st_lookup, 0);
#endif

}

#ifdef __cplusplus
}
#endif