/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "FINFULLCUT.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: FINFULLCUT
* Description: constructor
********************************************************************/
FINFULLCUT::FINFULLCUT( const string &name )
: Atomic( name )
, finfullcut_Ppin(addInputPort( "finfullcut_Ppin" ))
, finfullcut_Gin(addInputPort( "finfullcut_Gin" ))
, finfullcut_Pin(addInputPort( "finfullcut_Pin" ))
, finfullcut_wkpein(addInputPort( "finfullcut_wkpein" ))
, finfullcut_cout(addOutputPort( "finfullcut_cout" ))
, finfullcut_ceout(addOutputPort( "finfullcut_ceout" ))
, finfullcut_ccfout(addOutputPort( "finfullcut_ccfout" ))
, finfullcut_chout(addOutputPort( "finfullcut_chout" ))
, finfullcut_cwout(addOutputPort( "finfullcut_cwout" ))
, finfullcut_tout(addOutputPort( "finfullcut_tout" ))
, finfullcut_wkpeout(addOutputPort( "finfullcut_wkpeout" ))
//, finfullcut_time(finfullcut_h, finfullcut_m, finfullcut_s, 0)
, finfullcut_time(0,1,7,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &FINFULLCUT::initFunction()
{
	finfullcut_wkpe_in = finfullcut_wkpe_out = 0;
	finfullcut_h = finfullcut_m = finfullcut_s = 0;
	finfullcut_Pp = finfullcut_G = finfullcut_P = finfullcut_c = finfullcut_ce = 0;
	finfullcut_ccf = finfullcut_ch = finfullcut_cw, finfullcut_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &FINFULLCUT::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == finfullcut_wkpein){
		finfullcut_wkpe_in = msg.value();
		finfullcut_t = ((finfullcut_G+4)*60/finfullcut_Pp)*6/32;
		finfullcut_tt = (int)finfullcut_t;
		finfullcut_h = finfullcut_tt/3600;
		finfullcut_m = (finfullcut_tt%3600)/60;
		finfullcut_s = finfullcut_tt%3600%60;
		holdIn(active,finfullcut_time);
	}
	if(msg.port() == finfullcut_Ppin){
		finfullcut_Pp = msg.value();
	}
	if(msg.port() == finfullcut_Gin){
		finfullcut_G = msg.value();
	}
//	if(finfullcut_wkpe_in >= 1){
//		if(msg.port() == finfullcut_Ppin){
//			finfullcut_Pp = msg.value();
//		}
//		if(msg.port() == finfullcut_Gin){
//			finfullcut_G = msg.value();
//		}
////		if(msg.port() == finfullcut_Pin){
////			finfullcut_P = msg.value();
////		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &FINFULLCUT::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &FINFULLCUT::outputFunction( const InternalMessage &msg )
{
	if(finfullcut_wkpe_in >= 1){

		finfullcut_P = 8945.6;
//		finfullcut_P = 8935.5;/*train*/
//		finfullcut_t = 64;/*train*/

//		finfullcut_t = ((finfullcut_G+4)*60/finfullcut_Pp)*26/32;
//		finfullcut_tt = (int)finfullcut_t;
//		finfullcut_h = finfullcut_tt/3600;
//		finfullcut_m = (finfullcut_tt%3600)/60;
//	    finfullcut_s = finfullcut_tt%3600%60;
//	    holdIn(active,finfullcut_time);
	    finfullcut_wkpe_out = 1;

	    finfullcut_ce = 0.8042*finfullcut_P*finfullcut_t/3600000;
	    finfullcut_ccf = (finfullcut_t/830000)*(2.85*13+0.2*13);
	    finfullcut_ch = (finfullcut_t/86400)*17.57*1.7;
	    finfullcut_cw = 0.2*0.109375*0.05;
	    finfullcut_c = finfullcut_ce+finfullcut_ccf+finfullcut_ch+finfullcut_cw;
	}
	if(finfullcut_wkpe_out >= 1){
		sendOutput(msg.time(),finfullcut_cout,finfullcut_c);
		sendOutput(msg.time(),finfullcut_ceout,finfullcut_ce);
		sendOutput(msg.time(),finfullcut_ccfout,finfullcut_ccf);
		sendOutput(msg.time(),finfullcut_chout,finfullcut_ch);
		sendOutput(msg.time(),finfullcut_cwout,finfullcut_cw);
		sendOutput(msg.time(),finfullcut_tout,finfullcut_tt);
		sendOutput(msg.time(),finfullcut_wkpeout,finfullcut_wkpe_out);
		finfullcut_wkpe_in = 0;
	}

	return *this;

}

FINFULLCUT::~FINFULLCUT()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
