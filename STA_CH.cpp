/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "STA_CH.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: STA_CH
* Description: constructor
********************************************************************/
STA_CH::STA_CH( const string &name )
: Atomic( name )
,chout(addOutputPort( "chout" ))
,chtmpout(addOutputPort( "chtmpout" ))
,ch1in(addInputPort( "ch1in" ))
,ch2in(addInputPort( "ch2in" ))
,ch3in(addInputPort( "ch3in" ))
,ch4in(addInputPort( "ch4in" ))
,ch5in(addInputPort( "ch5in" ))
,ch6in(addInputPort( "ch6in" ))
,statime_ch(0,0,0,0)
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &STA_CH::initFunction()
{
	ch1 = ch2 = ch3 = ch4 = ch5 = ch6 = ch = chtmp = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &STA_CH::externalFunction( const ExternalMessage &msg )
{
	if(msg.port() == ch1in){
		holdIn(active,statime_ch);
			ch1 = msg.value();
			chtmp = ch1;
		}
		if(msg.port() == ch2in){
			holdIn(active,statime_ch);
				ch2 = msg.value();
				chtmp = ch2;
			}
		if(msg.port() == ch3in){
			holdIn(active,statime_ch);
				ch3 = msg.value();
				chtmp = ch3;
			}
		if(msg.port() == ch4in){
			holdIn(active,statime_ch);
				ch4 = msg.value();
				chtmp = ch4;
			}
		if(msg.port() == ch5in){
			holdIn(active,statime_ch);
				ch5 = msg.value();
				chtmp = ch5;
			}
		if(msg.port() == ch6in){
			holdIn(active,statime_ch);
				ch6 = msg.value();
				chtmp = ch6;
			}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &STA_CH::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &STA_CH::outputFunction( const InternalMessage &msg )
{
	if(chtmp != 0){
			ch += chtmp;
			sendOutput( msg.time(), chout, ch) ;
			sendOutput( msg.time(), chtmpout, chtmp) ;
			chtmp = 0;
		}
	return *this;

}

STA_CH::~STA_CH()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
