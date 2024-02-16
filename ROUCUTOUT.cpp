/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "ROUCUTOUT.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: ROUCUTOUT
* Description: constructor
********************************************************************/
ROUCUTOUT::ROUCUTOUT( const string &name )
: Atomic( name )
, roucutout_Ppin(addInputPort( "roucutout_Ppin" ))
, roucutout_Gin(addInputPort( "roucutout_Gin" ))
, roucutout_Pin(addInputPort( "roucutout_Pin" ))
, roucutout_wkpein(addInputPort( "roucutout_wkpein" ))
, roucutout_cout(addOutputPort( "roucutout_cout" ))
, roucutout_ceout(addOutputPort( "roucutout_ceout" ))
, roucutout_ccfout(addOutputPort( "roucutout_ccfout" ))
, roucutout_chout(addOutputPort( "roucutout_chout" ))
, roucutout_cwout(addOutputPort( "roucutout_cwout" ))
, roucutout_tout(addOutputPort( "roucutout_tout" ))
, roucutout_wkpeout(addOutputPort( "roucutout_wkpeout" ))
//, roucutout_time(roucutout_h, roucutout_m, roucutout_s, 0)
, roucutout_time(0,8,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ROUCUTOUT::initFunction()
{
	roucutout_wkpe_in = roucutout_wkpe_out = 0;
	roucutout_h = roucutout_m = roucutout_s = 0;
	roucutout_Pp = roucutout_G = roucutout_P = roucutout_c = roucutout_ce = 0;
	roucutout_ccf = roucutout_ch = roucutout_cw, roucutout_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &ROUCUTOUT::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == roucutout_wkpein){
		roucutout_wkpe_in = msg.value();
		roucutout_t = ((roucutout_G+6)*60/roucutout_Pp)*27/32;
		roucutout_tt = (int)roucutout_t;
		roucutout_h = roucutout_tt/3600;
		roucutout_m = (roucutout_tt%3600)/60;
		roucutout_s = roucutout_tt%3600%60;
		holdIn(active,roucutout_time);
	}
	if(msg.port() == roucutout_Ppin){
		roucutout_Pp = msg.value();
	}
	if(msg.port() == roucutout_Gin){
		roucutout_G = msg.value();
	}
//	if(roucutout_wkpe_in >= 1){
//		if(msg.port() == roucutout_Ppin){
//			roucutout_Pp = msg.value();
//		}
//		if(msg.port() == roucutout_Gin){
//			roucutout_G = msg.value();
//		}
////		if(msg.port() == roucutout_Pin){
////			roucutout_P = msg.value();
////		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &ROUCUTOUT::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &ROUCUTOUT::outputFunction( const InternalMessage &msg )
{
	if(roucutout_wkpe_in >= 1){

		roucutout_P = 8901.8;
//		roucutout_P = 8910.1;/*train*/
//		roucutout_t = 481;/*train*/

//		roucutout_t = ((roucutout_G+6)*60/roucutout_Pp)*27/32;
//		roucutout_tt = (int)roucutout_t;
//		roucutout_h = roucutout_tt/3600;
//		roucutout_m = (roucutout_tt%3600)/60;
//	    roucutout_s = roucutout_tt%3600%60;
//	    holdIn(active,roucutout_time);
	    roucutout_wkpe_out = 1;

	    roucutout_ce = 0.8042*roucutout_P*roucutout_t/3600000;
	    roucutout_ccf = (roucutout_t/830000)*(2.85*13+0.2*13);
	    roucutout_ch = (roucutout_t/86400)*17.57*1.7;
	    roucutout_cw = 0.2*0.284375*0.95;
	    roucutout_c = roucutout_ce+roucutout_ccf+roucutout_ch+roucutout_cw;
	}
	if(roucutout_wkpe_out >= 1){
		sendOutput(msg.time(),roucutout_cout,roucutout_c);
		sendOutput(msg.time(),roucutout_ceout,roucutout_ce);
		sendOutput(msg.time(),roucutout_ccfout,roucutout_ccf);
		sendOutput(msg.time(),roucutout_chout,roucutout_ch);
		sendOutput(msg.time(),roucutout_cwout,roucutout_cw);
		sendOutput(msg.time(),roucutout_tout,roucutout_tt);
		sendOutput(msg.time(),roucutout_wkpeout,roucutout_wkpe_out);
		roucutout_wkpe_in = 0;
	}

	return *this;

}

ROUCUTOUT::~ROUCUTOUT()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
