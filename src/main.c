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
    fprintf(stdout, "Load a list of packages for the repository %s \n",
            repo_name_1);
    rc = altclient_get_branch_binary_packages(cli, repo_name_1 /*"sisyphus"*/, &resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error load packages list %d \n", rc);
        altclient_destructor(cli);
        cli = NULL;
        exit(EXIT_FAILURE);
    }

    alt_repo_t * repo_1 = alt_repo_new();
    assert(repo_1);
    rc = alt_repo_load(repo_1, resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error parse response %d \n", rc);
        exit(EXIT_FAILURE);
    }
    
    // 
    alt_arch_t * arch_1 = alt_arch_new();
    struct json_tokener * tokener = json_tokener_new();
    assert(tokener);

    struct json_object * json = json_tokener_parse_ex(tokener, resp, strlen(resp));

    enum json_tokener_error jerr = json_tokener_get_error( tokener );
    if (jerr == json_tokener_success) 
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
                /*fprintf(stdout, "%s\t%s\t%s\t%s \n", 
                    json_object_get_string( array_obj_name ),
                    json_object_get_string( array_obj_arch ),
                    json_object_get_string( array_obj_version ),
                    json_object_get_string( array_obj_release ) );
                    */

                rc = alt_arch_add(arch_1, json_object_get_string( array_obj_name ), alt_arch_i586);
                if(rc < 0)
                {
                    fprintf(stderr, "Error alt_arch_add() %d \n", rc);
                }
                
            }

            fprintf(stdout, "List size %d \n", arraylen);
            fprintf(stdout, "Arch size %d \n", arch_1->cnt);
        }

    }

//----------------------------------------------------------------------



    altclient_destructor(cli);
    cli = NULL;
    free(progname);

    return 0;
}


void print_usage()
{
    fprintf(stdout, "Usage:  %s repo1 repo2 \n",
            progname);
}