/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_C.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_C
* Description: constructor
********************************************************************/
STA_C::STA_C( const string &name )
: Atomic( name )
,cout(addOutputPort( "cout" ))
,ctmpout(addOutputPort( "ctmpout" ))
,c1in(addInputPort( "c1in" ))
,c2in(addInputPort( "c2in" ))
,c3in(addInputPort( "c3in" ))
,c4in(addInputPort( "c4in" ))
,c5in(addInputPort( "c5in" ))
,c6in(addInputPort( "c6in" ))
,statime_c(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_C::initFunction()
{
	c1 = c2 = c3 = c4 = c5 = c6 = c = ctmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_C::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == c1in){
		holdIn(active,statime_c);
			c1 = msg.value();
			ctmp = c1;
		}
		if(msg.port() == c2in){
			holdIn(active,statime_c);
				c2 = msg.value();
				ctmp = c2;
			}
		if(msg.port() == c3in){
			holdIn(active,statime_c);
				c3 = msg.value();
				ctmp = c3;
			}
		if(msg.port() == c4in){
			holdIn(active,statime_c);
				c4 = msg.value();
				ctmp = c4;
			}
		if(msg.port() == c5in){
			holdIn(active,statime_c);
				c5 = msg.value();
				ctmp = c5;
			}
		if(msg.port() == c6in){
			holdIn(active,statime_c);
				c6 = msg.value();
				ctmp = c6;
			}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_C::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_C::outputFunction( const InternalMessage &msg )
{
	if(ctmp != 0){
		c += ctmp;
		sendOutput( msg.time(), cout, c) ;
		sendOutput( msg.time(), ctmpout, ctmp) ;
		ctmp = 0;
	}
	return *this;

}

STA_C::~STA_C()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
