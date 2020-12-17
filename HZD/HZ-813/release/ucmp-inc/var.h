#ifndef __INC_VAR_DEF_H
#define __INC_VAR_DEF_H

#ifdef __cplusplus
extern "C" {
#endif	

typedef struct
{
    char 	desc_cn[NAME_STRING_LEN];
    char 	desc_en[NAME_STRING_LEN];
    char 	unit[8];
    char 	format[8];
    Uint8 	show_attr;
    Uint8 	type;
    Uint8 	info;
    Uint8 	reserved;
    float32 min;
    float32 max;
    float32 norm;
    float32 prm;
}SIGNAL_DESC;

#define      linkLIB(a)      init##a()

extern  int  registerComponent(Component *self);
extern  int  registerVarBlockIn(Component *self, void **signal, const char *desc, int size);
extern  int  registerVarBlockOut(Component *self, void *signal, const char *desc, int size);
extern  int  registerVarIn(Component *self, void **signal, const char *desc, Uint8 type, Uint8 level);
extern  int  registerVarOut(Component *self, void *signal, const char *desc, Uint8 type, Uint8 level);
extern  int  registerConstSignalOut(Component *self, void *signal, const char *desc, Uint8 type, Uint8 level);
extern  int  registerVarOutWithQuality(Component *self, void *signal,  const char *desc, Uint8 type, Uint8 level, void *quality);

extern  void addInValueSoeTime(void *in_var);
extern  int  registerVarQuality(void *signal, void *quality);
extern  int  registerVarLink(char *out_var_name, char *in_var_name);
extern  int  linkVarOutWithPtr(Component *self,void *out, char *ext_var_name);
extern  int  linkVarInWithPtr(Component *self,void **in, char *ext_var_name);
extern  int  registerParameter(Component *self,void *parameter,const char *desc,Uint8 type);
extern  int  registerParameterWithCallback(Component *self,void *parameter,const char *desc,Uint8 type,int (*pfunc)(void *),void *arg);

#ifdef __cplusplus
}
#endif
#endif
