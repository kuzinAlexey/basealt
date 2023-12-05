#include "arch.h"

#include <stdio.h>
#include <string.h>

const char * alt_arch_str[NUM_ARCHS] =
{
    "noarch", 
    "i586", 
    "x86_64", 
    "x86_64_i586", 
    "aarch64", 
    "ppc64le", 
    "mipsel", 
    "armh"
};


// support funcs
static uint32_t alt_arch_hash(const char * key, uint32_t limit);


alt_arch_t * alt_arch_new()
{
    alt_arch_t * arch = (alt_arch_t *)calloc(1, sizeof(alt_arch_t));
    if(!arch)
    {
        return NULL;
    }

    arch->limit = 255;  // начальный размер хэш
    arch->cnt = 0;

    arch->packs = (alt_pack_t **)calloc(1, sizeof(alt_pack_t *) * arch->limit);
    if(!arch->packs)
    {
        alt_arch_destructor(arch);
        return NULL;
    }

    arch->cur_hash = 0;
    arch->cur_pack = NULL;

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

                    arch->cnt--;

                    pack = next_pack;
                }
            }
            free(arch->packs);
        }
        free(arch);
    }

}

alt_pack_t * alt_arch_find(alt_arch_t * arch, const char * key)
{
    if(!arch || !key || (strlen(key) <= 0))
    {
        return NULL;
    }

    uint32_t hash =  alt_arch_hash(key, arch->limit);
    alt_pack_t * pack = arch->packs[hash];
    while(pack)
    {
        if(!strcmp(pack->key, key))
        {
            break;
        }
        pack = pack->next;
    }
    return pack;
}

int alt_arch_add(alt_arch_t * arch, const char * key, alt_arch_id tag, const char * vr)
{
    if(!arch || !key || (strlen(key) <= 0))
    {
        return -1;
    }

    int i;
/*
    // Удаляем пакет, с таким же ключем если есть
    alt_pack_t * pack = arch->packs[ pack_hash ];
    alt_pack_t * prev_pack = NULL;
    while(pack)
    {
        if(strcmp(pack->key, key) == 0)
        {
            if(prev_pack)
            {
                prev_pack->next = pack->next;
            }
            free(pack->key);
            free(pack);
            pack = NULL;
            break;
        }
        prev_pack = pack;
        fprintf(stdout, "tut %ld \n", pack);
        pack = pack->next;
    }
*/
    // добавляем пакет в таблицу
    alt_pack_t * new_pack = (alt_pack_t*)calloc(1, sizeof(alt_pack_t));
    if(!new_pack)
    {
        return -2;
    }

    new_pack->key = strdup(key);
    new_pack->hash = alt_arch_hash(key, arch->limit);
    new_pack->arch_id = tag;
    new_pack->ver_rel = strdup( vr );
    new_pack->next = arch->packs[ new_pack->hash ];
    arch->packs[new_pack->hash] = new_pack;
    arch->cnt++;

    // увеличиваем хэш таблицу, если она наполнилась
    if(arch->cnt >= arch->limit * 0.75)
    {
        // увеличиваем на 20%
        uint32_t new_limit = (double)arch->limit * 1.2;
        alt_pack_t ** new_packs = (alt_pack_t **)calloc(1, sizeof(alt_pack_t *) * new_limit);
        if(!new_packs)
        {
            return -3;
        }

        for(i = 0; i < arch->limit; i++)
        {
            alt_pack_t * pack = arch->packs[i];
            while(pack)
            {
                alt_pack_t * next_pack = pack->next;
                pack->hash = alt_arch_hash(pack->key, new_limit);
                pack->next = new_packs[pack->hash];
                new_packs[pack->hash] = pack;
                pack = next_pack;
            }
        }

        free(arch->packs);
        arch->packs = new_packs;
        arch->limit = new_limit;

        //fprintf(stdout, "Resize arch table %d \n", arch->limit);
    }

    return arch->cnt;
}

int alt_arch_tag(const char * arch_str)
{
    int i;
    for(i = 0; i < NUM_ARCHS; i++)
    {
        if(strcmp(arch_str, alt_arch_str[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

const char * alt_arch_string(alt_arch_id tag)
{
    return alt_arch_str[tag];
}


alt_pack_t * alt_arch_first(alt_arch_t * arch)
{
    if(!arch)
    {
        return NULL;
    }
    arch->cur_hash = 0;
    arch->cur_pack = arch->packs[arch->cur_hash];
    return alt_arch_next(arch);
}


alt_pack_t * alt_arch_next(alt_arch_t * arch)
{
    if(!arch)
    {
        return NULL;
    }

    while(arch->cur_pack == NULL)
    {
        if(arch->cur_hash < (arch->limit - 1))
        {
            arch->cur_hash++;
        }
        else
        {
            return NULL;
        }

        arch->cur_pack = arch->packs[arch->cur_hash];
    }

    if(!arch->cur_pack)
    {
        return NULL;
    }

    alt_pack_t * next_pack = arch->cur_pack->next;
    alt_pack_t * ret_pack = arch->cur_pack;
   
    arch->cur_pack = next_pack;

    return ret_pack;
}


// support funcs
static uint32_t alt_arch_hash(const char * key, uint32_t limit)
{
    uint32_t key_hash = 0;
    while(*key)
    {
        key_hash = 13 * key_hash ^ *key++;
    }
    key_hash %= limit;
    return key_hash;
}

