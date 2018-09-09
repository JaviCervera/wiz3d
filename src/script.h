#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool_t script_init();
void script_finish();
bool_t script_load(const char* filename);
const char* script_error();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SCRIPT_H_INCLUDED */
