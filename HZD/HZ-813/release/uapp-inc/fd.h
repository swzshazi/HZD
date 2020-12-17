#ifndef __INC_FD_H
#define __INC_FD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>
#include <sys/types.h>
#include "common_types.h"

#define MAX_FD                  64
#define MAX_TIMER_TASK          4
#define MAX_PYTHON_CALLBACK     256
#define MAX_BUF_LEN       		4096

#define RUN               	1
#define READY      			0

typedef struct
{
    int     active;
    int     fd;
    int     start;
    int     rd_cursor;
    char    buf[MAX_BUF_LEN];
    void   (*read)(void *);
    void    *arg;
    time_t  last_active_time;
}FD;

typedef struct
{
    void  (*callback_func)(void *);
    void   *callback_arg;
}PYTHON_CALLBACK;

extern    FD                   fdt[MAX_FD];
extern    PYTHON_CALLBACK      python_callback[MAX_PYTHON_CALLBACK];

extern void disableOneFdNode(int fd);
extern int  fdIsActive(int fd);

//应用接口C库，文件描述符管理部分
extern void initFdNode(void);
extern void enableFdNode(void);
extern void delFdNode(int fd);
extern void hzFdSelect(void);
extern int  addFdNodeFunc(int fd,void (*func)(void *),void *arg,int is_active_now);

//应用接口C库，python回调部分
extern void initPythonCallback(void);
extern int  addPythonCallback(Uint8 type, void *func, void *arg);

//应用接口C库，休眠管理部分
extern void hzWait(int ms);

#ifdef __cplusplus
}
#endif

#endif  /*__INC_FD_H*/
