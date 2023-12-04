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

int alt_repo_load(alt_repo_t * repo, const char * msg)
{
    if(!repo || !msg || (strlen(msg) <= 0))
    {
        return -1;
    }

    int i;
    int rc = 0;

    struct json_tokener * tokener = json_tokener_new();
    if(!tokener)
    {
        return -2;
    }

    struct json_object * json = json_tokener_parse_ex(tokener, msg, strlen(msg));
    if(json_tokener_get_error( tokener ) == json_tokener_success)
    {
        struct json_object * packages_list;
        if(json_object_object_get_ex(json, "packages", &packages_list))
        {
            int arraylen = json_object_array_length( packages_list );

            for(i = 0; i < arraylen; i++) 
            {
                struct json_object * array_obj = json_object_array_get_idx( packages_list, i );
                struct json_object * array_obj_name = json_object_object_get(array_obj, "name");
                struct json_object * array_obj_arch = json_object_object_get(array_obj, "arch");
                struct json_object * array_obj_version = json_object_object_get(array_obj, "version");
                struct json_object * array_obj_release = json_object_object_get(array_obj, "release");

                int arch_tag = alt_arch_tag( json_object_get_string( array_obj_arch ) );
                const char * key = json_object_get_string( array_obj_name );
                if(arch_tag >= 0)
                {
                    alt_arch_add(repo->archs[ arch_tag ], key, arch_tag);
                }

                /*fprintf(stdout, "%s\t%s\t%s\t%s \n", 
                    json_object_get_string( array_obj_name ),
                    json_object_get_string( array_obj_arch ),
                    json_object_get_string( array_obj_version ),
                    json_object_get_string( array_obj_release ) );
                    */
                
            }
            rc = arraylen;
        }
    }

    json_tokener_free(tokener);
    
    return rc;
}



