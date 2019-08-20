#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Memblock* CALL spCreateMemblock(int size);
EXPORT Memblock* CALL spLoadMemblock(const char* filename);
EXPORT void CALL spDeleteMemblock(Memblock* memblock);
EXPORT int CALL spGetMemblockSize(const Memblock* memblock);
EXPORT unsigned char CALL spGetMemblockByte(const Memblock* memblock, int offset);
EXPORT unsigned short CALL spGetMemblockShort(const Memblock* memblock, int offset);
EXPORT int CALL spGetMemblockInt(const Memblock* memblock, int offset);
EXPORT float CALL spGetMemblockFloat(const Memblock* memblock, int offset);
EXPORT double CALL spGetMemblockDouble(const Memblock* memblock, int offset);
EXPORT void CALL spSetMemblockByte(Memblock* memblock, int offset, unsigned char val);
EXPORT void CALL spSetMemblockShort(Memblock* memblock, int offset, unsigned short val);
EXPORT void CALL spSetMemblockInt(Memblock* memblock, int offset, int val);
EXPORT void CALL spSetMemblockFloat(Memblock* memblock, int offset, float val);
EXPORT void CALL spSetMemblockDouble(Memblock* memblock, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
