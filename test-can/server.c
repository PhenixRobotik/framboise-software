#include "server.h"
#include "can.h"

RP_Interface jostof_iface;
RP_Interface tsmr_iface;
RC_Client jostof_client;
RC_Client tsmr_client;

typedef enum{PARAMS, RETURN}fprot_field;
static const char tsmr_fprots[NB_FUNS][2][RC_FMT_SIZE] =
  {
   [SET_STOP]              = {"",     ""   },
   [SET_THETA]             = {"F",    "u"   },
   [SET_THETA_SPEED]       = {"F",    "u"   },
   [SET_TRANSLATION]       = {"F",    "u"   },
   [SET_TRANSLATION_SPEED] = {"F",    "u"   },
   [SET_X_Y_THETA]         = {"FFFu", "u"   },
   [GET_ODOMETRY]          = {"",     "FFF"},
   [GET_STATE]             = {"",     "u"  },
   [ASSER_ENABLE]                = {"",     ""},
   [ASSER_DISABLE]               = {"",     ""}
  };

int init_jostof_rc(){
  //TODO : error codes
  RP_Init_Interface(&jostof_iface, NULL, JOSTOF_RX_CAN_ID, JOSTOF_TX_CAN_ID, can_transmit, get_tick);
  RC_Client_Init(&jostof_client, &jostof_iface, 0);
  RC_Client_Add_Function(&jostof_client, 0, "", "iiii");
  RP_Sync(&jostof_iface, 10);

  return 0;
}

int init_tsmr_rc(){
  //TODO : error codes
  RP_Init_Interface(&tsmr_iface, NULL, TSMR_RX_CAN_ID, TSMR_TX_CAN_ID, can_transmit, get_tick);
  RC_Client_Init(&tsmr_client, &tsmr_iface, 0);
  RC_Client_Add_Function(&tsmr_client, 0, "sbBuifFs", "sbBuifFs");
  RP_Sync(&tsmr_iface, 10);
  
  int i;
  for(i = 0; i < NB_FUNS; ++i){
    if(RC_Client_Add_Function(&tsmr_client,
			      i,
			      tsmr_fprots[i][PARAMS],
			      tsmr_fprots[i][RETURN]) != 0){
      return -1;
    }
  }

  return 0;
}

/*
void get_asser_data(RC_Server *server){
  uint8_t index;
  RC_Server_Get_Args(server, &index);
  if(index > 2){
    RC_Server_Return(server, 0, 0., 0., 0., 0, 0);
    return;
  }
  
  RC_Server_Return(server, 1,
		   pid_data[index].Kp,
		   pid_data[index].Ki,
		   pid_data[index].Kd,
		   pid_data[index].pos_eps,
		   pid_data[index].speed_eps);
}
*/
