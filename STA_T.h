/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_T_H
#define __STA_T_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_T: public Atomic
{
public:
	STA_T( const string &name = "STA_T" ) ;	 // Default constructor
	~STA_T();					// Destructor
	virtual string className() const
		{return "STA_T";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &t1in;
		Port &t2in;
		Port &t3in;
		Port &t4in;
		Port &t5in;
		Port &t6in;
		Port &tout;
		Port &ttmpout;
		Time statime_t;
		double t1,t2,t3,t4,t5,t6,t,ttmp;
};	// class STA_T


#endif   //__STA_T_H 
