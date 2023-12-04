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
            repo_name_1);
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