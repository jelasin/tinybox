#include "cmd_ls.h"

int ls_handle(cmd_t *pcmd_t)
{
    if (pcmd_t->cmd_arg_count == 1 && 0 == strcmp(pcmd_t->cmd_arg_list[0], "-h"))
    {
        INFO("Usage: ls [FILE]...");
        INFO("List information about the FILEs (the current directory by default).");
        INFO("  -h  display this help and exit");
        return 0;
    }
    if (0 == pcmd_t->cmd_arg_count)
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, PATH_MAX) == NULL)
        {
            ERROR("[ls_handle] Failed to get current working directory, failed %s", strerror(errno));
            return -1;
        }
        if (0 != ls_print_dir(cwd))
        {
            ERROR("[ls_handle] Failed to list directory %s", cwd);
            return -1;
        }
    }
    else
    {
        for (int i = 0; i < pcmd_t->cmd_arg_count; i++)
        {
            enum file_type type = get_file_type(pcmd_t->cmd_arg_list[i], false);
            if (type == FT_DIR)
            {
                if (0 != ls_print_dir(pcmd_t->cmd_arg_list[i]))
                {
                    ERROR("[ls_handle] Failed to list directory %s", pcmd_t->cmd_arg_list[i]);
                    return -1;
                }
            }
            else if (type == FT_FILE || type == FT_UNKNOWN)
            {
                if (0 != ls_print_file(pcmd_t->cmd_arg_list[i]))
                {
                    ERROR("[ls_handle] Failed to list file %s", pcmd_t->cmd_arg_list[i]);
                    return -1;
                }
            }
            else
            {
                ERROR("[ls_handle] Unknown file type %d for %s", type, pcmd_t->cmd_arg_list[i]);
                return -1;
            }
            
        }
    }
    return 0;
}

int ls_print_file(const char* path)
{
    return 0;
}

int ls_print_dir(const char* path)
{
    return 0;
}

