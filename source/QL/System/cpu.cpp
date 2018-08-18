#include <QL/System/cpu.hpp>
#include <QL/System/memory.hpp>

#include <iostream>

#include <string.h>

void ql::cpu::cpuid(ql::uint32_t id, ql::uint32_t regs[4]) {
    asm volatile
    (
        "cpuid"
        :   "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3])
        :   "a"(id), "c"(0)
    );
}

std::string ql::cpu::getVendor() {

    ql::uint32_t regs[4];
    char vendor[12];

    ql::cpu::cpuid(ql::cpu::input::VENDOR, regs);

    ((ql::uint32_t*)vendor)[0] = regs[1];
    ((ql::uint32_t*)vendor)[1] = regs[3];
    ((ql::uint32_t*)vendor)[2] = regs[2];

    return std::string(vendor,12);
}

std::string ql::cpu::getName() {

    std::string name;

    for(ql::uint32_t i = 0; i < 3; i++) {
        ql::uint32_t regs[4];

        ql::cpu::cpuid(ql::cpu::input::PROC_NAME_1+i,regs);

        char filtered[sizeof regs] = {0};

        filtered[ql::memory::filterByRange(regs,filtered,sizeof regs,(const ql::uint8_t[2]){32,127},1)] = 0;

        name += filtered;
    }

    return name;

}