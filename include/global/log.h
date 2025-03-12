#ifndef __LOG_H__
#define __LOG_H__

#include "vt_color.h"
#include <time.h>

#define LOG(level, fmt, ...) \
    do { \
        time_t now = time(NULL); \
        char buf[20]; \
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
        fprintf(stderr, "[%s] [%s] " fmt "\n", buf, level, ##__VA_ARGS__); \
    } while (0)

#define ERROR(fmt, args...) LOG(RED"ERROR"NONE, fmt, ##args)
#define WARN(fmt, args...) LOG(YELLOW"WARN"NONE, fmt, ##args)
#define INFO(fmt, args...) LOG("INFO", fmt, ##args)

#define INFO_CMD(cmd) \
    do { \
        INFO("cmd_name: %s", cmd.cmd_name); \
        INFO("cmd_arg_count: %d", cmd.cmd_arg_count); \
        for (int i = 0; i < cmd.cmd_arg_count; i++) \
        { \
            INFO("cmd_arg_list[%d]: %s", i, cmd.cmd_arg_list[i]); \
        } \
    } while (0)

#endif /* __LOG_H__ */