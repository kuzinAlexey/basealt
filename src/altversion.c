#include "altversion.h"

#include <stdio.h>
#include <string.h>

// support functions
void parse_version(const char * version, int * major, int * minor, int * patch);
void parse_release(const char * release, int * num);



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

    // parse "version"
    parse_version(version, &ver->major, &ver->minor, &ver->patch);

    // parse "release"
    parse_release(release, &ver->release_num);


    return 0;
}

int altversion_compare(altversion_t * first, altversion_t * second)
{
    if(!first || !second)
    {
        return -1;
    }

// compare version
    if(first->major > second->major)
    {
        return ALT_COMP_GT;
    }
    else if(first->major < second->major)
    {
        return ALT_COMP_LT;
    }
    if(first->minor > second->minor)
    {
        return ALT_COMP_GT;
    }
    else if(first->minor < second->minor)
    {
        return ALT_COMP_LT;
    }
    if(first->patch > second->patch)
    {
        return ALT_COMP_GT;
    }
    else if(first->patch < second->patch)
    {
        return ALT_COMP_LT;
    }

// compare release
    if(first->release_num > second->release_num)
    {
        return ALT_COMP_GT;
    }
    else if(first->release_num < second->release_num)
    {
        return ALT_COMP_LT;
    }

    return ALT_COMP_EQ;
}



// support functions
void parse_version(const char * version, int * major, int * minor, int * patch)
{
    char * str = (char*)version;
    char * token = NULL;

    *major = 0;
    *minor = 0;
    *patch = 0;

    token = strtok(str, ".");   // major
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

void parse_release(const char * release, int * num)
{
    char * str = (char*)release;

    *num = 0;

    // Поиск подстроки "alt"
    char * altPtr = strstr(str, "alt");
    if (altPtr == NULL) // Строка не содержит "alt"
    {
        return;
    } 
 
    // Извлечение числа после "alt"
    sscanf(altPtr + 3, "%d", num); // +3 для пропуска символов "alt"
}


