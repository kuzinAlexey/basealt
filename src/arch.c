#include "arch.h"


alt_arch_t * alt_arch_new()
{
    alt_arch_t * arch = (alt_arch_t *)calloc(1, sizeof(alt_arch_t));
    if(!arch)
    {
        return NULL;
    }

    arch->limit = 255;  // начальное значение корзин
    arch->packs = (alt_arch_t **)calloc(1, sizeof(alt_arch_t *) * arch->limit);
    if(!arch->packs)
    {
        alt_arch_destructor(arch);
        return NULL;
    }

    arch->cnt = 0;

    return arch;
}

void alt_arch_destructor(void * arch_p)
{
    int i;
    alt_arch_t * arch = (alt_arch_t *)arch_p;
    if(arch)
    {
        if(arch->packs)
        {
            for(i = 0; i < arch->limit; i++)
            {
                alt_pack_t * pack = arch->packs[i];
                while(pack)
                {
                    alt_pack_t * next_pack = pack->next;
                    // remove packet
                    if(pack->key)
                    {
                        free(pack->key);
                        pack->key = NULL;
                    }
                    free(pack);

                    hashtable->count--;

                    pack = next_pack;
                }
            }

            free(hashtable->buckets);
        }
        free(arch);
    }

}




