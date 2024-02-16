/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_CW_H
#define __STA_CW_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_CW: public Atomic
{
public:
	STA_CW( const string &name = "STA_CW" ) ;	 // Default constructor
	~STA_CW();					// Destructor
	virtual string className() const
		{return "STA_CW";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &cw1in;
		Port &cw2in;
		Port &cw3in;
		Port &cw4in;
		Port &cw5in;
		Port &cw6in;
		Port &cwout;
		Port &cwtmpout;
		Time statime_cw;
		double cw1,cw2,cw3,cw4,cw5,cw6,cw,cwtmp;
};	// class STA_CW


#endif   //__STA_CW_H 
