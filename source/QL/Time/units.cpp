#include <QL/Time/units.hpp>

ql::Time& ql::Time::operator=(const ql::Time::us& a) {
    t = a.t * 1000;
}

ql::Time& ql::Time::operator=(const ql::Time::ms& a) {
    t = a.t * 1000000;
}

ql::Time& ql::Time::operator=(const ql::Time::sec& a) {
    t = a.t * 1000000000;
}

ql::Time::us ql::Time::getUS() {
    return t / 1000;
}

ql::Time::ms ql::Time::getMS() {
    return t / 1000000;
}

ql::Time::sec ql::Time::getSEC() {
    return (double)t / 1000000000;
}

ql::Time::Time(const ql::Time::us& a) {
    *this = a;
}

ql::Time::Time(const ql::Time::ms& a) {
    *this = a;
}

ql::Time::Time(const ql::Time::sec& a) {
    *this = a;
}