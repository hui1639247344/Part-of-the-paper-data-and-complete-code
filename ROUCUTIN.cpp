/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "ROUCUTIN.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: ROUCUTIN
* Description: constructor
********************************************************************/
ROUCUTIN::ROUCUTIN( const string &name )
: Atomic( name )
, roucutin_Ppin(addInputPort( "roucutin_Ppin" ))
, roucutin_Gin(addInputPort( "roucutin_Gin" ))
, roucutin_Pin(addInputPort( "roucutin_Pin" ))
, roucutin_wkpein(addInputPort( "roucutin_wkpein" ))
, roucutin_cout(addOutputPort( "roucutin_cout" ))
, roucutin_ceout(addOutputPort( "roucutin_ceout" ))
, roucutin_ccfout(addOutputPort( "roucutin_ccfout" ))
, roucutin_chout(addOutputPort( "roucutin_chout" ))
, roucutin_cwout(addOutputPort( "roucutin_cwout" ))
, roucutin_tout(addOutputPort( "roucutin_tout" ))
, roucutin_wkpeout(addOutputPort( "roucutin_wkpeout" ))
//, roucutin_time(roucutin_h, roucutin_m, roucutin_s, 0)
, roucutin_time(0, 7, 18, 0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ROUCUTIN::initFunction()
{
	roucutin_wkpe_in = roucutin_wkpe_out = 0;
	roucutin_h = roucutin_m = roucutin_s = 0;
	roucutin_Pp = roucutin_G = roucutin_P = roucutin_c = roucutin_ce = 0;
	roucutin_ccf = roucutin_ch = roucutin_cw, roucutin_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &ROUCUTIN::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == roucutin_wkpein){
		roucutin_wkpe_in = msg.value();
		roucutin_t = ((roucutin_G+4)*60/roucutin_Pp)*26/32;
		roucutin_tt = (int)roucutin_t;
		roucutin_h = roucutin_tt/3600;
		roucutin_m = (roucutin_tt%3600)/60;
		roucutin_s = roucutin_tt%3600%60;
	    holdIn(active,roucutin_time);
	}
	if(msg.port() == roucutin_Ppin){
		roucutin_Pp = msg.value();
	}
	if(msg.port() == roucutin_Gin){
		roucutin_G = msg.value();
	}
//	if(roucutin_wkpe_in >= 1){
//		if(msg.port() == roucutin_Ppin){
//			roucutin_Pp = msg.value();
//		}
//		if(msg.port() == roucutin_Gin){
//			roucutin_G = msg.value();
//		}
////	if(msg.port() == roucutin_Pin){
////		roucutin_P = msg.value();
////	}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &ROUCUTIN::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &ROUCUTIN::outputFunction( const InternalMessage &msg )
{
	if(roucutin_wkpe_in >= 1){

		roucutin_P = 8922.5;
//		roucutin_P = 8982.1;/*train*/
//		roucutin_t = 442;/*train*/

//		roucutin_t = ((roucutin_G+4)*60/roucutin_Pp)*26/32;
//		roucutin_tt = (int)roucutin_t;
//		roucutin_h = roucutin_tt/3600;
//		roucutin_m = (roucutin_tt%3600)/60;
//	    roucutin_s = roucutin_tt%3600%60;
//	    holdIn(active,roucutin_time);
	    roucutin_wkpe_out = 1;

	    roucutin_ce = 0.8042*roucutin_P*roucutin_t/3600000;
	    roucutin_ccf = (roucutin_t/830000)*(2.85*13+0.2*13);
	    roucutin_ch = (roucutin_t/86400)*17.57*1.7;
	    roucutin_cw = 0.2*0.30625*0.95;
	    roucutin_c = roucutin_ce+roucutin_ccf+roucutin_ch+roucutin_cw;
	}
	if(roucutin_wkpe_out >= 1){
		sendOutput(msg.time(),roucutin_cout,roucutin_c);
		sendOutput(msg.time(),roucutin_ceout,roucutin_ce);
		sendOutput(msg.time(),roucutin_ccfout,roucutin_ccf);
		sendOutput(msg.time(),roucutin_chout,roucutin_ch);
		sendOutput(msg.time(),roucutin_cwout,roucutin_cw);
		sendOutput(msg.time(),roucutin_tout,roucutin_tt);
		sendOutput(msg.time(),roucutin_wkpeout,roucutin_wkpe_out);
		roucutin_wkpe_in = 0;
	}
	
	return *this;

}

ROUCUTIN::~ROUCUTIN()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
