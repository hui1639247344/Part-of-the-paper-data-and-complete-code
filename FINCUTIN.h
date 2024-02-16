/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __FINCUTIN_H
#define __FINCUTIN_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class FINCUTIN: public Atomic
{
public:
	FINCUTIN( const string &name = "FINCUTIN" ) ;	 // Default constructor
	~FINCUTIN();					// Destructor
	virtual string className() const
		{return "FINCUTIN";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &fincutin_Ppin;
	      Port &fincutin_Gin;
	      Port &fincutin_Pin;
	      Port &fincutin_wkpein;
	      Port &fincutin_cout;
	      Port &fincutin_ceout;
	      Port &fincutin_ccfout;
	      Port &fincutin_chout;
	      Port &fincutin_cwout;
	      Port &fincutin_tout;
	      Port &fincutin_wkpeout;
	      Time fincutin_time;
	      int fincutin_wkpe_in, fincutin_wkpe_out;
	      int fincutin_tt, fincutin_h, fincutin_m, fincutin_s;
	      double fincutin_Pp, fincutin_G, fincutin_P, fincutin_c, fincutin_ce;
	      double fincutin_ccf, fincutin_ch, fincutin_cw, fincutin_t;
};	// class FINCUTIN


#endif   //__FINCUTIN_H 
