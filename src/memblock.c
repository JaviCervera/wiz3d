#include "file_system.h"
#include "memblock.h"
#include <string.h>

EXPORT Memblock* CALL spCreateMemblock(int size) {
  char* memblock = (char*)calloc(1, size + 4);
  ((int*)memblock)[0] = (int)size;
  return (Memblock*)((int*)memblock+1);
}

EXPORT Memblock* CALL spLoadMemblock(const char* filename) {
  size_t size;
  Memblock* memblock = NULL;

  size = spGetFileSize(filename);
  if (size > 0) {
    memblock = spCreateMemblock(size);
    _GetFileContents(filename, memblock);
  }

  return memblock;
}

EXPORT void CALL spDeleteMemblock(Memblock* memblock) {
  free((int*)memblock-1);
}

EXPORT int CALL spGetMemblockSize(const Memblock* memblock) {
  return ((const int*)memblock-1)[0];
}

EXPORT unsigned char CALL spGetMemblockByte(const Memblock* memblock, int offset) {
  unsigned char val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT unsigned short CALL spGetMemblockShort(const Memblock* memblock, int offset) {
  unsigned short val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT int CALL spGetMemblockInt(const Memblock* memblock, int offset) {
  int val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT float CALL spGetMemblockFloat(const Memblock* memblock, int offset) {
  float val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT double CALL spGetMemblockDouble(const Memblock* memblock, int offset) {
  double val;
  memcpy(&val, (const char*)memblock+offset, sizeof(val));
  return val;
}

EXPORT void CALL spSetMemblockByte(Memblock* memblock, int offset, unsigned char val) {
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL spSetMemblockShort(Memblock* memblock, int offset, unsigned short val) {
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL spSetMemblockInt(Memblock* memblock, int offset, int val) {
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL spSetMemblockFloat(Memblock* memblock, int offset, float val) {
  memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL spSetMemblockDouble(Memblock* memblock, int offset, double val) {
  memcpy((char*)memblock+offset, &val, sizeof(val));
}
