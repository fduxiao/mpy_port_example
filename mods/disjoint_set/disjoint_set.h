#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__

#include <py/obj.h>
#include "core.h"

// See https://micropython-usermod.readthedocs.io/en/latest/usermods_09.html for more infomation.

// If you want this to be reusable by others
typedef struct _DisjointSet_obj_t {
    mp_obj_base_t base;
    disjoint_set_t set;
} DisjointSet_obj_t;

// the type object
extern const mp_obj_type_t type_DisjointSet;

#endif
