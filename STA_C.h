/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_C_H
#define __STA_C_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_C: public Atomic
{
public:
	STA_C( const string &name = "STA_C" ) ;	 // Default constructor
	~STA_C();					// Destructor
	virtual string className() const
		{return "STA_C";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &c1in;
		Port &c2in;
		Port &c3in;
		Port &c4in;
		Port &c5in;
		Port &c6in;
		Port &cout;
		Port &ctmpout;
		Time statime_c;
		double c1,c2,c3,c4,c5,c6,c,ctmp;
};	// class STA_C


#endif   //__STA_C_H 
