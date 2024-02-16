/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __STA_CCE_H
#define __STA_CCE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class STA_CCE: public Atomic
{
public:
	STA_CCE( const string &name = "STA_CCE" ) ;	 // Default constructor
	~STA_CCE();					// Destructor
	virtual string className() const
		{return "STA_CCE";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &Frin;
	Port &cin;
	Port &tin;
	Port &cceout;
	Port &cce_wkpein;
	Time statime_cce;
	int wkpe;
	double cce_t,cce_c,cce_m,cce_e,cce_q,cce_fr,cce;
};	// class STA_CCE


#endif   //__STA_CCE_H 
