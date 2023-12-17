/**
 * Структура формата записи версии пакета для alt linux
 * https://www.altlinux.org/Spec
*/

#ifndef alt_version_H
#define alt_version_H

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

typedef struct _alt_version_t
{
    int major;              
    int minor;
    int patch;
    int release_num;
} alt_version_t;

int alt_version_init(alt_version_t * ver);
void alt_version_clear(alt_version_t * ver);
int alt_version_setup(alt_version_t * ver, const char * version, const char * release);
int alt_version_compare(alt_version_t * first, alt_version_t * second);


#ifdef __cplusplus
}
#endif

#endif // alt_version_H
