#include "altversion.h"

#include <stdio.h>
#include <string.h>

// support functions
void parse_version(const char * version, int * major, int * minor, int * patch);

int altversion_init(altversion_t * ver)
{
    if(!ver)
    {
        return -1;
    }
    ver->major = 0;
    ver->minor = 0;
    ver->patch = 0;
    ver->release_num = 0; 
    return 0;
}
void altversion_clear(altversion_t * ver)
{
    if(ver)
    {
        ver->major = 0;
        ver->minor = 0;
        ver->patch = 0;
        ver->release_num = 0; 
    }
}

int altversion_setup(altversion_t * ver, const char * version, const char * release)
{
    if(!ver)
    {
        return -1;
    }
    if(!version || (strlen(version) <= 0) ||
         !release || (strlen(release) <= 0))
    {
        return -2;
    }

    char * token = NULL;

    // parse "version"
    parse_version(version, &ver->major, &ver->minor, &ver->patch);

    // parse "release"


    return 0;
}

int altversion_compare(altversion_t * first, altversion_t * second)
{

}




// support functions
void parse_version(const char * version, int * major, int * minor, int * patch)
{
    *major = 0;
    *minor = 0;
    *patch = 0;

    token = strtok(version, ".");   // major
    if(token)
    {
        *major = strtol(token, NULL, 10);
    }
    else
    {
        return;
    }

    token = strtok(NULL, ".");  // minor
    if(token)
    {
        *minor = strtol(token, NULL, 10);
    }
    else
    {
        return;
    }

    token = strtok(NULL, ".");  // patch
    if(token)
    {
        *patch = strtol(token, NULL, 10);
    }
    else
    {
        return;
    }
}