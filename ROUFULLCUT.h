/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __ROUFULLCUT_H
#define __ROUFULLCUT_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class ROUFULLCUT: public Atomic
{
public:
	ROUFULLCUT( const string &name = "ROUFULLCUT" ) ;	 // Default constructor
	~ROUFULLCUT();					// Destructor
	virtual string className() const
		{return "ROUFULLCUT";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &roufullcut_Ppin;
	      Port &roufullcut_Gin;
	      Port &roufullcut_Pin;
	      Port &roufullcut_wkpein;
	      Port &roufullcut_cout;
	      Port &roufullcut_ceout;
	      Port &roufullcut_ccfout;
	      Port &roufullcut_chout;
	      Port &roufullcut_cwout;
	      Port &roufullcut_tout;
	      Port &roufullcut_wkpeout;
	      Time roufullcut_time;
	      int roufullcut_wkpe_in, roufullcut_wkpe_out;
	      int roufullcut_tt, roufullcut_h, roufullcut_m, roufullcut_s;
	      double roufullcut_Pp, roufullcut_G, roufullcut_P, roufullcut_c, roufullcut_ce;
	      double roufullcut_ccf, roufullcut_ch, roufullcut_cw, roufullcut_t;
};	// class ROUFULLCUT


#endif   //__ROUFULLCUT_H 
