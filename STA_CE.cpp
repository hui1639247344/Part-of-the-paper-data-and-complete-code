/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_CE.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_CE
* Description: constructor
********************************************************************/
STA_CE::STA_CE( const string &name )
: Atomic( name )
,ceout(addOutputPort( "ceout" ))
,cetmpout(addOutputPort( "cetmpout" ))
,ce1in(addInputPort( "ce1in" ))
,ce2in(addInputPort( "ce2in" ))
,ce3in(addInputPort( "ce3in" ))
,ce4in(addInputPort( "ce4in" ))
,ce5in(addInputPort( "ce5in" ))
,ce6in(addInputPort( "ce6in" ))
,statime_ce(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_CE::initFunction()
{
	ce1 = ce2 = ce3 = ce4 = ce5 = ce6 = ce = cetmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_CE::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == ce1in){
		holdIn(active,statime_ce);
		ce1 = msg.value();
		cetmp = ce1;
	}
	if(msg.port() == ce2in){
		holdIn(active,statime_ce);
			ce2 = msg.value();
			cetmp = ce2;
		}
	if(msg.port() == ce3in){
		holdIn(active,statime_ce);
			ce3 = msg.value();
			cetmp = ce3;
		}
	if(msg.port() == ce4in){
		holdIn(active,statime_ce);
			ce4 = msg.value();
			cetmp = ce4;
		}
	if(msg.port() == ce5in){
		holdIn(active,statime_ce);
			ce5 = msg.value();
			cetmp = ce5;
		}
	if(msg.port() == ce6in){
		holdIn(active,statime_ce);
			ce6 = msg.value();
			cetmp = ce6;
		}
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_CE::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_CE::outputFunction( const InternalMessage &msg )
{
	if(cetmp != 0){
		ce += cetmp;
		sendOutput( msg.time(), ceout, ce) ;
		sendOutput( msg.time(), cetmpout, cetmp) ;
		cetmp = 0;
	}
	return *this;

}

STA_CE::~STA_CE()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
