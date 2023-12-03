#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <json-c/json.h>

#include "altclient.h"

void print_usage();

char * progname = NULL;

int main(int argc, char ** argv) 
{
    int rc = 0;
    altclient_t * cli = NULL;
    char * resp = NULL;
    const char * repo1 = NULL;
    const char * repo2 = NULL;

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
    repo1 = (const char *)argv[1];
    repo2 = (const char *)argv[2];

//----------------------------------------------------------------------

    cli = altclient_new( DEFAULT_DOMAIN );     
    assert(cli);

//----------------------------------------------------------------------
//  Load packages by repo 1
//----------------------------------------------------------------------
    fprintf(stdout, "Load a list of packages for the repository %s \n",
            repo1);
    rc = altclient_get_branch_binary_packages(cli, repo1 /*"sisyphus"*/, &resp);
    if(rc < 0)
    {
        fprintf(stderr, "Error load packages list %d \n", rc);
        altclient_destructor(cli);
        cli = NULL;
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "LOad packet\n %s \n", resp);
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