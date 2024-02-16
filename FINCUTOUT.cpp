/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "FINCUTOUT.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: FINCUTOUT
* Description: constructor
********************************************************************/
FINCUTOUT::FINCUTOUT( const string &name )
: Atomic( name )
, fincutout_Ppin(addInputPort( "fincutout_Ppin" ))
, fincutout_Gin(addInputPort( "fincutout_Gin" ))
, fincutout_Pin(addInputPort( "fincutout_Pin" ))
, fincutout_wkpein(addInputPort( "fincutout_wkpein" ))
, fincutout_cout(addOutputPort( "fincutout_cout" ))
, fincutout_ceout(addOutputPort( "fincutout_ceout" ))
, fincutout_ccfout(addOutputPort( "fincutout_ccfout" ))
, fincutout_chout(addOutputPort( "fincutout_chout" ))
, fincutout_cwout(addOutputPort( "fincutout_cwout" ))
, fincutout_tout(addOutputPort( "fincutout_tout" ))
, fincutout_wkpeout(addOutputPort( "fincutout_wkpeout" ))
//, fincutout_time(fincutout_h, fincutout_m, fincutout_s, 0)
, fincutout_time(0,5,37,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &FINCUTOUT::initFunction()
{
	fincutout_wkpe_in = fincutout_wkpe_out = 0;
	fincutout_h = fincutout_m = fincutout_s = 0;
	fincutout_Pp = fincutout_G = fincutout_P = fincutout_c = fincutout_ce = 0;
	fincutout_ccf = fincutout_ch = fincutout_cw, fincutout_t = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &FINCUTOUT::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == fincutout_wkpein){
		fincutout_wkpe_in = msg.value();
		fincutout_t = ((fincutout_G+8)*60/fincutout_Pp)*27/32;
		fincutout_tt = (int)fincutout_t;
		fincutout_h = fincutout_tt/3600;
		fincutout_m = (fincutout_tt%3600)/60;
		fincutout_s = fincutout_tt%3600%60;
		holdIn(active,fincutout_time);
	}
	if(msg.port() == fincutout_Ppin){
		fincutout_Pp = msg.value();
	}
	if(msg.port() == fincutout_Gin){
		fincutout_G = msg.value();
	}
//	if(fincutout_wkpe_in >= 1){
//		if(msg.port() == fincutout_Ppin){
//			fincutout_Pp = msg.value();
//		}
//		if(msg.port() == fincutout_Gin){
//			fincutout_G = msg.value();
//		}
////		if(msg.port() == fincutout_Pin){
////			fincutout_P = msg.value();
////		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &FINCUTOUT::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &FINCUTOUT::outputFunction( const InternalMessage &msg )
{
	if(fincutout_wkpe_in >= 1){

		fincutout_P = 8852.7;
//		fincutout_P = 8873.3;/*train*/
//		fincutout_t = 326;/*train*/

//		fincutout_t = ((fincutout_G+4)*60/fincutout_Pp)*26/32;
//		fincutout_tt = (int)fincutout_t;
//		fincutout_h = fincutout_tt/3600;
//		fincutout_m = (fincutout_tt%3600)/60;
//	    fincutout_s = fincutout_tt%3600%60;
//	    holdIn(active,fincutout_time);
	    fincutout_wkpe_out = 1;

	    fincutout_ce = 0.8042*fincutout_P*fincutout_t/3600000;
	    fincutout_ccf = (fincutout_t/830000)*(2.85*13+0.2*13);
	    fincutout_ch = (fincutout_t/86400)*17.57*1.7;
	    fincutout_cw = 0.2*0.284375*0.05;
	    fincutout_c = fincutout_ce+fincutout_ccf+fincutout_ch+fincutout_cw;
	}
	if(fincutout_wkpe_out >= 1){
		sendOutput(msg.time(),fincutout_cout,fincutout_c);
		sendOutput(msg.time(),fincutout_ceout,fincutout_ce);
		sendOutput(msg.time(),fincutout_ccfout,fincutout_ccf);
		sendOutput(msg.time(),fincutout_chout,fincutout_ch);
		sendOutput(msg.time(),fincutout_cwout,fincutout_cw);
		sendOutput(msg.time(),fincutout_tout,fincutout_tt);
		sendOutput(msg.time(),fincutout_wkpeout,fincutout_wkpe_out);
		fincutout_wkpe_in = 0;
	}

	return *this;

}

FINCUTOUT::~FINCUTOUT()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
