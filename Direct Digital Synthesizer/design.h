#ifndef __DESIGN__
#define __DESIGN__

#include <complex>
#include <ap_fixed.h>

#define CABS_EPS 1E-3				// error tolerance for cabs function
#define NUM_VECTORS 1000

//#define DEBUG

#if 0
#define NBITS 24 
#define NBITS_FRAC 21 
#endif

#if 0
#define NBITS 20 
#define NBITS_FRAC 17
#endif

#if 1
#define NBITS 18 
#define NBITS_FRAC 15
#endif

#if 0
#define NBITS 12 
#define NBITS_FRAC 9
#endif

#if 0
#define NBITS 8 
#define NBITS_FRAC 5
#endif

#if 0
#define NBITS 24 
#define NBITS_FRAC 20 
#endif

#define NBITS_INT NBITS-NBITS_FRAC
#define RECIP_NITERS 8
#if 0
typedef int data_t
#endif

#if 1
typedef ap_fixed<NBITS, NBITS_INT, AP_TRN, AP_WRAP> data_t_;
typedef std::complex<data_t_> data_t;
#endif


void one_on_cabs_squared(data_t x, data_t_* y);
data_t_ Recip(data_t_ a);

#endif
