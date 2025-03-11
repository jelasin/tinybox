#ifndef __CMD_TYPE_H__
#define __CMD_TYPE_H__

#define SZ_NAME 8           // 命令名称长度
#define SZ_ARG 128          // 命令参数长度
#define SZ_COUNT 10         // 命令参数个数
#define SZ_PATH 1024        // 文件路径名最大长度
#define PATH_MAX SZ_PATH    // 路径最大长度

#define MAX_CMD_LEN 1024    // 命令最大长度

enum file_type 
{
    FT_DIR = 0,             // 是目录
    FT_FILE = 1,            // 是普通文件
    FT_ERROR = 2,           // 出错
    FT_UNKNOWN = 3,         // 文件类型未知
    FT_LINK = 4,            // 是链接文件
    FT_SOCKET = 5,          // 是socket文件
    FT_BLOCK = 6,           // 是块设备文件
    FT_CHAR = 7,            // 是字符设备文件
    FT_FIFO = 8,            // 是命名管道文件
};

typedef struct command {
    char cmd_name[SZ_NAME];                 // 命令名称
    int  cmd_arg_count;                     // 命令参数个数
    char cmd_arg_list[SZ_COUNT][SZ_ARG];    // 命令参数列表
} cmd_t;


#define SZ_FILE_NAME 64
#define SZ_FILE_PERMISSION 10
#define SZ_FILE_TIME 32                                                      
#define SZ_FILE_LINK_CONTENT 64

typedef struct file_attribute
{                                                                          
    struct stat f_attr_stat_info;                   // 保留系统原来的结构
    char f_attr_type;                               // 文件类型
    char f_attr_uname[SZ_FILE_NAME];                // user name
    char f_attr_gname[SZ_FILE_NAME];                // group name
    char f_attr_mtime[SZ_FILE_TIME];                // 最后一次修改时间
    char f_attr_permission[SZ_FILE_PERMISSION];     // 权限
    char f_attr_name[SZ_FILE_NAME];                 // 文件名
    char f_attr_link_content[SZ_FILE_LINK_CONTENT]; // 链接指向的内容
} file_attribute_t;

#endif /* __CMD_TYPE_H__ */