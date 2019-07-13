#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct memory_t;

EXPORT struct memory_t* CALL memory_new(int size);
EXPORT void CALL memory_delete(struct memory_t* memory);
EXPORT int CALL memory_size(const struct memory_t* memory);
EXPORT unsigned char CALL memory_byte(const struct memory_t* memory, int offset);
EXPORT unsigned short CALL memory_short(const struct memory_t* memory, int offset);
EXPORT int CALL memory_int(const struct memory_t* memory, int offset);
EXPORT float CALL memory_float(const struct memory_t* memory, int offset);
EXPORT double CALL memory_double(const struct memory_t* memory, int offset);
EXPORT void CALL memory_setbyte(struct memory_t* memory, int offset, unsigned char val);
EXPORT void CALL memory_setshort(struct memory_t* memory, int offset, unsigned short val);
EXPORT void CALL memory_setint(struct memory_t* memory, int offset, int val);
EXPORT void CALL memory_setfloat(struct memory_t* memory, int offset, float val);
EXPORT void CALL memory_setdouble(struct memory_t* memory, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
