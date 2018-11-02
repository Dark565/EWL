#include "Xrandr.hpp"

namespace impl

bool G_Xrandr_lib_load() {

    ewl::native::libraryData* l_data = ewl::native::getLibraryData(ewl::native::tags::Xrandr);
    ewl::Library* obj = &l_data->object;
    Xrandr_Functions_Set* fs = (Xrandr_Functions_Set*)l_data->data;

    if(!obj->isLegit)

}