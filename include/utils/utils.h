#ifndef __UTILS_H__
#define __UTILS_H__

#include "cmd_type.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#include <pwd.h>
#include <grp.h>

#define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)

/*
* get file type
* @param path: file path
* @param flag: true if check src file and print error message, 
*              false if check dest file and not print error message
* @return: file type
**/
extern enum file_type get_file_type(const char *path, bool flag);
/*
* get file attribute
* @param path: file path
* @param pf_attr_t: file attribute struct
* @return: 0 if success, -1 if fail
**/
extern int get_file_attribute(const char *path, file_attribute_t* pf_attr_t);

extern int f_get_file_type(const char *path, file_attribute_t* pf_attr_t);

extern int f_get_file_name(const char *path, file_attribute_t* pf_attr_t);

extern int f_get_file_permisson(const struct stat *st, file_attribute_t* pf_attr_t);

extern int f_get_file_owner(file_attribute_t* pf_attr_t);

extern int f_get_file_group(file_attribute_t* pf_attr_t);

extern int f_get_file_size(const struct stat *st, file_attribute_t* pf_attr_t);

extern int f_get_file_mtime(const struct stat *st, file_attribute_t* pf_attr_t);

extern int f_get_file_link_content(const char *path, file_attribute_t* pf_attr_t);

extern int f_get_file_nlink(const struct stat *st, file_attribute_t* pf_attr_t);

#endif /* __UTILS_H__ */