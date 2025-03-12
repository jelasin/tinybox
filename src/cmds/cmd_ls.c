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

    if (0 != ls_execute(pcmd_t))
    {
        ERROR("[ls_handle] Failed to execute ls command");
        return -1;
    }

    return 0;
}

int ls_print_file(const char* path)
{
    file_attribute_t file_t;
    if (0 != get_file_attribute(path, &file_t))
    {
        ERROR("[ls_print_file] Failed to get file attribute for %s", path);
        return -1;
    }
    fprintf(stderr, "%c %s %s %s %s %s %s %s %s\n",
        file_t.f_attr_type, file_t.f_attr_permission, file_t.f_attr_nlink,
        file_t.f_attr_uname, file_t.f_attr_gname, file_t.f_attr_size,
        file_t.f_attr_mtime, file_t.f_attr_name, file_t.f_attr_link_content);
    return 0;
}

int ls_print_dir(const char* path)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) == NULL)
    {
        ERROR("[ls_print_dir] Failed to open directory %s, failed %s", path, strerror(errno));
        return -1;
    }
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        {
            continue;
        }
        char file_path[PATH_MAX];
        snprintf(file_path, PATH_MAX, "%s/%s", path, ent->d_name);
        file_attribute_t file_t;
        if (0 != get_file_attribute(file_path, &file_t))
        {
            ERROR("[ls_print_dir] Failed to get file attribute for %s", file_path);
            return -1;
        }
        fprintf(stderr, "%c %s %s %s %s %s %s %s %s\n",
            file_t.f_attr_type, file_t.f_attr_permission, file_t.f_attr_nlink,
            file_t.f_attr_uname, file_t.f_attr_gname, file_t.f_attr_size,
            file_t.f_attr_mtime, file_t.f_attr_name, file_t.f_attr_link_content);
    }
    return 0;
}

int ls_execute(cmd_t *pcmd_t)
{
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
            else if (type != FT_DIR && type != FT_ERROR && type != FT_UNKNOWN)
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