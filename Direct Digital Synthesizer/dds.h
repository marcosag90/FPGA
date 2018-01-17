#ifndef __DDS_H__
#define __DDS_H__
#include <ap_fixed.h>
#include <ap_int.h>
#define FS	245.76E6
#define	F	80.957E6
#define TRIG_LUT_DEPTH_FULL_CYCLE	8192*2*2
#define TRIG_LUT_DEPTH	2048*2*2
#define PI 3.1416
#define NBITSADDRESS	14+1+1

// define number representation for filter coefficients
#define TRIG_LUT_NBITS 20
#define TRIG_LUT_NBITS_FRAC 19
#define TRIG_LUT_NBITS_INT TRIG_LUT_NBITS - TRIG_LUT_NBITS_FRAC

// define number representation for the output sine and cosine
#define SINCOS_NBITS 32
#define SINCOS_NBITS_FRAC 31
#define SINCOS_NBITS_INT SINCOS_NBITS - SINCOS_NBITS_FRAC

// define number repre.sentation for phase increment

#if 1
#define PHS_INC_NBITS 32
#define PHS_INC_NBITS_FRAC 10
#define PHS_INC_NBITS_INT PHS_INC_NBITS - PHS_INC_NBITS_FRAC
#endif

// define number representation for filter accumulator
#define ACC_NBITS 32
#define ACC_NBITS_FRAC 10
#define ACC_NBITS_INT ACC_NBITS - ACC_NBITS_FRAC

typedef ap_fixed<TRIG_LUT_NBITS, TRIG_LUT_NBITS_INT>	TrigLUT;
typedef ap_fixed<SINCOS_NBITS, SINCOS_NBITS_INT>	SinCosType;
typedef ap_fixed<PHS_INC_NBITS, PHS_INC_NBITS_INT>	PhsInc;
typedef ap_fixed<ACC_NBITS, ACC_NBITS_INT>	PhaseAcc;
typedef ap_uint<NBITSADDRESS-3>	Address;
typedef ap_uint<NBITSADDRESS>	Address_long;

// function prototypes
void init_trig_lut(TrigLUT lut[], const int N); //function prototype
void dds(PhsInc phaseInc, SinCosType* sin, SinCosType* cos);

#endif
