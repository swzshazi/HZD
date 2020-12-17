#ifndef __INCTASKH
#define __INCTASKH

#ifdef __cplusplus
extern "C" {
#endif

extern  Uint32  lvl1_cycle_time;
extern  Uint32  lvl2_cycle_time;
extern  Uint32  lvl3_cycle_time;
extern  Uint32  lvl4_cycle_time;

extern 	Uint32  lvl1_run_cnt;
extern 	Uint32  lvl2_run_cnt;
extern 	Uint32  lvl3_run_cnt;
extern 	Uint32  lvl4_run_cnt;

// 应用调用C库接口
extern  int  setTask(int level,void(*)(),void*);
extern  int  setFirstTask(int level, void (*)(), void *);
extern  int  setLastTask(int level, void (*)(), void *);
extern 	int  addTimerTask(unsigned long period,void (*func)(void *),void *arg);
extern  int  newThread(unsigned char policy,int pri_no,void *func,void *args);

#ifdef __cplusplus
}
#endif

#endif
