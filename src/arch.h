#ifndef ARCH_H
#define ARCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


enum alt_arch_id
{
    noarch = 0,
    alt_arch_i586,      ///<
    alt_arch_x86_64,
    alt_arch_x86_64_i586,
    alt_arch_aarch64,
    alt_arch_ppc64le,
    alt_arch_mipsel,
    alt_arch_armh
};

const char * alt_arch[] =
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


struct alt_pack_t
{
    char * key;                     //!< Наименование пакета
    int arch_id;                    //!< Идентификатор архитектуры пакета
    uint32_t index;                 //!< Хэш индекс пакета
    struct alt_pack_t * next;       //!< Следующий пакет в списке коллизий по имени
};


typedef struct _alt_arch_t
{
    int id;                         ///< Идентификатор архитектуры
    int limit;                      ///< Выделенное количество корзин
    int cnt;                        ///< Количество пакетов
    uint32_t count;                 //!< Текущий размер таблицы
    struct alt_pack_t ** packs;     //!< Массив элементов таблицы

}alt_arch_t;

alt_arch_t * alt_arch_new();
void alt_arch_destructor(void * arch_p);


#ifdef __cplusplus
}
#endif

#endif // ARCH_H
