#ifndef _MICRO_CONFIG_H
#define _MICRO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// 定义系统内核编译选项

#define    SUPPORT_MMB                               // 支持MMB传输
#undef     SUPPORT_MMB_SELECT                        // 支持MMB选择性接收

#ifdef __cplusplus
}
#endif
#endif 