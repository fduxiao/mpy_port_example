#include <py/builtin.h>
#include <py/runtime.h>
#include <py/obj.h>
#include "core.h"

// functions

// info
static mp_obj_t disjoint_set_info(void) {
    mp_printf(&mp_plat_print, "disjoint set\n");
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(disjoint_set_info_obj, disjoint_set_info);


// Register them in the table.
static const mp_rom_map_elem_t disjoint_set_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_disjoint_set) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&disjoint_set_info_obj) },
};

// Then, make the dict obj.
static MP_DEFINE_CONST_DICT(disjoint_set_module_globals, disjoint_set_module_globals_table);

// Then, the module obj.
const mp_obj_module_t disjoint_set_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&disjoint_set_module_globals,
};

// Finally, register the module.
MP_REGISTER_MODULE(MP_QSTR_disjoint_set, disjoint_set_module);
