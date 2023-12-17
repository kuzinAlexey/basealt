/**
 * Структура формата записи версии пакета для alt linux
 * https://www.altlinux.org/Spec
*/

#ifndef REPO_H
#define REPO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

enum alt_compare_result
{
    ALT_COMP_EQ = 0,        ///< Структуры равны
    ALT_COMP_GT,            ///< Первая структура больше второй
    ALT_COMP_LT             ///< Первая структура меньше второй
};

typedef struct _altversion_t
{
    int major;              
    int minor;
    int patch;
    int release_num;
} altversion_t;

int altversion_init(altversion_t * ver);
void altversion_clear(altversion_t * ver);
int altversion_setup(altversion_t * ver, const char * version, const char * release);
int altversion_compare(altversion_t * first, altversion_t * second);


#ifdef __cplusplus
}
#endif

#endif // REPO_H
