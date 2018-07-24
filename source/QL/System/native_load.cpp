#include <QL/System/native_load.hpp>

#include "../dynamic_loads_ut.hpp"

bool ql::native::load(uint32_t tag) {
    switch(tag) {
        case 0:     return M0::load();
        case 1:     return M1::load();
    }
}

bool ql::native::unload(uint32_t tag) {
    switch(tag) {
        case 0:     return M0::unload();
        case 1:     return M1::unload();
    }
}