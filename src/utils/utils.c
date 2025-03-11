#include "utils.h"

enum file_type get_file_type(const char *path, bool flag)
{
    if (path == NULL)
    {
        if (flag) ERROR("[get_file_type] invalid args");
        return FT_ERROR;
    }
#if defined(DEBUG)
    INFO("[get_file_type] path: %s", path);
#endif

    struct stat st;
    int ret = stat(path, &st);
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
        return NULL;
    }

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
        ERROR("[get_file_attribute] unknown file type: %s", path);
        return -1;
    }

    return 0;
}