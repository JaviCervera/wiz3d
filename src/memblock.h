#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Memblock* CALL bmCreateMemblock(int size);
EXPORT Memblock* CALL bmLoadMemblock(const char* filename);
EXPORT void CALL bmDeleteMemblock(Memblock* memblock);
EXPORT int CALL bmGetMemblockSize(const Memblock* memblock);
EXPORT unsigned char CALL bmGetMemblockByte(const Memblock* memblock, int offset);
EXPORT unsigned short CALL bmGetMemblockShort(const Memblock* memblock, int offset);
EXPORT int CALL bmGetMemblockInt(const Memblock* memblock, int offset);
EXPORT float CALL bmGetMemblockFloat(const Memblock* memblock, int offset);
EXPORT double CALL bmGetMemblockDouble(const Memblock* memblock, int offset);
EXPORT void CALL bmSetMemblockByte(Memblock* memblock, int offset, unsigned char val);
EXPORT void CALL bmSetMemblockShort(Memblock* memblock, int offset, unsigned short val);
EXPORT void CALL bmSetMemblockInt(Memblock* memblock, int offset, int val);
EXPORT void CALL bmSetMemblockFloat(Memblock* memblock, int offset, float val);
EXPORT void CALL bmSetMemblockDouble(Memblock* memblock, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
