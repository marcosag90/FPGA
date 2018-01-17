#ifndef __FIR_H__
#define __FIR_H__
#include "ap_fixed.h"
#define N 23
#define epsilon 1E-3

// define number representation for filter coefficients
#define COEFF_NBITS 16
#define COEFF_NBITS_FRAC 15
#define COEFF_NBITS_INT COEFF_NBITS - COEFF_NBITS_FRAC

// define number representation for filter input data
#define IDATA_NBITS 16
#define IDATA_NBITS_FRAC 15
#define IDATA_NBITS_INT IDATA_NBITS - IDATA_NBITS_FRAC

// define number representation for filter output 

#if 1
#define ODATA_NBITS 16
#define ODATA_NBITS_FRAC 15
#define ODATA_NBITS_INT ODATA_NBITS - ODATA_NBITS_FRAC
#endif

#if 0
#define ODATA_NBITS 24 
#define ODATA_NBITS_FRAC 20
#define ODATA_NBITS_INT ODATA_NBITS - ODATA_NBITS_FRAC
#endif

// define number representation for filter accumulator
#define ACC_NBITS 36
#define ACC_NBITS_FRAC 25
#define ACC_NBITS_INT ACC_NBITS - ACC_NBITS_FRAC

typedef ap_fixed<COEFF_NBITS, COEFF_NBITS_INT>	Coeff;
typedef ap_fixed<COEFF_NBITS, COEFF_NBITS_INT>	coef_t;
typedef ap_fixed<IDATA_NBITS, IDATA_NBITS_INT>	idata_t;
typedef ap_fixed<ODATA_NBITS, ODATA_NBITS_INT>	odata_t;
typedef ap_fixed<ACC_NBITS, ACC_NBITS_INT>	Acc;

// function prototypes
void fir_real (idata_t x, idata_t x2, odata_t *y);
void fir_imag (idata_t x, idata_t x2, odata_t *y2);
void fir(idata_t xr, idata_t xi, idata_t xr2, idata_t xi2, odata_t *yr, odata_t *yi);

#endif
