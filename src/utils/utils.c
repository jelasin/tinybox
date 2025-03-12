#include "utils.h"

enum file_type get_file_type(const char *path, bool flag)
{
    if (path == NULL)
    {
        if (flag) ERROR("[get_file_type] invalid args");
        return FT_ERROR;
    }

    struct stat st;
    int ret = lstat(path, &st);
    if (ret != 0)
    {
        if (ret == ENOENT)
        {     
            if (flag) ERROR("[get_file_type] %s not exist", path);
            return FT_ERROR;
        }
        else
        {
            if (flag) ERROR("[get_file_type] stat %s failed, %s", path, strerror(errno));
            return FT_ERROR;
        }
    }

    if (S_ISREG(st.st_mode))
    {
        return FT_FILE;
    }
    else if (S_ISDIR(st.st_mode))
    {
        return FT_DIR;
    }
    else if (S_ISLNK(st.st_mode))
    {
        return FT_LINK;
    }
    else if (S_ISFIFO(st.st_mode))
    {
        return FT_FIFO;
    }
    else if (S_ISSOCK(st.st_mode))
    {
        return FT_SOCKET;
    }
    else if (S_ISCHR(st.st_mode))
    {
        return FT_CHAR;
    }
    else if (S_ISBLK(st.st_mode))
    {
        return FT_BLOCK;
    }
    else
    {
        if (flag) ERROR("[get_file_type] unknown file type: %s", path);
        return FT_UNKNOWN;
    }
}

