/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_CH_H
#define __STA_CH_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_CH: public Atomic
{
public:
	STA_CH( const string &name = "STA_CH" ) ;	 // Default constructor
	~STA_CH();					// Destructor
	virtual string className() const
		{return "STA_CH";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &ch1in;
		Port &ch2in;
		Port &ch3in;
		Port &ch4in;
		Port &ch5in;
		Port &ch6in;
		Port &chout;
		Port &chtmpout;
		Time statime_ch;
		double ch1,ch2,ch3,ch4,ch5,ch6,ch,chtmp;
};	// class STA_CH


#endif   //__STA_CH_H 
