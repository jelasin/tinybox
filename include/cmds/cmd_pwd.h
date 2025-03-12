#ifndef __CMD_PWD_H__
#define __CMD_PWD_H__

#include "cmd_type.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

/*
* pwd_handle - handle the pwd command
*/
extern int pwd_handle(cmd_t *pcmd_t);
/*
* pwd_execute - execute the pwd command
* @cmd - the command to execute
* @return - 0 if success, -1 if failure
**/
extern int pwd_execute(cmd_t *pcmd_t);

#endif /* __CMD_PWD_H__ */