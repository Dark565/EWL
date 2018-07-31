#include <QL/System/platform.hpp>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <pthread.h>

ql::id_t ql::platform::runProgram(const std::string &path, const std::vector<std::string> &args)
{
    ql::id_t pid;
    if (!(pid = fork()))
    {
        const char **str = (const char **)malloc(sizeof(const char *) * (args.size() + 1));
        for (ql::uint32_t i = 0; i < args.size(); i++)
        {
            str[i] = args[i].c_str();
        }
        str[args.size() + 1] = NULL;
        printf("%i", execvp(path.c_str(), (char *const *)str));
    }
    return pid;
}

ql::id_t ql::platform::getCurrProcessPID()
{
    return getpid();
}

ql::id_t ql::platform::getCurrUserID()
{
    return getuid();
}

ql::id_t ql::platform::getUserID(const std::string &str)
{
    passwd *pw = getpwnam(str.c_str());
    int r = pw->pw_uid;
    free(pw);
    return r;
}

std::string ql::platform::getHomeDir(ql::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_dir;
    free(pw);

    return rets;
}

std::string ql::platform::getProgramDir()
{
    char buf[1024];
    buf[0] = 0;
    getcwd(buf, sizeof(buf));
    return std::string(buf);
}

std::string ql::platform::getUsername(ql::id_t id)
{
    passwd *pw = getpwuid(id);
    std::string rets = pw->pw_name;
    free(pw);
    return rets;
}

std::string ql::platform::getHostname()
{
    char buf[1024];
    buf[0] = 0;
    gethostname(buf, sizeof(buf));
    return std::string(buf);
}

#if defined __QL_UNIX
std::string ql::platform::getShell()
{
    passwd *pw = getpwuid(ql::platform::getCurrUserID());
    std::string rets = ps;
    free(pw);
    return rets;
}
#endif

ql::id_t ql::this_thread::getID()
{
    return pthread_self();
}

void ql::this_thread::sleep(ql::Time s_t)
{
    usleep(s_t.getUS().t);
}
