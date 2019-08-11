#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SMemblock;

EXPORT struct SMemblock* CALL CreateMemblock(int size);
EXPORT struct SMemblock* CALL LoadMemblock(const char* filename);
EXPORT void CALL DeleteMemblock(struct SMemblock* memblock);
EXPORT int CALL GetMemblockSize(const struct SMemblock* memblock);
EXPORT unsigned char CALL GetMemblockByte(const struct SMemblock* memblock, int offset);
EXPORT unsigned short CALL GetMemblockShort(const struct SMemblock* memblock, int offset);
EXPORT int CALL GetMemblockInt(const struct SMemblock* memblock, int offset);
EXPORT float CALL GetMemblockFloat(const struct SMemblock* memblock, int offset);
EXPORT double CALL GetMemblockDouble(const struct SMemblock* memblock, int offset);
EXPORT void CALL SetMemblockByte(struct SMemblock* memblock, int offset, unsigned char val);
EXPORT void CALL SetMemblockShort(struct SMemblock* memblock, int offset, unsigned short val);
EXPORT void CALL SetMemblockInt(struct SMemblock* memblock, int offset, int val);
EXPORT void CALL SetMemblockFloat(struct SMemblock* memblock, int offset, float val);
EXPORT void CALL SetMemblockDouble(struct SMemblock* memblock, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
