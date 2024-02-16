/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_CCF_H
#define __STA_CCF_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_CCF: public Atomic
{
public:
	STA_CCF( const string &name = "STA_CCF" ) ;	 // Default constructor
	~STA_CCF();					// Destructor
	virtual string className() const
		{return "STA_CCF";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &ccf1in;
		Port &ccf2in;
		Port &ccf3in;
		Port &ccf4in;
		Port &ccf5in;
		Port &ccf6in;
		Port &ccfout;
		Port &ccftmpout;
		Time statime_ccf;
		double ccf1,ccf2,ccf3,ccf4,ccf5,ccf6,ccf,ccftmp;
};	// class STA_CCF


#endif   //__STA_CCF_H 
