#include "cmd_handle.h"

int main()
{
    char* cmd = (char*)malloc(MAX_CMD_LEN);

    // get user id
    uid_t euid = geteuid();
    char form = (0 == euid) ? '#' : '$';

    while (true) 
    {
        // get current working directory
        char cur_dir[PATH_MAX];
        memset(cmd, '\0', MAX_CMD_LEN);
        if (getcwd(cur_dir, PATH_MAX) == NULL)
        {
            WARN("getcwd failed: %s", strerror(errno));
        }
        // print prompt
        fprintf(stderr, "tinybox:%s%c ", cur_dir, form);
        // read command from user
        fgets(cmd, MAX_CMD_LEN, stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        // handle exit and quit commands
        if (0 == strcmp(cmd, "exit") || 0 == strcmp(cmd, "quit"))
        {
            printf("Bye!\n");
            free(cmd);
            cmd = NULL;
            exit(0);
        }
        
        // handle help command
        if (0 == strcmp(cmd, "help"))
        {
            cmd_help();
            continue;
        }

        // execute command
        cmd_execute(cmd);
    }


    return 0;
}