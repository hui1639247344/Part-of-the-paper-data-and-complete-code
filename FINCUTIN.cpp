/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "FINCUTIN.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: FINCUTIN
* Description: constructor
********************************************************************/
FINCUTIN::FINCUTIN( const string &name )
: Atomic( name )
, fincutin_Ppin(addInputPort( "fincutin_Ppin" ))
, fincutin_Gin(addInputPort( "fincutin_Gin" ))
, fincutin_Pin(addInputPort( "fincutin_Pin" ))
, fincutin_wkpein(addInputPort( "fincutin_wkpein" ))
, fincutin_cout(addOutputPort( "fincutin_cout" ))
, fincutin_ceout(addOutputPort( "fincutin_ceout" ))
, fincutin_ccfout(addOutputPort( "fincutin_ccfout" ))
, fincutin_chout(addOutputPort( "fincutin_chout" ))
, fincutin_cwout(addOutputPort( "fincutin_cwout" ))
, fincutin_tout(addOutputPort( "fincutin_tout" ))
, fincutin_wkpeout(addOutputPort( "fincutin_wkpeout" ))
//, fincutin_time(fincutin_h, fincutin_m, fincutin_s, 0)
, fincutin_time(0,4,52,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &FINCUTIN::initFunction()
{
	fincutin_wkpe_in = fincutin_wkpe_out = 0;
	fincutin_h = fincutin_m = fincutin_s = 0;
	fincutin_Pp = fincutin_G = fincutin_P = fincutin_c = fincutin_ce = 0;
	fincutin_ccf = fincutin_ch = fincutin_cw, fincutin_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &FINCUTIN::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == fincutin_wkpein){
		fincutin_wkpe_in = msg.value();
		fincutin_t = ((fincutin_G+4)*60/fincutin_Pp)*26/32;
		fincutin_tt = (int)fincutin_t;
		fincutin_h = fincutin_tt/3600;
		fincutin_m = (fincutin_tt%3600)/60;
		fincutin_s = fincutin_tt%3600%60;
		holdIn(active,fincutin_time);
	}
	if(msg.port() == fincutin_Ppin){
		fincutin_Pp = msg.value();
	}
	if(msg.port() == fincutin_Gin){
		fincutin_G = msg.value();
	}
//	if(fincutin_wkpe_in >= 1){
//		if(msg.port() == fincutin_Ppin){
//			fincutin_Pp = msg.value();
//		}
//		if(msg.port() == fincutin_Gin){
//			fincutin_G = msg.value();
//		}
////		if(msg.port() == fincutin_Pin){
////			fincutin_P = msg.value();
////		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &FINCUTIN::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &FINCUTIN::outputFunction( const InternalMessage &msg )
{
	if(fincutin_wkpe_in >= 1){

		fincutin_P = 8922.5;
//		fincutin_P = 8935.5;/*train*/
//		fincutin_t = 289;/*train*/

//		fincutin_t = ((fincutin_G+4)*60/fincutin_Pp)*26/32;
//		fincutin_tt = (int)fincutin_t;
//		fincutin_h = fincutin_tt/3600;
//		fincutin_m = (fincutin_tt%3600)/60;
//	    fincutin_s = fincutin_tt%3600%60;
//	    holdIn(active,fincutin_time);
	    fincutin_wkpe_out = 1;

	    fincutin_ce = 0.8042*fincutin_P*fincutin_t/3600000;
	    fincutin_ccf = (fincutin_t/830000)*(2.85*13+0.2*13);
	    fincutin_ch = (fincutin_t/86400)*17.57*1.7;
	    fincutin_cw = 0.2*0.30625*0.05;
	    fincutin_c = fincutin_ce+fincutin_ccf+fincutin_ch+fincutin_cw;
	}
	if(fincutin_wkpe_out >= 1){
		sendOutput(msg.time(),fincutin_cout,fincutin_c);
		sendOutput(msg.time(),fincutin_ceout,fincutin_ce);
		sendOutput(msg.time(),fincutin_ccfout,fincutin_ccf);
		sendOutput(msg.time(),fincutin_chout,fincutin_ch);
		sendOutput(msg.time(),fincutin_cwout,fincutin_cw);
		sendOutput(msg.time(),fincutin_tout,fincutin_tt);
		sendOutput(msg.time(),fincutin_wkpeout,fincutin_wkpe_out);
		fincutin_wkpe_in = 0;
	}
	return *this;

}

FINCUTIN::~FINCUTIN()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
