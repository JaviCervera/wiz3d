#include "file_system.h"
#include "memblock.h"
#include <string.h>

EXPORT Memblock* CALL wzCreateMemblock(int size) {
    char* memblock = (char*)calloc(1, size + 4);
    ((int*)memblock)[0] = (int)size;
    return (Memblock*)((int*)memblock+1);
}

EXPORT Memblock* CALL wzLoadMemblock(const char* filename) {
    size_t size;
    Memblock* memblock = NULL;

    size = wzGetFileSize(filename);
    if (size > 0) {
        memblock = wzCreateMemblock(size);
        _GetFileContents(filename, memblock);
    }

    return memblock;
}

EXPORT void CALL wzDeleteMemblock(Memblock* memblock) {
    free((int*)memblock-1);
}

EXPORT int CALL wzGetMemblockSize(const Memblock* memblock) {
    return ((const int*)memblock-1)[0];
}

EXPORT unsigned char CALL wzGetMemblockByte(const Memblock* memblock, int offset) {
    unsigned char val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT unsigned short CALL wzGetMemblockShort(const Memblock* memblock, int offset) {
    unsigned short val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT int CALL wzGetMemblockInt(const Memblock* memblock, int offset) {
    int val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT float CALL wzGetMemblockFloat(const Memblock* memblock, int offset) {
    float val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT double CALL wzGetMemblockDouble(const Memblock* memblock, int offset) {
    double val;
    memcpy(&val, (const char*)memblock+offset, sizeof(val));
    return val;
}

EXPORT void CALL wzSetMemblockByte(Memblock* memblock, int offset, unsigned char val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL wzSetMemblockShort(Memblock* memblock, int offset, unsigned short val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL wzSetMemblockInt(Memblock* memblock, int offset, int val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL wzSetMemblockFloat(Memblock* memblock, int offset, float val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}

EXPORT void CALL wzSetMemblockDouble(Memblock* memblock, int offset, double val) {
    memcpy((char*)memblock+offset, &val, sizeof(val));
}
