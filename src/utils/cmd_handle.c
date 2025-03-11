#include "cmd_handle.h"

int cmd_execute(char *recv_cmd)
{
    if (NULL == recv_cmd)
    {
        ERROR("[cmd_execute] recv_cmd is NULL");
        return -1;
    }
    int ret = 0;
    cmd_t cmd;
    init_cmd_struct(&cmd);

    parse_cmd_line(recv_cmd, &cmd);

#if defined(DEBUG)
    INFO_CMD(cmd);
#endif

    ret = dispatch_cmd(&cmd);

    return ret;
}

int init_cmd_struct(cmd_t *pcmd_t)
{
    memset(pcmd_t, '\x00', sizeof(cmd_t));
    return 0;
}

int parse_cmd_line(char *recv_cmd, cmd_t *pcmd_t)
{
    if (NULL == recv_cmd || NULL == pcmd_t)
    {
        ERROR("[parse_cmd_line] recv_cmd or pcmd_t is NULL");
        return -1;
    }

    char *p_cmd_name = recv_cmd;
    char *p_cmd_arg = NULL;
    char *p_context = NULL;
    char *p_step = " ";
    // get command name
    p_cmd_arg = strtok_r(p_cmd_name, p_step, &p_context);
    if (NULL == p_cmd_arg)
    {
        ERROR("[parse_cmd_line] p_cmd_arg is NULL");
        return -1;
    }
    strncpy(pcmd_t->cmd_name, p_cmd_arg, SZ_NAME);

    // get command arguments
    int i = 0;
    for (; i < SZ_COUNT; i++)
    {
        p_cmd_arg = strtok_r(NULL, p_step, &p_context);
        if (NULL == p_cmd_arg)
        {
            break;
        }
        strncpy(pcmd_t->cmd_arg_list[i], p_cmd_arg, SZ_ARG);
    }
    pcmd_t->cmd_arg_count = i;

    return 0;
}

int dispatch_cmd(cmd_t *pcmd_t)
{
    if (NULL == pcmd_t)
    {
        ERROR("[dispatch_cmd] pcmd_t is NULL");
        return -1;
    }

    if (0 == strcmp(pcmd_t->cmd_name, "ls"))
    {
        return ls_handle(pcmd_t);
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "cp"))
    {
        return cp_handle(pcmd_t);
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "pwd"))
    {
        return pwd_handle();
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "cd"))
    {
        return cd_handle(pcmd_t);
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "rm"))
    {
        return rm_handle(pcmd_t);
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "exec"))
    {
        return 0;
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "mkdir"))
    {
        return 0;
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "touch"))
    {
        return 0;
    }
    else if (0 == strcmp(pcmd_t->cmd_name, "echo"))
    {
        return 0;
    }
    
    WARN("[dispatch_cmd] unknown command: %s", pcmd_t->cmd_name);
    return -1;
}

int cmd_help()
{
    printf("Usage: [command] [arguments]\n");
    printf("Available commands: [help, exit, ls, cp, pwd, rm, exec]\n");
    return 0;
}