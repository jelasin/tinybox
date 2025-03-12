#ifndef __CMD_CD_H__
#define __CMD_CD_H__

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
* cd command
* @cmd: command structure
**/
extern int cd_handle(cmd_t *pcmd_t);
/*
* cd command execute function
* @cmd: command structure
* @return: 0 on success, -1 on failure
**/
extern int cd_execute(cmd_t *pcmd_t);

#endif /* __CMD_CD_H__ */