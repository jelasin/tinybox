#include "cmd_pwd.h"

int pwd_handle(cmd_t *pcmd_t)
{
    pwd_execute(pcmd_t);
    return 0;
}

int pwd_execute(cmd_t *pcmd_t)
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