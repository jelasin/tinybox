#include "cmd_cd.h"

// global variable to store recent directory
char g_recent_path[MAX_CMD_LEN] = "";

int cd_handle(cmd_t *pcmd_t)
{
    if (pcmd_t->cmd_arg_count == 2 && 0 == strcmp(pcmd_t->cmd_arg_list[0], "-h"))
    {
        INFO("Usage: ");
        INFO("       cd <directory> : change to specified directory");
        INFO("       cd - : change to previous directory");
        INFO("       cd ~ : change to home directory");
        INFO("       cd -h: show help message");
        return 0;
    }
    else if (pcmd_t->cmd_arg_count > 1)
    {
        ERROR("[cd_handle] Too many arguments for cd command");
        return -1;
    }
    
    if (0 != strcmp(pcmd_t->cmd_arg_list[0], "-") && 0 != strcmp(pcmd_t->cmd_arg_list[0], "~") && get_file_type(pcmd_t->cmd_arg_list[0], false) != FT_DIR)
    {
        ERROR("[cd_handle] Not a directory: %s\n", pcmd_t->cmd_arg_list[0]);
        return -1;
    }

    if (0 != cd_execute(pcmd_t))
    {
        ERROR("[cd_handle] Failed to execute cd command");
        return -1;
    }
    return 0;
}
int cd_execute(cmd_t *pcmd_t)
{
    char cur_dir[PATH_MAX];
    if (getcwd(cur_dir, PATH_MAX) == NULL)
    {
        ERROR("[cd_handle] Failed to get current directory: %s", strerror(errno));
        return -1;
    }
#if defined(DEBUG)
    INFO("[cmd_cd] g_recent_path: %s", g_recent_path);
#endif
    if (0 == pcmd_t->cmd_arg_count || 0 == strcmp(pcmd_t->cmd_arg_list[0], "~"))
    {
        char *home = getenv("HOME");
        if (home == NULL)
        {
#if defined(DEBUG)
            WARN("[cd_handle] Failed to get HOME environment variable, return to '/'\n");
#endif
            if (chdir("/") == -1) // change to root directory
            {   
                ERROR("[cd_handle] Failed to change directory to /: %s", strerror(errno));
                return -1;
            }
            return 0;
        }
        if (chdir(home) == -1) // change to home directory
        {
            ERROR("[cd_handle] Failed to change directory to %s: %s", home, strerror(errno));
            return -1;
        }
        INFO("[cd_handle] Changed to directory: %s", home);
        strncpy(g_recent_path, cur_dir, MAX_CMD_LEN-1); // update recent directory
        return 0;
    }

    if (0 == strcmp(pcmd_t->cmd_arg_list[0], "-"))
    {
#if defined(DEBUG)
    INFO("[cd_handle] change to g_recent_path: %s", g_recent_path);
#endif
        char *oldpwd = g_recent_path;
        if (strlen(oldpwd) == 0)
        {
            ERROR("[cd_handle] No recent directory\n");
            return -1;
        }
        if (chdir(oldpwd) == -1) // change to recent directory
        {
            ERROR("[cd_handle] Failed to change directory to %s: %s", oldpwd, strerror(errno));
            return -1;
        }
        INFO("Changed to directory: %s", oldpwd);
        strncpy(g_recent_path, cur_dir, MAX_CMD_LEN-1); // update recent directory
        return 0;
    } 

    char *dir = pcmd_t->cmd_arg_list[0];
    if (chdir(dir) == -1) // change to specified directory
    {
        ERROR("[cd_handle] Failed to change directory to %s: %s", dir, strerror(errno));
        return -1;
    }
    INFO("[cd_handle] Changed to directory: %s", dir);
    strncpy(g_recent_path, cur_dir, MAX_CMD_LEN-1); // update recent directory
    return 0;
}