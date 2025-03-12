#ifndef __CMD_CP_H__
#define __CMD_CP_H__

#include "cmd_type.h"
#include "log.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

typedef struct cp_file_info {
    enum file_type src_ftype;   // 源文件类型
    char src_path[SZ_PATH];     // 源文件路径名
    char dest_path[SZ_PATH];    // 目标文件路径名
} cp_file_info_t;

/*
* handle cp command
* @param pcmd_t: command struct
* @return: 0 if success, -1 if fail
**/
extern int cp_handle(cmd_t *pcmd_t);
/*
* parse src and dest path, and get file info
* @param pcmd_t: command struct
* @param pfile_info: file info struct
* @return: 0 if success, <0 if fail
**/
extern int parse_cp_args(cmd_t *pcmd_t, cp_file_info_t *pfile_info);
/*
* copy file
* @param src_path: source file path
* @param dest_path: destination file path
* @return: 0 if success, -1 if fail
**/
extern int cp_file(char *src_path, char *dest_path);
/*
* copy directory
* @param src_path: source directory path
* @param dest_path: destination directory path
* @return: 0 if success, -1 if fail
**/
extern int cp_dir(char *src_path, char *dest_path);

#endif /* __CMD_CP_H__ */