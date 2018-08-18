#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>

ql::platform::id_t ql::platform::runProgram(const std::string &path, const std::vector<std::string> &args)
{
    ql::platform::id_t pid;
    if (!(pid = fork()))
    {
        const char **str = (const char **)malloc(sizeof(const char *) * (args.size() + 1));
        for (ql::uint32_t i = 0; i < args.size(); i++)
        {
            str[i] = args[i].c_str();
        }
        str[args.size() + 1] = NULL;
        execvp(path.c_str(), (char *const *)str);
    }
    return pid;
}

ql::platform::id_t ql::platform::getCurrProcessPID()
{
    return getpid();
}

ql::platform::id_t ql::platform::getCurrUserID()
{
    return getuid();
}

ql::platform::id_t ql::platform::getUserID(const std::string &str)
{
    passwd *pw = getpwnam(str.c_str());
    int r = pw->pw_uid;
    return r;
}

bool ql::platform::changeCurrentDir(const std::string& dir) {
    return !chdir(dir.c_str());
}

std::string ql::platform::getHomeDir(ql::platform::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_dir;

    return rets;
}

std::string ql::platform::getCurrentDir()
{
    char buf[1024];
    buf[0] = 0;
    getcwd(buf, sizeof(buf));
    return std::string(buf);
}

std::string ql::platform::getUsername(ql::platform::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_name;
    return rets;
}

std::string ql::platform::getHostname()
{
    char buf[1024];
    buf[0] = 0;
    gethostname(buf, sizeof(buf));
    return std::string(buf);
}

std::string ql::platform::getShell()
{
    passwd *pw = getpwuid(ql::platform::getCurrUserID());
    std::string rets = pw->pw_shell;
    return rets;
}

ql::Thread::id_t ql::this_thread::getID()
{
    return pthread_self();
}

void ql::this_thread::sleep(ql::Time s_t)
{
    usleep(s_t.getUS().t);
}

ql::uint32_t ql::platform::getCPUsCount()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}