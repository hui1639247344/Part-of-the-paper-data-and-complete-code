/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_CCE.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_CCE
* Description: constructor
********************************************************************/
STA_CCE::STA_CCE( const string &name )
: Atomic( name )
,cceout(addOutputPort( "cceout" ))
,Frin(addInputPort( "Frin" ))
,cin(addInputPort( "cin" ))
,tin(addInputPort( "tin" ))
,cce_wkpein(addInputPort( "cce_wkpein" ))
,statime_cce(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_CCE::initFunction()
{
	wkpe = 0;
	cce_t = cce_c = cce_fr = cce_m = cce_e = cce_q = cce = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_CCE::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == cce_wkpein){
		holdIn(active,statime_cce);
		wkpe = msg.value();
	}
	if(msg.port() == Frin){
		holdIn(active,statime_cce);
		cce_fr = msg.value();
	}
	if(msg.port() == cin){
		holdIn(active,statime_cce);
		cce_c = msg.value();
	}
	if(msg.port() == tin){
		holdIn(active,statime_cce);
		cce_t = msg.value();
	}
//	if(wkpe == 1){
//		if(msg.port() == Frin){
//			holdIn(active,statime_cce);
//			cce_fr = msg.value();
//		}
//		if(msg.port() == cin){
//			holdIn(active,statime_cce);
//			cce_c = msg.value();
//		}
//		if(msg.port() == tin){
//			holdIn(active,statime_cce);
//			cce_t = msg.value();
//		}
//	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_CCE::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_CCE::outputFunction( const InternalMessage &msg )
{
	if(wkpe >= 1){
		cce_m = 0.74*(cce_c/0.8042)+(cce_t/830000)*13*21.5+(cce_t/86400)*1200;
		cce_e = 1/(cce_t);
		cce_q = cce_fr;
		cce = (0.31*(34.96-cce_m)/(34.96-22.84)+0.29*(cce_e-0.00046019)/(0.00070621-0.00046169)+0.4*(68.9-cce_q)/(68.9-2.1))/cce_c;
		sendOutput( msg.time(), cceout, cce) ;
	}
	return *this;

}

STA_CCE::~STA_CCE()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
