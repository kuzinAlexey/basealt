#include "arch.h"

#include <string.h>

const char * alt_arch_str[] =
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

    arch->limit = 255;  // начальное значение корзин
    arch->packs = (alt_pack_t **)calloc(1, sizeof(alt_pack_t *) * arch->limit);
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

int alt_arch_add(alt_arch_t * arch, const char * key, alt_arch_id tag)
{
    if(!arch || !key || (strlen(key) <= 0))
    {
        return -1;
    }

    int i;

    // увеличиваем хэш таблицу, если она наполнилась
    if(arch->cnt >= arch->limit)
    {
        // увеличиваем на 20%
        uint32_t new_limit = arch->limit * 1.2;
        alt_pack_t ** new_packs = (alt_pack_t **)calloc(1, sizeof(alt_pack_t *) * new_limit);
        if(!new_packs)
        {
            return -2;
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
    }

    // вставляем данные в таблицу
    int pack_hash = alt_arch_hash(key, arch->limit);
    alt_pack_t * pack = arch->packs[ pack_hash ];

    // Удаляем пакет, с таким же ключем если есть
    alt_pack_t * prev_pack = NULL;
    while(pack)
    {
        if(!strcmp(pack->key, key))
        {
            if(prev_pack)
            {
                prev_pack->next = pack->next;
            }
            free(pack->key);
            free(pack);
            break;
        }
        prev_pack = pack;
        pack = pack->next;
    }

    // добавляем пакет в таблицу
    alt_pack_t * new_pack = (alt_pack_t*)calloc(1, sizeof(alt_pack_t));
    if(!new_pack)
    {
        return -3;
    }

    new_pack->key = strdup(key);
    new_pack->hash = pack_hash;
    new_pack->arch_id = tag;
    new_pack->next = arch->packs[ pack_hash ];
    arch->packs[pack_hash] = new_pack;
    arch->cnt++;

    return arch->cnt;
}



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

