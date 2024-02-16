/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "ROUFULLCUT.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: ROUFULLCUT
* Description: constructor
********************************************************************/
ROUFULLCUT::ROUFULLCUT( const string &name )
: Atomic( name )
, roufullcut_Ppin(addInputPort( "roufullcut_Ppin" ))
, roufullcut_Gin(addInputPort( "roufullcut_Gin" ))
, roufullcut_Pin(addInputPort( "roufullcut_Pin" ))
, roufullcut_wkpein(addInputPort( "roufullcut_wkpein" ))
, roufullcut_cout(addOutputPort( "roufullcut_cout" ))
, roufullcut_ceout(addOutputPort( "roufullcut_ceout" ))
, roufullcut_ccfout(addOutputPort( "roufullcut_ccfout" ))
, roufullcut_chout(addOutputPort( "roufullcut_chout" ))
, roufullcut_cwout(addOutputPort( "roufullcut_cwout" ))
, roufullcut_tout(addOutputPort( "roufullcut_tout" ))
, roufullcut_wkpeout(addOutputPort( "roufullcut_wkpeout" ))
//, roufullcut_time(roufullcut_h, roufullcut_m, roufullcut_s, 0)
, roufullcut_time(0,1,41,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ROUFULLCUT::initFunction()
{
	roufullcut_wkpe_in = roufullcut_wkpe_out = 0;
	roufullcut_h = roufullcut_m = roufullcut_s = 0;
	roufullcut_Pp = roufullcut_G = roufullcut_P = roufullcut_c = roufullcut_ce = 0;
	roufullcut_ccf = roufullcut_ch = roufullcut_cw, roufullcut_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &ROUFULLCUT::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == roufullcut_wkpein){
		roufullcut_wkpe_in = msg.value();
		roufullcut_t = ((roufullcut_G+4)*60/roufullcut_Pp)*6/32;
		roufullcut_tt = (int)roufullcut_t;
		roufullcut_h = roufullcut_tt/3600;
		roufullcut_m = (roufullcut_tt%3600)/60;
	    roufullcut_s = roufullcut_tt%3600%60;
	    holdIn(active,roufullcut_time);
	}
	if(msg.port() == roufullcut_Ppin){
		roufullcut_Pp = msg.value();
	}
	if(msg.port() == roufullcut_Gin){
		roufullcut_G = msg.value();
	}
//	if(roufullcut_wkpe_in >= 1){
//		if(msg.port() == roufullcut_Ppin){
//			roufullcut_Pp = msg.value();
//		}
//		if(msg.port() == roufullcut_Gin){
//			roufullcut_G = msg.value();
//		}
////		if(msg.port() == roufullcut_Pin){
////			roufullcut_P = msg.value();
////		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &ROUFULLCUT::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &ROUFULLCUT::outputFunction( const InternalMessage &msg )
{
	if(roufullcut_wkpe_in >= 1){

		roufullcut_P = 9200.2;
//		roufullcut_P = 9180;/*train*/
//		roufullcut_t = 95;/*train*/

//		roufullcut_t = ((roufullcut_G+4)*60/roufullcut_Pp)*6/32;
//		roufullcut_tt = (int)roufullcut_t;
//		roufullcut_h = roufullcut_tt/3600;
//		roufullcut_m = (roufullcut_tt%3600)/60;
//	    roufullcut_s = roufullcut_tt%3600%60;
//	    holdIn(active,roufullcut_time);
	    roufullcut_wkpe_out = 1;

	    roufullcut_ce = 0.8042*roufullcut_P*roufullcut_t/3600000;
	    roufullcut_ccf = (roufullcut_t/830000)*(2.85*13+0.2*13);
	    roufullcut_ch = (roufullcut_t/86400)*17.57*1.7;
	    roufullcut_cw = 0.2*0.109375*0.95;
	    roufullcut_c = roufullcut_ce+roufullcut_ccf+roufullcut_ch+roufullcut_cw;
	}
	if(roufullcut_wkpe_out >= 1){
		sendOutput(msg.time(),roufullcut_cout,roufullcut_c);
		sendOutput(msg.time(),roufullcut_ceout,roufullcut_ce);
		sendOutput(msg.time(),roufullcut_ccfout,roufullcut_ccf);
		sendOutput(msg.time(),roufullcut_chout,roufullcut_ch);
		sendOutput(msg.time(),roufullcut_cwout,roufullcut_cw);
		sendOutput(msg.time(),roufullcut_tout,roufullcut_tt);
		sendOutput(msg.time(),roufullcut_wkpeout,roufullcut_wkpe_out);
		roufullcut_wkpe_in = 0;
	}

	return *this;

}

ROUFULLCUT::~ROUFULLCUT()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
