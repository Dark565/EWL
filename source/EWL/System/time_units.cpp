#include <EWL/System/Time/units.hpp>

ewl::Time& ewl::Time::operator=(const ewl::Time::us& a) {
    t = a.t * 1000;
    return *this;
}

ewl::Time& ewl::Time::operator=(const ewl::Time::ms& a) {
    t = a.t * 1000000;
    return *this;
}

ewl::Time& ewl::Time::operator=(const ewl::Time::sec& a) {
    t = a.t * 1000000000;
    return *this;
}

ewl::Time::us ewl::Time::getUS() {
    return t / 1000;
}

ewl::Time::ms ewl::Time::getMS() {
    return t / 1000000;
}

ewl::Time::sec ewl::Time::getSEC() {
    return (double)t / 1000000000;
}

ewl::Time::Time(const ewl::Time::us& a) {
    *this = a;
}

ewl::Time::Time(const ewl::Time::ms& a) {
    *this = a;
}

ewl::Time::Time(const ewl::Time::sec& a) {
    *this = a;
}
