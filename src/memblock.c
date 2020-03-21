#include "file_system.h"
#include "memblock.h"
#include <string.h>

EXPORT Memblock* CALL bmCreateMemblock(int size) {
    char* memblock = (char*)calloc(1, size + 4);
    ((int*)memblock)[0] = (int)size;
    return (Memblock*)((int*)memblock+1);
}

EXPORT Memblock* CALL bmLoadMemblock(const char* filename) {
    size_t size;
    Memblock* memblock = NULL;

    size = bmGetFileSize(filename);
    if (size > 0) {
        memblock = bmCreateMemblock(size);
        _GetFileContents(filename, memblock);
    }

    return memblock;
}

EXPORT void CALL bmDeleteMemblock(Memblock* memblock) {
    free((int*)memblock-1);
}

EXPORT int CALL bmGetMemblockSize(const Memblock* memblock) {
    return ((const int*)memblock-1)[0];
}

EXPORT unsigned char CALL bmGetMemblockByte(const Memblock* memblock, int offset) {
    unsigned char val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT unsigned short CALL bmGetMemblockShort(const Memblock* memblock, int offset) {
    unsigned short val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT int CALL bmGetMemblockInt(const Memblock* memblock, int offset) {
    int val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT float CALL bmGetMemblockFloat(const Memblock* memblock, int offset) {
    float val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT double CALL bmGetMemblockDouble(const Memblock* memblock, int offset) {
    double val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT void CALL bmSetMemblockByte(Memblock* memblock, int offset, unsigned char val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL bmSetMemblockShort(Memblock* memblock, int offset, unsigned short val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL bmSetMemblockInt(Memblock* memblock, int offset, int val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL bmSetMemblockFloat(Memblock* memblock, int offset, float val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL bmSetMemblockDouble(Memblock* memblock, int offset, double val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}
