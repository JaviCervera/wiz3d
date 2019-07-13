#include "memory.h"
#include <string.h>

EXPORT struct memory_t* CALL memory_new(int size)
{
  char* memory = (char*)calloc(1, size + 4);
  ((int*)memory)[0] = size;
  return (struct memory_t*)((int*)memory+1);
}

EXPORT void CALL memory_delete(struct memory_t* memory)
{
  free((int*)memory-1);
}

EXPORT int CALL memory_size(const struct memory_t* memory)
{
  return ((const int*)memory-1)[0];
}

EXPORT unsigned char CALL memory_byte(const struct memory_t* memory, int offset)
{
  unsigned char val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

EXPORT unsigned short CALL memory_short(const struct memory_t* memory, int offset)
{
  unsigned short val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

EXPORT int CALL memory_int(const struct memory_t* memory, int offset)
{
  int val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

EXPORT float CALL memory_float(const struct memory_t* memory, int offset)
{
  float val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

EXPORT double CALL memory_double(const struct memory_t* memory, int offset)
{
  double val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

EXPORT void CALL memory_setbyte(struct memory_t* memory, int offset, unsigned char val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

EXPORT void CALL memory_setshort(struct memory_t* memory, int offset, unsigned short val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

EXPORT void CALL memory_setint(struct memory_t* memory, int offset, int val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

EXPORT void CALL memory_setfloat(struct memory_t* memory, int offset, float val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

EXPORT void CALL memory_setdouble(struct memory_t* memory, int offset, double val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}
