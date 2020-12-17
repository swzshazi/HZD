/* FileName: DEBUGU.c */

#include <stdlib.h>
#include "hzplatform.h"
#include "DEBUGU.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void DEBUGU_task( DEBUGU *dp);

int initDEBUGU( DEBUGU *dp);


DEBUGU *newDEBUGU(Component *parent, const char *name)
{
	DEBUGU *dp;
	Uint8 i;
	char	tp_str[150];
	
	dp = (DEBUGU*)calloc(1, sizeof( DEBUGU ));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "DEBUGU";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (void *)initDEBUGU;

	registerComponent( (Component*)dp);
	

	
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b1_in), "dbg_b1_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b2_in), "dbg_b2_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b3_in), "dbg_b3_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b4_in), "dbg_b4_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b5_in), "dbg_b5_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b6_in), "dbg_b6_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b7_in), "dbg_b7_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_b8_in), "dbg_b8_in", T_BIT, LEVEL1 );
	
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s1_in), "dbg_s1_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s2_in), "dbg_s2_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s3_in), "dbg_s3_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s4_in), "dbg_s4_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s5_in), "dbg_s5_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s6_in), "dbg_s6_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s7_in), "dbg_s7_in", T_INT16,LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_s8_in), "dbg_s8_in", T_INT16,LEVEL1 );
	
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f1_in), "dbg_f1_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f2_in), "dbg_f2_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f3_in), "dbg_f3_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f4_in), "dbg_f4_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f5_in), "dbg_f5_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f6_in), "dbg_f6_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f7_in), "dbg_f7_in", T_FLOAT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->dbg_f8_in), "dbg_f8_in", T_FLOAT, LEVEL1 );
//////////////////////////////////////////////////////////////////////////////////////////////////////

	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b1), "dbg_b1", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b2), "dbg_b2", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b3), "dbg_b3", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b4), "dbg_b4", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b5), "dbg_b5", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b6), "dbg_b6", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b7), "dbg_b7", T_BIT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_b8), "dbg_b8", T_BIT, LEVEL1 );

	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s1), "dbg_s1", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s2), "dbg_s2", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s3), "dbg_s3", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s4), "dbg_s4", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s5), "dbg_s5", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s6), "dbg_s6", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s7), "dbg_s7", T_INT16,LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_s8), "dbg_s8", T_INT16,LEVEL1 );

	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f1), "dbg_f1", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f2), "dbg_f2", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f3), "dbg_f3", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f4), "dbg_f4", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f5), "dbg_f5", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f6), "dbg_f6", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f7), "dbg_f7", T_FLOAT, LEVEL1 );
	registerVarOut( (Component*)dp, (void*)&(dp->dbg_f8), "dbg_f8", T_FLOAT, LEVEL1 );
	
	return dp;
}

void DEBUGU_check_task(DEBUGU *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}



INIT_CODE
int initDEBUGU(DEBUGU *dp)
{
	dp->dbg_b8 = 1;
	
	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	
	setTask( 1, DEBUGU_task, dp);
	setTask( 4, DEBUGU_check_task, dp);

	return 0;
}

void DEBUGU_task(DEBUGU *dp)
{
	dp->dbg_b1 = 1;
}

