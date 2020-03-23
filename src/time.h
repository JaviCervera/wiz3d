#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL wzUpdateTimer();

EXPORT float CALL wzGetDeltaTime();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TIME_H_INCLUDED */
