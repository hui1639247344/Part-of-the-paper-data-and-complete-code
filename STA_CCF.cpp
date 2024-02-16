/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_CCF.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_CCF
* Description: constructor
********************************************************************/
STA_CCF::STA_CCF( const string &name )
: Atomic( name )
,ccfout(addOutputPort( "ccfout" ))
,ccftmpout(addOutputPort( "ccftmpout" ))
,ccf1in(addInputPort( "ccf1in" ))
,ccf2in(addInputPort( "ccf2in" ))
,ccf3in(addInputPort( "ccf3in" ))
,ccf4in(addInputPort( "ccf4in" ))
,ccf5in(addInputPort( "ccf5in" ))
,ccf6in(addInputPort( "ccf6in" ))
,statime_ccf(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_CCF::initFunction()
{
	ccf1 = ccf2 = ccf3 = ccf4 = ccf5 = ccf6 = ccf = ccftmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_CCF::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == ccf1in){
		holdIn(active,statime_ccf);
			ccf1 = msg.value();
			ccftmp = ccf1;
		}
		if(msg.port() == ccf2in){
			holdIn(active,statime_ccf);
				ccf2 = msg.value();
				ccftmp = ccf2;
			}
		if(msg.port() == ccf3in){
			holdIn(active,statime_ccf);
				ccf3 = msg.value();
				ccftmp = ccf3;
			}
		if(msg.port() == ccf4in){
			holdIn(active,statime_ccf);
				ccf4 = msg.value();
				ccftmp = ccf4;
			}
		if(msg.port() == ccf5in){
			holdIn(active,statime_ccf);
				ccf5 = msg.value();
				ccftmp = ccf5;
			}
		if(msg.port() == ccf6in){
			holdIn(active,statime_ccf);
				ccf6 = msg.value();
				ccftmp = ccf6;
			}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_CCF::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_CCF::outputFunction( const InternalMessage &msg )
{
	if(ccftmp != 0){
		ccf += ccftmp;
		sendOutput( msg.time(), ccfout, ccf) ;
		sendOutput( msg.time(), ccftmpout, ccftmp) ;
		ccftmp = 0;
	}
	return *this;

}

STA_CCF::~STA_CCF()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
