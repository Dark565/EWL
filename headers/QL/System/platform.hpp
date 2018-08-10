#pragma once

#include <QL/System/Time/units.hpp>
#include <QL/System/thread.hpp>
#include <QL/Definitions/defs.hpp>

#include <string>
#include <QL/Definitions/int.hpp>
#include <vector>
#include <csignal>

namespace ql {
    namespace platform {

        typedef uint32_t id_t;

        const static id_t root_uid = 0;

        /*Opens program*/
        id_t runProgram(const std::string& path, const std::vector<std::string>& args = std::vector<std::string>());

        /*Gets ID of current user*/
        id_t getCurrUserID();

        /*Gets user ID by name*/
        id_t getUserID(const std::string& str);

        /*Gets process ID of current process*/
        id_t getCurrProcessPID();

        /*Gets directory of current program*/
        std::string getProgramDir();

        /*Gets home dir of user*/
        std::string getHomeDir(id_t id);

        /*Gets user name by ID*/
        std::string getUsername(id_t id);

        /*Gets name of the host*/
        std::string getHostname();

        /*Only unix, Windows users :P*/
        #if defined __QL_UNIX

        std::string getShell();
        
        #endif

    }

    namespace this_thread {

        /*Gets id of current thread*/
        Thread::id_t getID();

        /*Sleeps thread for taken microseconds*/
        void sleep(Time s_t);
    }
}