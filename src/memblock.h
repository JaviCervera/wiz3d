#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Memblock* CALL CreateMemblock(int size);
EXPORT Memblock* CALL LoadMemblock(const char* filename);
EXPORT void CALL DeleteMemblock(Memblock* memblock);
EXPORT int CALL GetMemblockSize(const Memblock* memblock);
EXPORT unsigned char CALL GetMemblockByte(const Memblock* memblock, int offset);
EXPORT unsigned short CALL GetMemblockShort(const Memblock* memblock, int offset);
EXPORT int CALL GetMemblockInt(const Memblock* memblock, int offset);
EXPORT float CALL GetMemblockFloat(const Memblock* memblock, int offset);
EXPORT double CALL GetMemblockDouble(const Memblock* memblock, int offset);
EXPORT void CALL SetMemblockByte(Memblock* memblock, int offset, unsigned char val);
EXPORT void CALL SetMemblockShort(Memblock* memblock, int offset, unsigned short val);
EXPORT void CALL SetMemblockInt(Memblock* memblock, int offset, int val);
EXPORT void CALL SetMemblockFloat(Memblock* memblock, int offset, float val);
EXPORT void CALL SetMemblockDouble(Memblock* memblock, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
