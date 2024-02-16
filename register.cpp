/*******************************************************************
*
*  Auto Generated File
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  This registration file is used to describe the atomic models that can be used to compose coupled models.
*
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico
#include "ROUCUTIN.h"        // class ROUCUTIN
#include "ROUFULLCUT.h"	// class ROUFULLCUT
#include "ROUCUTOUT.h"	// class ROUCUTOUT
#include "FINCUTIN.h"	// class FINCUTIN
#include "FINFULLCUT.h"	// class FINFULLCUT
#include "FINCUTOUT.h"	// class FINCUTOUT
#include "STA_C.h"	// class STA_C
#include "STA_CE.h"	// class STA_CE
#include "STA_CCF.h"	// class STA_CCF
#include "STA_CH.h"	// class STA_CH
#include "STA_CW.h"	// class STA_CW
#include "STA_T.h"	// class STA_T
#include "STA_CCE.h"	// class STA_CCE

void MainSimulator::registerNewAtomics()
{
	// Register Built-in models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;

	// Register custom models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ROUCUTIN>(), "ROUCUTIN" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ROUFULLCUT>() , "ROUFULLCUT" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ROUCUTOUT>() , "ROUCUTOUT" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FINCUTIN>() , "FINCUTIN" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FINFULLCUT>() , "FINFULLCUT" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FINCUTOUT>() , "FINCUTOUT" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_C>() , "STA_C" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_CE>() , "STA_CE" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_CCF>() , "STA_CCF" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_CH>() , "STA_CH" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_CW>() , "STA_CW" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_T>() , "STA_T" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<STA_CCE>() , "STA_CCE" ) ;
}
