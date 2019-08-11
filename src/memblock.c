#include "memblock.h"
#include <string.h>

EXPORT struct SMemblock* CALL CreateMemblock(int size)
{
  char* memblock = (char*)calloc(1, size + 4);
  ((int*)memblock)[0] = size;
  return (struct SMemblock*)((int*)memblock+1);
}

EXPORT void CALL DeleteMemblock(struct SMemblock* memblock)
{
  free((int*)memblock-1);
}

EXPORT int CALL GetMemblockSize(const struct SMemblock* memblock)
{
  return ((const int*)memblock-1)[0];
}

EXPORT unsigned char CALL GetMemblockByte(const struct SMemblock* memblock, int offset)
{
  unsigned char val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT unsigned short CALL GetMemblockShort(const struct SMemblock* memblock, int offset)
{
  unsigned short val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT int CALL GetMemblockInt(const struct SMemblock* memblock, int offset)
{
  int val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT float CALL GetMemblockFloat(const struct SMemblock* memblock, int offset)
{
  float val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT double CALL GetMemblockDouble(const struct SMemblock* memblock, int offset)
{
  double val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT void CALL SetMemblockByte(struct SMemblock* memblock, int offset, unsigned char val)
{
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL SetMemblockShort(struct SMemblock* memblock, int offset, unsigned short val)
{
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL SetMemblockInt(struct SMemblock* memblock, int offset, int val)
{
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL SetMemblockFloat(struct SMemblock* memblock, int offset, float val)
{
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL SetMemblockDouble(struct SMemblock* memblock, int offset, double val)
{
  memcpy((char*)memblock+offset, &val, sizeof(val));
}
