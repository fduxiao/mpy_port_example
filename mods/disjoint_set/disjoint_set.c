#include <py/builtin.h>
#include <py/runtime.h>
#include <py/obj.h>
#include "core.h"
#include "disjoint_set.h"

#define CANNOT_ALLOCATE_MEMORY 12

// functions

// info
static mp_obj_t disjoint_set_info(void) {
    mp_printf(&mp_plat_print, "disjoint set\n");
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(disjoint_set_info_obj, disjoint_set_info);


// classes

// print function
static void DisjointSet_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind;
    DisjointSet_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int size = 0;
    if(self->set != NULL) {
        size = self->set->size;
    }
    mp_print_str(print, "DisjointSet(");
    mp_obj_print_helper(print, mp_obj_new_int(size), PRINT_REPR);
    mp_print_str(print, ")");
}

// constructor
static mp_obj_t DisjointSet_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 1, true);
    // parse the arguments
    mp_int_t size = 0;
    if(n_args == 1) {
        size = mp_obj_get_int(args[0]);
    }

    disjoint_set_t set;
    
    if(size == 0) {
        set = NULL;
    } else {
        set = disjoint_set_new(size);
        if(set == NULL) {
            mp_raise_OSError(CANNOT_ALLOCATE_MEMORY);
            return mp_const_none;
        }
    }

    // make the python object;
    DisjointSet_obj_t *self = m_new_obj(DisjointSet_obj_t);
    // and set its type.
    self->base.type = &type_DisjointSet;

    // then, initialize the data
    self->set = set;
    return MP_OBJ_FROM_PTR(self);
}


// check if the set is empty or not
static mp_obj_t DisjointSet_empty(const mp_obj_t self_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_bool(self->set == NULL);
}
MP_DEFINE_CONST_FUN_OBJ_1(DisjointSet_empty_obj, DisjointSet_empty);


// initialize
static mp_obj_t DisjointSet_init(const mp_obj_t self_in, const mp_obj_t size_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    if(self->set != NULL) {
        disjoint_set_delete(self->set);
    }
    mp_int_t size = mp_obj_get_int(size_in);
    if(size == 0) {
        return self_in;
    }
    self->set = disjoint_set_new(size);
    if(self->set == NULL) {
        mp_raise_OSError(CANNOT_ALLOCATE_MEMORY);
        return mp_const_none;
    }
    return self_in;
}
MP_DEFINE_CONST_FUN_OBJ_2(DisjointSet_init_obj, DisjointSet_init);


// deinitialize
static mp_obj_t DisjointSet_deinit(const mp_obj_t self_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    disjoint_set_delete(self->set);
    self->set = NULL;
    return self_in;
}
MP_DEFINE_CONST_FUN_OBJ_1(DisjointSet_deinit_obj, DisjointSet_deinit);


// class size
static mp_obj_t DisjointSet_get_n_sets(const mp_obj_t self_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    if(self->set == NULL) {
        return mp_obj_new_int(0);
    }
    return mp_obj_new_int(self->set->n_sets);
}
MP_DEFINE_CONST_FUN_OBJ_1(DisjointSet_get_n_sets_obj, DisjointSet_get_n_sets);


// find
static mp_obj_t DisjointSet_find(const mp_obj_t self_in, const mp_obj_t index_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    mp_int_t index = mp_obj_get_int(index_in);
    return mp_obj_new_int(disjoint_set_find(self->set, index));
}
MP_DEFINE_CONST_FUN_OBJ_2(DisjointSet_find_obj, DisjointSet_find);


// union
static mp_obj_t DisjointSet_union(const mp_obj_t self_in, const mp_obj_t i_in, const mp_obj_t j_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    mp_int_t i = mp_obj_get_int(i_in);
    mp_int_t j = mp_obj_get_int(j_in);
    return mp_obj_new_int(disjoint_set_union(self->set, i, j));
}
MP_DEFINE_CONST_FUN_OBJ_3(DisjointSet_union_obj, DisjointSet_union);


// same
static mp_obj_t DisjointSet_same(const mp_obj_t self_in, const mp_obj_t i_in, const mp_obj_t j_in) {
    DisjointSet_obj_t* self = MP_OBJ_TO_PTR(self_in);
    mp_int_t i = mp_obj_get_int(i_in);
    mp_int_t j = mp_obj_get_int(j_in);
    mp_int_t root_i = disjoint_set_find(self->set, i);
    mp_int_t root_j = disjoint_set_find(self->set, j);
    mp_int_t result = 0;
    if(root_i == -1 || root_j == -1) {
        result = 0;
    } else {
        result = root_i == root_j;
    }
    return mp_obj_new_bool(result);
}
MP_DEFINE_CONST_FUN_OBJ_3(DisjointSet_same_obj, DisjointSet_same);


