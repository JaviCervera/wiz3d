#include "memory.h"
#include <string.h>

struct memory_t* memory_new(int size)
{
  char* memory = (char*)calloc(1, size + 4);
  ((int*)memory)[0] = size;
  return (struct memory_t*)((int*)memory+1);
}

void memory_delete(struct memory_t* memory)
{
  free((int*)memory-1);
}

int memory_size(const struct memory_t* memory)
{
  return ((const int*)memory-1)[0];
}

unsigned char memory_byte(const struct memory_t* memory, int offset)
{
  unsigned char val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

unsigned short memory_short(const struct memory_t* memory, int offset)
{
  unsigned short val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

int memory_int(const struct memory_t* memory, int offset)
{
  int val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

float memory_float(const struct memory_t* memory, int offset)
{
  float val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

double memory_double(const struct memory_t* memory, int offset)
{
  double val;
  memcpy(&val, (const char*)memory+offset, sizeof(val));
  return val;
}

void memory_setbyte(struct memory_t* memory, int offset, unsigned char val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

void memory_setshort(struct memory_t* memory, int offset, unsigned short val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

void memory_setint(struct memory_t* memory, int offset, int val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

void memory_setfloat(struct memory_t* memory, int offset, float val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}

void memory_setdouble(struct memory_t* memory, int offset, double val)
{
  memcpy((char*)memory+offset, &val, sizeof(val));
}
