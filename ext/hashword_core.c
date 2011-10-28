#include <stdint.h>
#include <ruby/ruby.h>

#define rot(x,k) (((x) << (k)) | ((x) >> (32 - (k))))

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

#ifndef RARRAY_PTR
# define RARRAY_PTR(a) RARRAY(a)->ptr
#endif

VALUE
rb_cObject_hashword(VALUE self, VALUE key, VALUE len, VALUE init) {
  VALUE *k = RARRAY_PTR(key);
  size_t length = (size_t) NUM2UINT(len);
  uint32_t initval = NUM2UINT(init);
  uint32_t a, b, c;

  a = b = c = 0xdeadbeef + (((uint32_t) length) << 2) + initval;

  while (length > 3) {
    a += NUM2UINT(k[0]);
    b += NUM2UINT(k[1]);
    c += NUM2UINT(k[2]);
    mix(a, b, c);
    length -= 3;
    k += 3;
  }

  switch (length) {
  case 3: c += NUM2UINT(k[2]);
  case 2: b += NUM2UINT(k[1]);
  case 1:
    a += NUM2UINT(k[0]);
    final(a, b, c);
    break;
  }

  return UINT2NUM(c);
}

void
Init_hashword_core(void) {
  rb_define_singleton_method(rb_cObject, "hashword", rb_cObject_hashword, 3);
}
