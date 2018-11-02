#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>

ewl::platform::id_t ewl::platform::runProgram(const std::string &path, const std::vector<std::string> &args)
{
    ewl::platform::id_t pid;
    if (!(pid = fork()))
    {
        const char **str = (const char **)malloc(sizeof(const char *) * (args.size() + 1));
        for (ewl::uint32_t i = 0; i < args.size(); i++)
        {
            str[i] = args[i].c_str();
        }
        str[args.size() + 1] = NULL;
        execvp(path.c_str(), (char *const *)str);
    }
    return pid;
}

ewl::platform::id_t ewl::platform::getCurrProcessPID()
{
    return getpid();
}

ewl::platform::id_t ewl::platform::getCurrUserID()
{
    return getuid();
}

ewl::platform::id_t ewl::platform::getUserID(const std::string &str)
{
    passwd *pw = getpwnam(str.c_str());
    int r = pw->pw_uid;
    return r;
}

bool ewl::platform::changeCurrentDir(const std::string& dir) {
    return !chdir(dir.c_str());
}

std::string ewl::platform::getHomeDir(ewl::platform::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_dir;

    return rets;
}

std::string ewl::platform::getCurrentDir()
{
    char buf[1024];
    buf[0] = 0;
    getcwd(buf, sizeof(buf));
    return std::string(buf);
}

std::string ewl::platform::getUsername(ewl::platform::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_name;
    return rets;
}

std::string ewl::platform::getHostname()
{
    char buf[1024];
    buf[0] = 0;
    gethostname(buf, sizeof(buf));
    return std::string(buf);
}

std::string ewl::platform::getShell()
{
    passwd *pw = getpwuid(ewl::platform::getCurrUserID());
    std::string rets = pw->pw_shell;
    return rets;
}

ewl::Thread::id_t ewl::this_thread::getID()
{
    return pthread_self();
}

void ewl::this_thread::sleep(ewl::Time s_t)
{
    usleep(s_t.getUS().t);
}

ewl::uint32_t ewl::platform::getCPUsCount()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}