#include <EWL/System/cpu.hpp>
#include <EWL/System/memory.hpp>

#include <iostream>

#include <string.h>

void ewl::cpu::cpuid(ewl::uint32_t id, ewl::uint32_t regs[4]) {
    asm volatile
    (
        "cpuid"
        :   "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3])
        :   "a"(id), "c"(0)
    );
}

std::string ewl::cpu::getVendor() {

    ewl::uint32_t regs[4];
    char vendor[12];

    ewl::cpu::cpuid(ewl::cpu::input::VENDOR, regs);

    ((ewl::uint32_t*)vendor)[0] = regs[1];
    ((ewl::uint32_t*)vendor)[1] = regs[3];
    ((ewl::uint32_t*)vendor)[2] = regs[2];

    return std::string(vendor,12);
}

std::string ewl::cpu::getName() {

    std::string name;

    for(ewl::uint32_t i = 0; i < 3; i++) {
        ewl::uint32_t regs[4];

        ewl::cpu::cpuid(ewl::cpu::input::PROC_NAME_1+i,regs);

        char filtered[sizeof regs] = {0};

        filtered[ewl::memory::filterByRange(regs,filtered,sizeof regs,(const ewl::uint8_t[2]){32,127},1)] = 0;

        name += filtered;
    }

    return name;

}

ewl::uint32_t ewl::cpu::surroundingCycles() {

    
    ewl::uint32_t num;

    asm volatile
    #include "cpu.asm"

    return num;


}