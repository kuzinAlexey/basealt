#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>


#include "altclient.h"
#include "repo.h"


void print_usage();

char * progname = NULL;

int main(int argc, char ** argv) 
{
    int i, j;
    int rc = 0;
    altclient_t * cli = NULL;
    char * resp = NULL;
    const char * repo_name_1 = NULL;
    const char * repo_name_2 = NULL;

//----------------------------------------------------------------------
//  Parse args
//----------------------------------------------------------------------
    char * delim_ptr = strrchr(argv[0], '/');
    progname = (delim_ptr != NULL) ? strdup(delim_ptr + 1) : strdup(argv[0]);
    assert(progname);
    if(argc != 3)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    repo_name_1 = (const char *)argv[1];
    repo_name_2 = (const char *)argv[2];

//----------------------------------------------------------------------

    cli = altclient_new( DEFAULT_DOMAIN );     
    assert(cli);

//----------------------------------------------------------------------
//  Load packages by repo 1
//----------------------------------------------------------------------
    alt_repo_t * repo_1 = alt_repo_new();
    assert(repo_1);

    fprintf(stdout, "Loading a list of packages by the repository %s \n",
            repo_name_1);
    rc = altclient_get_branch_binary_packages(cli, repo_name_1, &resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error load packages list %d \n", rc);
        altclient_destructor(cli);
        cli = NULL;
        exit(EXIT_FAILURE);
    }

    rc = alt_repo_load(repo_1, resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error parse response %d \n", rc);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Loaded %d packets by %s \n", 
            rc, repo_name_1);

//----------------------------------------------------------------------

//----------------------------------------------------------------------
//  Load packages by repo 2
//----------------------------------------------------------------------
    alt_repo_t * repo_2 = alt_repo_new();
    assert(repo_2);

    fprintf(stdout, "Loading a list of packages by the repository %s \n",
            repo_name_2);

    rc = altclient_get_branch_binary_packages(cli, repo_name_2, &resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error load packages list %d \n", rc);
        altclient_destructor(cli);
        cli = NULL;
        exit(EXIT_FAILURE);
    }

    rc = alt_repo_load(repo_2, resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error parse response %d \n", rc);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Loaded %d packets by %s \n", 
            rc, repo_name_2);

//----------------------------------------------------------------------

    struct json_object * only_repo_1 = json_object_new_object();
    assert(only_repo_1);
    struct json_object * only_repo_2 = json_object_new_object();
    assert(only_repo_2);

    alt_pack_t * pack_find, * pack;

    // цикл для перебора архитектур
    for(i = 0; i < NUM_ARCHS; i++)
    {
        // перебор пакетов из репозитория 1
        struct json_object * only_arch_1 = json_object_new_array();
        assert(only_arch_1);

        pack = alt_arch_first( repo_1->archs[i] );
        while(pack)
        {
            pack_find = alt_arch_find( repo_2->archs[i], pack->key);
            if(!pack_find)
            {
                json_object_array_add(only_arch_1, json_object_new_string(pack->key));
            }
            pack = alt_arch_next( repo_1->archs[i] );
        }
        json_object_object_add(only_repo_1, alt_arch_string((alt_arch_id)i), only_arch_1);

        // перебор пакетов из репозитория 2
        struct json_object * only_arch_2 = json_object_new_array();
        assert(only_arch_2);

        pack = alt_arch_first( repo_2->archs[i] );
        while(pack)
        {
            pack_find = alt_arch_find( repo_1->archs[i], pack->key);
            if(!pack_find)
            {
                json_object_array_add(only_arch_2, json_object_new_string(pack->key));
            }
            pack = alt_arch_next( repo_2->archs[i] );
        }
        json_object_object_add(only_repo_2, alt_arch_string((alt_arch_id)i), only_arch_2);

    }

    struct json_object * output = json_object_new_object();
    assert(output);
    json_object_object_add(output, repo_name_1, only_repo_1);
    json_object_object_add(output, repo_name_2, only_repo_2);

    FILE * outfile = fopen("/tmp/output.json", "w");
    if(outfile)
    {
        fprintf(outfile, "\n%s\n", json_object_to_json_string(output));
        fclose(outfile);
    }


    // destructors
    json_object_put(output);

    alt_repo_destructor(repo_1);
    alt_repo_destructor(repo_2);
    altclient_destructor(cli);
    free(progname);

    return 0;
}


void print_usage()
{
    fprintf(stdout, "Usage:  %s repo1 repo2 \n",
            progname);
}