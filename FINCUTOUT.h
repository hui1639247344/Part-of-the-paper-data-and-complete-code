/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __FINCUTOUT_H
#define __FINCUTOUT_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class FINCUTOUT: public Atomic
{
public:
	FINCUTOUT( const string &name = "FINCUTOUT" ) ;	 // Default constructor
	~FINCUTOUT();					// Destructor
	virtual string className() const
		{return "FINCUTOUT";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &fincutout_Ppin;
	      Port &fincutout_Gin;
	      Port &fincutout_Pin;
	      Port &fincutout_wkpein;
	      Port &fincutout_cout;
	      Port &fincutout_ceout;
	      Port &fincutout_ccfout;
	      Port &fincutout_chout;
	      Port &fincutout_cwout;
	      Port &fincutout_tout;
	      Port &fincutout_wkpeout;
	      Time fincutout_time;
	      int fincutout_wkpe_in, fincutout_wkpe_out;
	      int fincutout_tt, fincutout_h, fincutout_m, fincutout_s;
	      double fincutout_Pp, fincutout_G, fincutout_P, fincutout_c, fincutout_ce;
	      double fincutout_ccf, fincutout_ch, fincutout_cw, fincutout_t;
};	// class FINCUTOUT


#endif   //__FINCUTOUT_H 
