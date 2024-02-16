/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __ROUCUTIN_H
#define __ROUCUTIN_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class ROUCUTIN: public Atomic
{
public:
	ROUCUTIN( const string &name = "ROUCUTIN" ) ;	 // Default constructor
	~ROUCUTIN();					// Destructor
	virtual string className() const
		{return "ROUCUTIN";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &roucutin_Ppin;
	      Port &roucutin_Gin;
	      Port &roucutin_Pin;
	      Port &roucutin_wkpein;
	      Port &roucutin_cout;
	      Port &roucutin_ceout;
	      Port &roucutin_ccfout;
	      Port &roucutin_chout;
	      Port &roucutin_cwout;
	      Port &roucutin_tout;
	      Port &roucutin_wkpeout;
	      Time roucutin_time;
	      int roucutin_wkpe_in, roucutin_wkpe_out;
	      int roucutin_tt, roucutin_h, roucutin_m, roucutin_s;
	      double roucutin_Pp, roucutin_G, roucutin_P, roucutin_c, roucutin_ce;
	      double roucutin_ccf, roucutin_ch, roucutin_cw, roucutin_t;
};	// class ROUCUTIN


#endif   //__ROUCUTIN_H 
