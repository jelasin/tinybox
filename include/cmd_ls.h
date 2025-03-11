#ifndef __CMD_LS_H__
#define __CMD_LS_H__

#include "cmd_type.h"
#include "log.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

/*
* ls handler function
* @param pcmd_t: command struct pointer
* @return: 0 on success, -1 on failure
**/
extern int ls_handle(cmd_t *pcmd_t);
/*
* print all files in a directory
* @param path: directory path
* @return: 0 on success, -1 on failure
**/
extern int ls_print_dir(const char* path);
/*
* print one file's attribute
* @param path: file path
* @return: 0 on success, -1 on failure
**/
extern int ls_print_file(const char* path);

#endif /* __CMD_LS_H__ */