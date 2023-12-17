#include "altversion.h"

#include <stdio.h>
#include <string.h>


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

    


    return 0;
}
int altversion_compare(altversion_t * first, altversion_t * second)
{

}

