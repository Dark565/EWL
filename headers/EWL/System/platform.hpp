#pragma once

#include <EWL/System/Time/units.hpp>
#include <EWL/System/thread.hpp>

#include <string>
#include <EWL/Definitions/int.hpp>
#include <vector>
#include <csignal>

namespace ewl {
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

        /*Gets count of logical CPUs*/
        uint32_t getCPUsCount();

        /*Sets current working dir*/
        bool changeCurrentDir(const std::string& dir);

        /*Gets current working dir*/
        std::string getCurrentDir();

        /*Gets home dir of user*/
        std::string getHomeDir(id_t id);

        /*Gets user name by ID*/
        std::string getUsername(id_t id);

        /*Gets name of the host*/
        std::string getHostname();

        /*Gets shell*/
        std::string getShell();
    
    }

    namespace this_thread {

        /*Gets id of current thread*/
        Thread::id_t getID();

        /*Sleeps thread for taken microseconds*/
        void sleep(Time s_t);
    }
}