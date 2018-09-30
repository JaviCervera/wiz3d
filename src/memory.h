#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct memory_t;

struct memory_t* memory_new(int size);
void memory_delete(struct memory_t* memory);
int memory_size(const struct memory_t* memory);
unsigned char memory_byte(const struct memory_t* memory, int offset);
unsigned short memory_short(const struct memory_t* memory, int offset);
int memory_int(const struct memory_t* memory, int offset);
float memory_float(const struct memory_t* memory, int offset);
double memory_double(const struct memory_t* memory, int offset);
void memory_setbyte(struct memory_t* memory, int offset, unsigned char val);
void memory_setshort(struct memory_t* memory, int offset, unsigned short val);
void memory_setint(struct memory_t* memory, int offset, int val);
void memory_setfloat(struct memory_t* memory, int offset, float val);
void memory_setdouble(struct memory_t* memory, int offset, double val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEMORY_H_INCLUDED */
