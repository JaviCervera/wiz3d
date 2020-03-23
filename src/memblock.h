#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Memblock* CALL wzCreateMemblock(int size);
EXPORT Memblock* CALL wzLoadMemblock(const char* filename);
EXPORT void CALL wzDeleteMemblock(Memblock* memblock);
EXPORT int CALL wzGetMemblockSize(const Memblock* memblock);
EXPORT unsigned char CALL wzGetMemblockByte(const Memblock* memblock, int offset);
EXPORT unsigned short CALL wzGetMemblockShort(const Memblock* memblock, int offset);
EXPORT int CALL wzGetMemblockInt(const Memblock* memblock, int offset);
EXPORT float CALL wzGetMemblockFloat(const Memblock* memblock, int offset);
EXPORT double CALL wzGetMemblockDouble(const Memblock* memblock, int offset);
EXPORT void CALL wzSetMemblockByte(Memblock* memblock, int offset, unsigned char val);
EXPORT void CALL wzSetMemblockShort(Memblock* memblock, int offset, unsigned short val);
EXPORT void CALL wzSetMemblockInt(Memblock* memblock, int offset, int val);
EXPORT void CALL wzSetMemblockFloat(Memblock* memblock, int offset, float val);
EXPORT void CALL wzSetMemblockDouble(Memblock* memblock, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
