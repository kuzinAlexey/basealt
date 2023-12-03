#ifndef ALTCLIENT_H
#define ALTCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <curl/curl.h>

#include "altclient_global.h"

#define DEFAULT_DOMAIN          (const char *)"https://rdb.altlinux.org"
#define DEFAULT_API             (const char *)"api"

typedef struct _altclient_t altclient_t;

struct _altclient_t
{
    char * parent;      ///< full domain api
};

ALTCLIENT_EXPORT altclient_t * altclient_new(const char * domain);
ALTCLIENT_EXPORT void altclient_destructor(void * cli_p);

/**
 * 
*/
ALTCLIENT_EXPORT int altclient_get_branch_binary_packages(altclient_t * cli, const char * branch, char ** response);

#ifdef __cplusplus
}
#endif

#endif // ALTCLIENT_H
