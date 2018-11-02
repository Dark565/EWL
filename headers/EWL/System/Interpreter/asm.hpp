#pragma once

#include <fstream>

namespace ewl {
    namespace interpreter {
        namespace assembly {
            typedef enum {
                MOV,
                ADD,
                XOR,
                LEA,
                OR,
                AND,
                OUT,
                IN,
                DIV,
                INT,
                PUSH,
                POP,
                CALL,
                RET,
                JMP,
                JZ,
                JE,
                JNZ,
                JNE,
                JA,
                JNBE,
                JB,
                JNAE,
                JC,
                JNB,
                JAE,
                JG,
                JNLE,
                JNG,
                JLE,
                JL,
                JNGE,
                JN,
                JGE,
                JCZX,
                JECXZ,
                JP,
                JNP,
                JS,
                JNS


            } instructions;

            typedef enum {
                INS,
                NUM,
                REG,
                CREG
            } args;

            class Register {
                
            };

            class RegisterTab {

            };

            struct Argument {
                char TYPE;

                virtual int32_t getValue();

                Argument(char TYPE_ARG) : TYPE(TYPE_ARG) {};
            };

            struct Instruction : public Argument {
                instructions ins;

                virtual int32_t getValue();

                Instruction() : Argument(args::INS) {}
            };

            struct Number : public Argument {
                uint32_t n;

                virtual int32_t getValue();

                Number() : Argument(args::NUM) {}
            };

            struct Indentifier : public Argument {
                Register* reg;

                virtual int32_t getValue();

                Indentifier() : Argument(args::REG) {}
            };

            struct ClosedIdentifier : public Argument {
                Register* reg;

                virtual int32_t getValue();

                ClosedIdentifier() : Argument(args::CREG) {}
            };

            class Command {
                void(*DoCommand)(RegisterTab* tb, std::vector<Argument*>* arg_tab);
                std::vector<Argument*> args;
            };

            class Parser {
                std::vector<Command> commands;
            public:
                Argument* parse();



                
                bool loadFromMemory(const char* mem);
                bool loadFromFile(const char* path);
            };
        }
    }
}