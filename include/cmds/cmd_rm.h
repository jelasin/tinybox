#ifndef __CMD_RM_H__
#define __CMD_RM_H__

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
* cmd_rm - remove file or directory
* @cmd: command structure
**/
extern int rm_handle(cmd_t *pcmd_t);
/*
* rm_executer - execute rm command
* @cmd: command structure
* return: 0 on success, -1 on failure
**/
extern int rm_execute(cmd_t *pcmd_t);
/*
* rm_file - remove file
* @path: file path
* return: 0 on success, -1 on failure
**/
extern int rm_file(const char *path);
/*
* rm_dir - remove directory
* @path: directory path
* return: 0 on success, -1 on failure
**/
extern int rm_dir(const char *path);

#endif /* __CMD_RM_H__ */