// Then, make the class object.
// Define the symbol table.
static const mp_rom_map_elem_t DisjointSet_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_empty), MP_ROM_PTR(&DisjointSet_empty_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_init), MP_ROM_PTR(&DisjointSet_init_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&DisjointSet_deinit_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_get_n_sets), MP_ROM_PTR(&DisjointSet_get_n_sets_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_find), MP_ROM_PTR(&DisjointSet_find_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_union), MP_ROM_PTR(&DisjointSet_union_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_same), MP_ROM_PTR(&DisjointSet_same_obj) },
};
// The symbol dict object.
static MP_DEFINE_CONST_DICT(DisjointSet_locals_dict, DisjointSet_locals_dict_table);

// special functions
static mp_obj_t DisjointSet_unary_op(mp_unary_op_t op, mp_obj_t self_in) {
    DisjointSet_obj_t *self = MP_OBJ_TO_PTR(self_in);
    switch (op) {
        case MP_UNARY_OP_LEN:
            if(self->set == NULL) {
                return mp_obj_new_int(0);
            }
            return mp_obj_new_int(self->set->size);
        default: return MP_OBJ_NULL; // operator not supported
    }
}

static void DisjointSet_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    DisjointSet_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if(dest[0] != MP_OBJ_NULL) {
        // unsupported
        return;
    }

    if(attr == MP_QSTR_size) {
        mp_int_t size = 0;
        if(self->set != NULL) {
            size = self->set->size;
        }
        dest[0] = mp_obj_new_int(size);
        return;
    }

    if(attr == MP_QSTR_n_sets) {
        mp_int_t n_sets = 0;
        if(self->set != NULL) {
            n_sets = self->set->n_sets;
        }
        dest[0] = mp_obj_new_int(n_sets);
        return;
    }

    // continue lookup in locals_dict
    dest[1] = MP_OBJ_SENTINEL;
}

static mp_obj_t DisjointSet_subscr(mp_obj_t self_in, mp_obj_t index_in, mp_obj_t value_in) {
    DisjointSet_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_int_t index = mp_obj_get_int(index_in);

    if(value_in == MP_OBJ_NULL) {
        // unsupported
        return MP_OBJ_NULL;
    }
    
    if(value_in == MP_OBJ_SENTINEL) {
        // load
        mp_int_t result = -1;
        if(self->set != NULL) {
            index %= self->set->size;
            index += self->set->size;
            index %= self->set->size;
            result = self->set->data[index];
        }
        return mp_obj_new_int(result);
    }
    // store
    if(self->set == NULL) {
        return MP_OBJ_NULL;
    }
    mp_int_t value = mp_obj_get_int(value_in);
    index %= self->set->size;
    index += self->set->size;
    index %= self->set->size;
    self->set->data[index] = value;
    return mp_const_none;
}

// I use the polyiterator here. See https://github.com/micropython/micropython/blob/master/py/objrange.c
// for other customized iterators.
typedef struct _DisjointSet_iter_t {
    mp_obj_base_t base;
    mp_fun_1_t iternext;
    disjoint_set_t set;
    int cur;
} DisjointSet_iter_t;

static mp_obj_t DisjointSet_it_iternext(mp_obj_t self_in) {
    DisjointSet_iter_t *self = MP_OBJ_TO_PTR(self_in);
    disjoint_set_t set = self->set;
    if(set == NULL) {
        return MP_OBJ_STOP_ITERATION;
    }
    if (self->cur < set->size) {
        int value = set->data[self->cur];
        self->cur += 1;
        return mp_obj_new_int(value);
    } else {
        return MP_OBJ_STOP_ITERATION;
    }
}

static mp_obj_t DisjointSet_getiter(mp_obj_t self_in, mp_obj_iter_buf_t *iter_buf) {
    DisjointSet_obj_t *self = MP_OBJ_TO_PTR(self_in);
    assert(sizeof(DisjointSet_iter_t) <= sizeof(mp_obj_iter_buf_t));
    DisjointSet_iter_t *it = (DisjointSet_iter_t *)iter_buf;
    it->base.type = &mp_type_polymorph_iter;
    it->iternext = DisjointSet_it_iternext;
    it->set = self->set;
    it->cur = 0;

    return it;
}

// Declare the type object.
MP_DEFINE_CONST_OBJ_TYPE(
    type_DisjointSet,
    MP_QSTR_DisjointSet,
    MP_TYPE_FLAG_NONE,
    print, DisjointSet_print,
    make_new, DisjointSet_make_new,
    unary_op, DisjointSet_unary_op,
    attr, DisjointSet_attr,
    subscr, DisjointSet_subscr,
    iter, DisjointSet_getiter,
    locals_dict, &DisjointSet_locals_dict
);


// Finally, we make the module object.
// The symbol table.
static const mp_rom_map_elem_t disjoint_set_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_disjoint_set) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&disjoint_set_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_DisjointSet), MP_ROM_PTR(&type_DisjointSet) },
};

// Then, make the dict obj.
static MP_DEFINE_CONST_DICT(disjoint_set_module_globals, disjoint_set_module_globals_table);

// Then, the module obj.
const mp_obj_module_t disjoint_set_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&disjoint_set_module_globals,
};

// Register the module.
MP_REGISTER_MODULE(MP_QSTR_disjoint_set, disjoint_set_module);
