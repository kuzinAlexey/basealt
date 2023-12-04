#include "repo.h"



alt_repo_t * alt_repo_new()
{
    alt_repo_t * repo = (alt_repo_t*)calloc(1, sizeof(alt_repo_t));
    if(!repo)
    {
        return NULL;
    }
    int i;

// создаем репозиторий на 8 архитектур
    repo->archs = (alt_arch_t**)calloc(1, sizeof(alt_arch_t*) * NUM_ARCHS);
    if(!repo->archs)
    {
        alt_repo_destructor(repo);
        return NULL;
    }

    repo->cnt = NUM_ARCHS;

    for(i = 0; i < NUM_ARCHS; i++)
    {
        repo->archs[i] = alt_arch_new();
        if(!repo->archs[i])
        {
            alt_repo_destructor(repo);
            return NULL;
        }
    }

    return repo;
}


void alt_repo_destructor(void * repo_p)
{
    int i;
    alt_repo_t * repo = (alt_repo_t*)repo_p;
    if(repo)
    {
        for(i = 0; i < repo->cnt; i++)
        {
            if(repo->archs[i])
            {
                free(repo->archs[i]);
                repo->archs[i] = NULL;
            }
        }
        free(repo->archs);
        free(repo);
    }
}

