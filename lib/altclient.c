#include "altclient.h"



altclient_t * altclient_new(const char * domain)
{
    if(!domain || (strlen(domain) <= 0))
    {
        return NULL;
    }

    altclient_t * cli = (altclient_t*)calloc(1, sizeof(altclient_t));
    if(!cli)
    {
        return NULL;
    }

    cli->parent = (char *)calloc(1, strlen(domain) + strlen(DEFAULT_API) + 2);
    if(!api->parent)
    {
        altclient_destructor(cli);
        cli = NULL;
        return NULL;
    }
    sprintf(cli->parent, "%s/%s", domain, DEFAULT_API);

    cli->curl = curl_share_init();
    if(!cli->curl)
    {
        altclient_destructor(cli);
        cli = NULL;
        return NULL;
    }

    pthread_mutex_init(&cli->curl_lock, NULL);

    curl_share_setopt(cli->curl_shared, CURLSHOPT_LOCKFUNC, lock_function);
    curl_share_setopt(cli->curl_shared, CURLSHOPT_UNLOCKFUNC, unlock_function);

    curl_share_setopt(cli->curl_shared, CURLSHOPT_USERDATA, api);

    return api;
}

void altclient_destructor(void * cli_p)
{
    altclient_t * cli = (altclient_t *)cli_p;
    if(cli)
    {
        if(cli->parent)
        {
            free(cli->parent);
            cli->parent = NULL;
        }
        free(cli);
    }
}

