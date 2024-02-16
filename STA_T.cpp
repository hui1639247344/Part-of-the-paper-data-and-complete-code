/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_T.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_T
* Description: constructor
********************************************************************/
STA_T::STA_T( const string &name )
: Atomic( name )
,tout(addOutputPort( "tout" ))
,ttmpout(addOutputPort( "ttmpout" ))
,t1in(addInputPort( "t1in" ))
,t2in(addInputPort( "t2in" ))
,t3in(addInputPort( "t3in" ))
,t4in(addInputPort( "t4in" ))
,t5in(addInputPort( "t5in" ))
,t6in(addInputPort( "t6in" ))
,statime_t(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_T::initFunction()
{
	t1 = t2 = t3 = t4 = t5 = t6 = t = ttmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_T::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == t1in){
		holdIn(active,statime_t);
			t1 = msg.value();
			ttmp = t1;
		}
		if(msg.port() == t2in){
			holdIn(active,statime_t);
				t2 = msg.value();
				ttmp = t2;
			}
		if(msg.port() == t3in){
			holdIn(active,statime_t);
				t3 = msg.value();
				ttmp = t3;
			}
		if(msg.port() == t4in){
			holdIn(active,statime_t);
				t4 = msg.value();
				ttmp = t4;
			}
		if(msg.port() == t5in){
			holdIn(active,statime_t);
				t5 = msg.value();
				ttmp = t5;
			}
		if(msg.port() == t6in){
			holdIn(active,statime_t);
				t6 = msg.value();
				ttmp = t6;
			}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_T::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_T::outputFunction( const InternalMessage &msg )
{
	if(ttmp != 0){
			t += ttmp;
			sendOutput( msg.time(), tout, t) ;
			sendOutput( msg.time(), ttmpout, ttmp) ;
			ttmp = 0;
		}
	return *this;

}

STA_T::~STA_T()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
