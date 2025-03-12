#ifndef __CMD_HANDLE_H__
#define __CMD_HANDLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "log.h"
#include "cmd_type.h"

#include "cmd_cp.h"
#include "cmd_ls.h"
#include "cmd_pwd.h"
#include "cmd_cd.h"
#include "cmd_rm.h"

/*
* initialize the cmd_t structure
* @param pcmd_t: the pointer to the cmd_t structure to be initialized
* @return: 0 if success, -1 if failed
**/
extern int init_cmd_struct(cmd_t *pcmd_t);
/*
* handle the received command line and execute the corresponding command
* @param recv_cmd: the received command line
* @return: 0 if success, -1 if failed
**/
extern int cmd_execute(char *recv_cmd);
// show help message
extern int cmd_help();
/*
* parse command line and store the command and arguments in cmd_t structure
* @param recv_cmd: the received command line
* @param pcmd_t: the pointer to the cmd_t structure to store the command and arguments
**/
extern int parse_cmd_line(char *recv_cmd, cmd_t *pcmd_t);
/*
* dispatch the command to the corresponding handler function
* @param pcmd_t: the pointer to the cmd_t structure containing the command and arguments
* @return: 0 if success, -1 if failed
**/
extern int dispatch_cmd(cmd_t *pcmd_t);


#endif // __CMD_HANDLE_H__