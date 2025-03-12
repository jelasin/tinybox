#include "cmd_cp.h"

int cp_handle(cmd_t *pcmd_t)
{
    if (0 == strcmp(pcmd_t->cmd_arg_list[0], "-h") && pcmd_t->cmd_arg_count == 1)
    {
        INFO("Usage: ");
        INFO("  cp [SOURCE] [DEST] : copy SOURCE to DEST");
    }
    else if (pcmd_t->cmd_arg_count != 2)
    {
        ERROR("[cp_handle] invalid args");
        return -1;
    }

    if (0 == strcmp(pcmd_t->cmd_arg_list[0], pcmd_t->cmd_arg_list[1]))
    {
        ERROR("[cp_handle] source and dest are the same");
        return -1;
    }
    
    cp_file_info_t file_info;
    int ret = parse_cp_args(pcmd_t, &file_info);
    if (0 != ret)
    {
        if (ret == -2)
        {
            WARN("[cp_handle] have a same file or dir name with %s, please check", pcmd_t->cmd_arg_list[1]);
            return -1;
        }
        else
        {
            ERROR("[cp_handle] parse cp args failed");
            return -1;
        }


    }
#if defined(DEBUG)
    INFO("[cp_handle] src_path: %s, dest_path: %s, src_ftype: %s", \
        file_info.src_path, file_info.dest_path, \
        file_info.src_ftype == FT_FILE ? "file" : (file_info.src_ftype == FT_DIR ? "dir" : "unknown"));
#endif
    if (file_info.src_ftype == FT_FILE)
    {
        ret = cp_file(file_info.src_path, file_info.dest_path);
    }
    else if (file_info.src_ftype == FT_DIR)
    {
        ret = cp_dir(file_info.src_path, file_info.dest_path);
    }
    else
    {
        ERROR("[cp_handle] not supported file type of %s", file_info.src_path);
        return -1;
    }

    if (0 != ret)
    {
        ERROR("[cp_handle] cp %s to %s failed, %s", file_info.src_path, file_info.dest_path, strerror(errno));
        return -1;
    }

    return 0;
}

int parse_cp_args(cmd_t *pcmd_t, cp_file_info_t *pfile_info)
{

    if (pcmd_t == NULL)
    {
        ERROR("[parse_cp_args] invalid args");
        return -1;
    }
    
    pfile_info->src_ftype = get_file_type(pcmd_t->cmd_arg_list[0], true);
    if (pfile_info->src_ftype == FT_ERROR)
    {
        ERROR("[parse_cp_args] get file type of %s failed", pcmd_t->cmd_arg_list[0]);
        return -1;
    }
    // if dest_file have a same name file return -2
    int check_dest_path = get_file_type(pcmd_t->cmd_arg_list[1], false);
    if (check_dest_path != FT_ERROR)
    {
        WARN("[parse_cp_args] have a same file or dir name with %s", pcmd_t->cmd_arg_list[1]);
        return -2;
    }

    strncpy(pfile_info->src_path, pcmd_t->cmd_arg_list[0], SZ_PATH-1);
    strncpy(pfile_info->dest_path, pcmd_t->cmd_arg_list[1], SZ_PATH-1);

    return 0;
}

int cp_file(char *src_path, char *dest_path)
{
    if (src_path == NULL || dest_path == NULL)
    {
        ERROR("[cp_file] invalid args");
        return -1;
    }
#if defined(DEBUG)
    INFO("[cp_file] src_path: %s, dest_path: %s", src_path, dest_path);
#endif

    FILE *fp_src = fopen(src_path, "rb");
    FILE *fp_dest = fopen(dest_path, "wb");
    if (fp_src == NULL || fp_dest == NULL)
    {
        ERROR("[cp_file] open file %s or %s failed, %s", src_path, dest_path, strerror(errno));
        return -1;
    }

    const int BUF_SIZE = 1024;

    char buf[BUF_SIZE];
    int len = 0;
    while ((len = fread(buf, 1, BUF_SIZE, fp_src)) > 0)
    {
        if (fwrite(buf, 1, len, fp_dest) != len)
        {
            ERROR("[cp_file] write file %s failed, %s", dest_path, strerror(errno));
            fclose(fp_src);
            fclose(fp_dest);
            return -1;
        }
    }

    fclose(fp_src);
    fclose(fp_dest);

    return 0;
}

int cp_dir(char *src_path, char *dest_path)
{
    if (src_path == NULL || dest_path == NULL)
    {
        ERROR("[cp_dir] invalid args");
        return -1;
    }

    int ret = 0;
    enum file_type ftype = get_file_type(src_path, true);

    if (ftype != FT_DIR && ftype != FT_FILE)
    {
        ERROR("[cp_dir] #1 get file type of %s failed", src_path);
#if defined(DEBUG)
        ERROR("[cp_dir] ftype: %d -> %s", \
            ftype,\
            ftype == FT_FILE ? "file" : (ftype == FT_DIR ? "dir" : "other"));
#endif
        return -1;
    }

    if (ftype == FT_FILE)
    {
        ret = cp_file(src_path, dest_path);
    }
    else if (ftype == FT_DIR)
    {
#if defined(DEBUG)
        INFO("[cp_dir] src_path: %s, dest_path: %s", src_path, dest_path);
#endif
        ret = mkdir(dest_path, 0777); // dest_path is a dir
        if (ret != 0)
        {
            if (errno != EEXIST)
            {
                ERROR("[cp_dir] mkdir %s failed, %s", dest_path, strerror(errno));
                return -1;
            }
            else
            {
                WARN("[cp_dir] %s already exist", dest_path);
                return -1;
            }
        }

        DIR *pdir_src = opendir(src_path);
        if (pdir_src == NULL)
        {
            ERROR("[cp_dir] open dir %s failed, %s", src_path, strerror(errno));
            return -1;
        }

        struct dirent *pdirent = NULL;

        while(true)
        {
            pdirent = readdir(pdir_src);
            if (pdirent == NULL)
            {
                break;
            }

            if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
            {
                continue;
            }

            char src_file_path[SZ_PATH];
            char dest_file_path[SZ_PATH];
            snprintf(src_file_path, SZ_PATH-1, "%s/%s", src_path, pdirent->d_name);
            snprintf(dest_file_path, SZ_PATH-1, "%s/%s", dest_path, pdirent->d_name);

            enum file_type ftype = get_file_type(src_file_path, true);
            if (ftype != FT_DIR && ftype != FT_FILE)
            {
                ERROR("[cp_dir] #2 get file type of %s failed", src_file_path);
#if defined(DEBUG)
                ERROR("[cp_dir] ftype: %d -> %s", \
                    ftype,\
                    ftype == FT_FILE ? "file" : (ftype == FT_DIR ? "dir" : "other"));
#endif
                ret = -1;
                break;
            }

            if (ftype == FT_FILE)
            {
                ret = cp_file(src_file_path, dest_file_path);
            }
            else if (ftype == FT_DIR)
            {
                ret = cp_dir(src_file_path, dest_file_path); // recursive call cp_dir to make sub_dir
            }
        }
        closedir(pdir_src);
    }

    return 0;
}