#include "cmd_pwd.h"

int pwd_handle()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        ERROR("[pwd_handle] Failed to get current working directory, failed %s", strerror(errno));
        return -1;
    }
    fprintf(stderr, "%s\n", cwd);
    return 0;
}