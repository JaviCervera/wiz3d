#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL UpdateTimer();

EXPORT float CALL GetDeltaTime();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TIME_H_INCLUDED */
