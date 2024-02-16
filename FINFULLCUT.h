/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __FINFULLCUT_H
#define __FINFULLCUT_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class FINFULLCUT: public Atomic
{
public:
	FINFULLCUT( const string &name = "FINFULLCUT" ) ;	 // Default constructor
	~FINFULLCUT();					// Destructor
	virtual string className() const
		{return "FINFULLCUT";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &finfullcut_Ppin;
	      Port &finfullcut_Gin;
	      Port &finfullcut_Pin;
	      Port &finfullcut_wkpein;
	      Port &finfullcut_cout;
	      Port &finfullcut_ceout;
	      Port &finfullcut_ccfout;
	      Port &finfullcut_chout;
	      Port &finfullcut_cwout;
	      Port &finfullcut_tout;
	      Port &finfullcut_wkpeout;
	      Time finfullcut_time;
	      int finfullcut_wkpe_in, finfullcut_wkpe_out;
	      int finfullcut_tt, finfullcut_h, finfullcut_m, finfullcut_s;
	      double finfullcut_Pp, finfullcut_G, finfullcut_P, finfullcut_c, finfullcut_ce;
	      double finfullcut_ccf, finfullcut_ch, finfullcut_cw, finfullcut_t;
};	// class FINFULLCUT


#endif   //__FINFULLCUT_H 
