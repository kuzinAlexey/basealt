#ifndef ARCH_H
#define ARCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum _alt_arch_id
{
    noarch = 0,
    alt_arch_i586,      ///<
    alt_arch_x86_64,
    alt_arch_x86_64_i586,
    alt_arch_aarch64,
    alt_arch_ppc64le,
    alt_arch_mipsel,
    alt_arch_armh
}alt_arch_id;


typedef struct _alt_pack_t
{
    char * key;                     ///< Наименование пакета
    int arch_id;                    ///< Идентификатор архитектуры пакета
    uint32_t hash;                 ///< Хэш индекс пакета
    struct _alt_pack_t * next;       ///< Следующий пакет в списке коллизий по имени
}alt_pack_t;


typedef struct _alt_arch_t
{
    int id;                         ///< Идентификатор архитектуры
    int limit;                      ///< Выделенное количество корзин
    int cnt;                        ///< Количество пакетов
    uint32_t count;                 ///< Текущий размер таблицы
    alt_pack_t ** packs;            ///< Массив элементов таблицы
}alt_arch_t;

alt_arch_t * alt_arch_new();
void alt_arch_destructor(void * arch_p);

int alt_arch_add(alt_arch_t * arch, const char * key, alt_arch_id tag);

#ifdef __cplusplus
}
#endif

#endif // ARCH_H
