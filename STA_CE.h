/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_CE_H
#define __STA_CE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_CE: public Atomic
{
public:
	STA_CE( const string &name = "STA_CE" ) ;	 // Default constructor
	~STA_CE();					// Destructor
	virtual string className() const
		{return "STA_CE";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &ce1in;
	Port &ce2in;
	Port &ce3in;
	Port &ce4in;
	Port &ce5in;
	Port &ce6in;
	Port &ceout;
	Port &cetmpout;
	Time statime_ce;
	double ce1,ce2,ce3,ce4,ce5,ce6,ce,cetmp;
};	// class STA_CE


#endif   //__STA_CE_H 