int get_file_attribute(const char *path, file_attribute_t* pf_attr_t)
{
    if (path == NULL)
    {
        ERROR("[get_file_attribute] invalid args");
        return -1;
    }
    
    struct stat st;
    if (0 != lstat(path, &st))
    {
        ERROR("[get_file_attribute] lstat %s failed, %s", path, strerror(errno));
        return -1;
    }
    pf_attr_t->f_attr_stat_info = st;

    if (0 != f_get_file_type(path, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file type failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_permisson(&st, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file permission failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_link_content(path, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file link content failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_owner(pf_attr_t))
    {
        ERROR("[get_file_attribute] get file owner failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_group(pf_attr_t))
    {
        ERROR("[get_file_attribute] get file group failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_size(&st, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file size failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_mtime(&st, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file mtime failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_name(path, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file name failed: %s", path);
        return -1;
    }
    if (0 != f_get_file_nlink(&st, pf_attr_t))
    {
        ERROR("[get_file_attribute] get file nlink failed: %s", path);
        return -1;
    }

    return 0;
}

int f_get_file_name(const char *path, file_attribute_t* pf_attr_t)
{
    char* f_name = strrchr(path, '/');
    if (NULL == f_name)
    {
        f_name = (char*)path;
    }
    else
    {
        f_name++;
    }
    strncpy(pf_attr_t->f_attr_name, f_name, SZ_FILE_NAME-1);
    return 0;
}

int f_get_file_type(const char *path, file_attribute_t* pf_attr_t)
{
    enum file_type type = get_file_type(path, false);
    if (type == FT_ERROR || type == FT_UNKNOWN)
    {
        ERROR("[get_file_attribute] get file type failed: %s", path);
        return -1;
    }

    switch (type)
    {
    case FT_FILE:
        pf_attr_t->f_attr_type = 'f';
        break;
    
    case FT_DIR:
        pf_attr_t->f_attr_type = 'd';
        break;
    
    case FT_LINK:
        pf_attr_t->f_attr_type = 'l';
        break;
    
    case FT_FIFO:
        pf_attr_t->f_attr_type = 'p';
        break;
    
    case FT_SOCKET:
        pf_attr_t->f_attr_type = 'S';
        break;
    
    case FT_CHAR:
        pf_attr_t->f_attr_type = 'c';
        break;
    
    case FT_BLOCK: 
        pf_attr_t->f_attr_type = 'b';
        break;
    
    default:
        ERROR("[f_get_file_type] unknown file type: %s", path);
        return -1;
    }

    return 0;
}

int f_get_file_permisson(const struct stat *st, file_attribute_t* pf_attr_t)
{
    pf_attr_t->f_attr_stat_info = *st;
    // get permission
    pf_attr_t->f_attr_permission[0] = (st->st_mode & S_IRUSR) ? 'r' : '-';
    pf_attr_t->f_attr_permission[1] = (st->st_mode & S_IWUSR) ? 'w' : '-';
    pf_attr_t->f_attr_permission[2] = (st->st_mode & S_IXUSR) ? 'x' : '-';
    pf_attr_t->f_attr_permission[3] = (st->st_mode & S_IRGRP) ? 'r' : '-';
    pf_attr_t->f_attr_permission[4] = (st->st_mode & S_IWGRP) ? 'w' : '-';
    pf_attr_t->f_attr_permission[5] = (st->st_mode & S_IXGRP) ? 'x' : '-';
    pf_attr_t->f_attr_permission[6] = (st->st_mode & S_IROTH) ? 'r' : '-';
    pf_attr_t->f_attr_permission[7] = (st->st_mode & S_IWOTH) ? 'w' : '-';
    pf_attr_t->f_attr_permission[8] = (st->st_mode & S_IXOTH) ? 'x' : '-';
    pf_attr_t->f_attr_permission[9] = '\0';

    return 0;
}

int f_get_file_owner(file_attribute_t* pf_attr_t)
{
    struct passwd *pw = getpwuid(pf_attr_t->f_attr_stat_info.st_uid);
    if (NULL == pw)
    {
        ERROR("[f_get_file_owner] get file owner failed: %s", pf_attr_t->f_attr_name);
        return -1;
    }
    strncpy(pf_attr_t->f_attr_uname, pw->pw_name, SZ_FILE_NAME-1);

    return 0;
}

int f_get_file_group(file_attribute_t* pf_attr_t)
{
    struct group *gr = getgrgid(pf_attr_t->f_attr_stat_info.st_gid);
    if (NULL == gr)
    {
        ERROR("[f_get_file_group] get file group failed: %s", pf_attr_t->f_attr_name);
        return -1;
    }
    strncpy(pf_attr_t->f_attr_gname, gr->gr_name, SZ_FILE_NAME-1);

    return 0;
}

int f_get_file_size(const struct stat *st, file_attribute_t* pf_attr_t)
{
    snprintf(pf_attr_t->f_attr_size, SZ_FILE_SIZE, "%ld", st->st_size);
    return 0;
}

int f_get_file_mtime(const struct stat *st, file_attribute_t* pf_attr_t)
{
    struct tm tm;
    if (NULL == localtime_r(&st->st_mtime, &tm))
    {
        ERROR("[f_get_file_mtime] get file mtime failed: %s", pf_attr_t->f_attr_name);
        return -1;
    }
    
    strftime(pf_attr_t->f_attr_mtime, SZ_FILE_TIME, "%Y-%m-%d %H:%M:%S", &tm);

    return 0;
}

int f_get_file_link_content(const char *path, file_attribute_t* pf_attr_t)
{
    if (pf_attr_t->f_attr_type != 'l')
    {
        memset(pf_attr_t->f_attr_link_content, '\0', SZ_FILE_LINK_CONTENT);
        return 0;
    }
    char link_content[SZ_FILE_LINK_CONTENT];
    int ret = readlink(path, link_content, SZ_FILE_LINK_CONTENT-1);
    if (ret < 0)
    {
        ERROR("[f_get_file_link_content] get file link content failed: %s : %s", path, strerror(errno));
        return -1;
    }
    link_content[ret] = '\0';
    snprintf(pf_attr_t->f_attr_link_content, SZ_FILE_LINK_CONTENT, "--> %s", link_content);

    return 0;
}

int f_get_file_nlink(const struct stat *st, file_attribute_t* pf_attr_t)
{
    snprintf(pf_attr_t->f_attr_nlink, SZ_FILE_NLINK, "%ld", st->st_nlink);
    return 0;
}