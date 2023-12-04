#ifndef REPO_H
#define REPO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "arch.h"

typedef struct _alt_repo_t
{
    int cnt;                ///< Количество архитектур
    alt_arch_t ** archs;    ///< Список архитектур
}alt_repo_t;

alt_repo_t * alt_repo_new();
void alt_repo_destructor(void * repo_p);


#ifdef __cplusplus
}
#endif

#endif // REPO_H
