/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_CW.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_CW
* Description: constructor
********************************************************************/
STA_CW::STA_CW( const string &name )
: Atomic( name )
,cwout(addOutputPort( "cwout" ))
,cwtmpout(addOutputPort( "cwtmpout" ))
,cw1in(addInputPort( "cw1in" ))
,cw2in(addInputPort( "cw2in" ))
,cw3in(addInputPort( "cw3in" ))
,cw4in(addInputPort( "cw4in" ))
,cw5in(addInputPort( "cw5in" ))
,cw6in(addInputPort( "cw6in" ))
,statime_cw(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_CW::initFunction()
{
	cw1 = cw2 = cw3 = cw4 = cw5 = cw6 = cw = cwtmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_CW::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == cw1in){
		holdIn(active,statime_cw);
			cw1 = msg.value();
			cwtmp = cw1;
		}
		if(msg.port() == cw2in){
			holdIn(active,statime_cw);
				cw2 = msg.value();
				cwtmp = cw2;
			}
		if(msg.port() == cw3in){
			holdIn(active,statime_cw);
				cw3 = msg.value();
				cwtmp = cw3;
			}
		if(msg.port() == cw4in){
			holdIn(active,statime_cw);
				cw4 = msg.value();
				cwtmp = cw4;
			}
		if(msg.port() == cw5in){
			holdIn(active,statime_cw);
				cw5 = msg.value();
				cwtmp = cw5;
			}
		if(msg.port() == cw6in){
			holdIn(active,statime_cw);
				cw6 = msg.value();
				cwtmp = cw6;
			}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_CW::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_CW::outputFunction( const InternalMessage &msg )
{
	if(cwtmp != 0){
			cw += cwtmp;
			sendOutput( msg.time(), cwout, cw) ;
			sendOutput( msg.time(), cwtmpout, cwtmp) ;
			cwtmp = 0;
		}
	return *this;

}

STA_CW::~STA_CW()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
