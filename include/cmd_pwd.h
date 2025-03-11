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
extern int pwd_handle();

#endif /* __CMD_PWD_H__ */