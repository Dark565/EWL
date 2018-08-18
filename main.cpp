#include <QL/System/cpu.hpp>
#include <QL/System/platform.hpp>
#include <QL/Definitions/Objects/array.hpp>

#include <iostream>
#include <stdlib.h>



int main() {

    std::cout << ql::cpu::getName() << '\n';   
}