#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL bmUpdateTimer();

EXPORT float CALL bmGetDeltaTime();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TIME_H_INCLUDED */
