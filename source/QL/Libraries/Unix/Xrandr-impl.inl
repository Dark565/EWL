#include "Xrandr.hpp"

namespace impl

bool G_Xrandr_lib_load() {

    ql::native::libraryData* l_data = ql::native::getLibraryData(ql::native::tags::Xrandr);
    ql::Library* obj = &l_data->object;
    Xrandr_Functions_Set* fs = (Xrandr_Functions_Set*)l_data->data;

    if(!obj->isLegit)

}