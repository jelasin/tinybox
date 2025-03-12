#include "cmd_rm.h"

int rm_handle(cmd_t *pcmd_t)
{
    if (pcmd_t->cmd_arg_count == 0 || 0 == strcmp(pcmd_t->cmd_arg_list[0], "-h")) 
    {
        INFO("Usage: rm <file1/dir1> <file2/dir2>...");
        return -1;
    }

    if (0 != rm_execute(pcmd_t))
    {
        ERROR("Failed to remove files/directories");
        return -1;
    }
    return 0;
}

int rm_file(const char *path)
{
    if (path == NULL)
    {
        ERROR("[rm_file] Invalid path");
        return -1;
    }
    if (0 != unlink(path))
    {
        ERROR("[rm_file] Failed to remove file: %s", path);
        return -1;
    }
    return 0;
}

int rm_dir(const char *path)
{
    if (path == NULL)
    {
        ERROR("[rm_dir] Invalid path");
        return -1;
    }
    
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        ERROR("[rm_dir] Failed to open directory: %s", path);
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        char sub_path[PATH_MAX];
        snprintf(sub_path, PATH_MAX, "%s/%s", path, entry->d_name);
        enum file_type type = get_file_type(sub_path, false);
        if (type != FT_DIR && type != FT_UNKNOWN && type != FT_ERROR)
        {
            if (0 != rm_file(sub_path))
            {
                ERROR("[rm_dir] Failed to remove file: %s", sub_path);
                return -1;
            }
        }
        else if (type == FT_DIR)
        {
            if (0 != rm_dir(sub_path))
            {
                ERROR("[rm_dir] Failed to remove directory: %s", sub_path);
                return -1;
            }
        }
        else
        {
            ERROR("[rm_dir] Can not remove file :%s", sub_path);
        }
    }
    if (0 != closedir(dir))
    {
        ERROR("[rm_dir] Failed to close directory: %s", path);
        return -1;
    }

    if (0 != rmdir(path))
    {
        ERROR("[rm_dir] Failed to remove directory: %s", path);
        return -1;
    }
    
    return 0;
}

int rm_execute(cmd_t *pcmd_t)
{
    for (int i = 0; i < pcmd_t->cmd_arg_count; i++)
    {
        enum file_type type = get_file_type(pcmd_t->cmd_arg_list[i], false);
        if (type != FT_DIR && type != FT_UNKNOWN && type != FT_ERROR)
        {
            if (0 != rm_file(pcmd_t->cmd_arg_list[i]))
            {
                ERROR("[rm_handle] Failed to remove file: %s", pcmd_t->cmd_arg_list[i]);
                return -1;
            }
        }
        else if (type == FT_DIR)
        {
            if (0 != rm_dir(pcmd_t->cmd_arg_list[i]))
            {
                ERROR("[rm_handle] Failed to remove directory: %s", pcmd_t->cmd_arg_list[i]);
                return -1;
            }
        }
        else
        {
            ERROR("[rm_handle] Can not remove file :%s", pcmd_t->cmd_arg_list[i]);
            return -1;
        }
    }
    return 0;
}