#include "altclient.h"

#include <sys/uio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


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
    if(!cli->parent)
    {
        altclient_destructor(cli);
        cli = NULL;
        return NULL;
    }
    sprintf(cli->parent, "%s/%s", domain, DEFAULT_API);

    curl_global_init(CURL_GLOBAL_ALL);

    return cli;
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

static size_t altclient_recv_package_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
    size_t realsize = size * nmemb;

    struct iovec * iov = (struct iovec *)userp;
    assert(iov);

    iov->iov_base = realloc(iov->iov_base, iov->iov_len + realsize + 1);
    if(!iov->iov_base)
    {
        fprintf(stderr, "Erro memory allocation (%s) \n", 
                strerror(errno));

        return 0;
    }

    memcpy((iov->iov_base + iov->iov_len), contents, realsize);

    iov->iov_len += realsize;
    *((char*)iov->iov_base + iov->iov_len) = 0;

    return realsize;
}

int altclient_get_branch_binary_packages(altclient_t * cli, const char * branch, char ** response)
{
    int rc = 0;
    CURLSH * curl = NULL;
    CURLcode res;
    char url[1024];

    struct iovec iov;
    memset(&iov, 0, sizeof(struct iovec));

    if(!cli || !branch || (strlen(branch) <= 0) || !response)
    {
        rc = -1;
        goto error;
    }
    
    curl = curl_easy_init();
    if(!curl)
    {
        rc = -2;
        goto error;
    }
    
    memset(url, 0, sizeof(url));
    sprintf(url, "%s/export/branch_binary_packages/%s",
            cli->parent, branch);
            
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, altclient_recv_package_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&iov);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        if(iov.iov_base && iov.iov_len)
        {
            free(iov.iov_base);
            iov.iov_base = NULL;
        }
        rc = -4;
        goto error;
    }

error:
    if(curl)
    {
        curl_easy_cleanup(curl);
        curl = NULL;
    }
    
    return rc;
}
