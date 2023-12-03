#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <json-c/json.h>

#include "altclient.h"

int main(void) 
{
    altclient_t * cli = altclient_new( DEFAULT_DOMAIN );     
    assert(cli);



    altclient_destructor(cli);
    cli = NULL;
    
    return 0;
}

