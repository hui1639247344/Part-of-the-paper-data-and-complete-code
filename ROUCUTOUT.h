/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __ROUCUTOUT_H
#define __ROUCUTOUT_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class ROUCUTOUT: public Atomic
{
public:
	ROUCUTOUT( const string &name = "ROUCUTOUT" ) ;	 // Default constructor
	~ROUCUTOUT();					// Destructor
	virtual string className() const
		{return "ROUCUTOUT";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &roucutout_Ppin;
	      Port &roucutout_Gin;
	      Port &roucutout_Pin;
	      Port &roucutout_wkpein;
	      Port &roucutout_cout;
	      Port &roucutout_ceout;
	      Port &roucutout_ccfout;
	      Port &roucutout_chout;
	      Port &roucutout_cwout;
	      Port &roucutout_tout;
	      Port &roucutout_wkpeout;
	      Time roucutout_time;
	      int roucutout_wkpe_in, roucutout_wkpe_out;
	      int roucutout_tt, roucutout_h, roucutout_m, roucutout_s;
	      double roucutout_Pp, roucutout_G, roucutout_P, roucutout_c, roucutout_ce;
	      double roucutout_ccf, roucutout_ch, roucutout_cw, roucutout_t;
};	// class ROUCUTOUT


#endif   //__ROUCUTOUT_H 
