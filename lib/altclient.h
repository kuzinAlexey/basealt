#ifndef ALTCLIENT_H
#define ALTCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <curl/curl.h>

#define DEFAULT_DOMAIN          (const char *)"https://rdb.altlinux.org"
#define DEFAULT_API             (const char *)"api"

typedef struct _altclient_t altclient_t;

struct _altclient_t
{
    char * parent;
    
    CURLSH * curl;
    pthread_mutex_t curl_lock;
};

altclient_t * altclient_new(const char * domain);


#ifdef __cplusplus
}
#endif

#endif // ALTCLIENT_H
