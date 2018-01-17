#include "dds.h"
#include <ap_fixed.h>
#include <math.h>


void init_trig_lut(TrigLUT lut[], const int N)
{
 	int i;
 	double sine_val;

	for (i=0; i<N; i++)
	{
		sine_val = sin(2*PI*(0.5+(double)i)/(TRIG_LUT_DEPTH_FULL_CYCLE));
		lut[i] = sine_val;
	}
}

void dds(PhsInc phaseInc, SinCosType* sin, SinCosType* cos)
{
	TrigLUT trigLUT[TRIG_LUT_DEPTH] ;	// allocate memory for the sine/cosine LUT (or trig LUT)
	static PhaseAcc phaseAcc=0.0;
	Address sin_address=0, cos_address=0;
	Address_long full_address;

	init_trig_lut(trigLUT, TRIG_LUT_DEPTH);
	//printf("Phase %f\t",float(phaseAcc));
	full_address=Address_long(phaseAcc);
	if((full_address[NBITSADDRESS-3])==0)		//check bit 2
	{
		sin_address=Address(full_address);
		cos_address=~Address(full_address);
		//printf("Sin Address: %d\n", int(sin_address));
		//printf("Cos Address: %d\n", int(cos_address));
	}
	else
	{
		sin_address=~Address(full_address);
		//printf("Sin Address: %i\n", int(full_address));
		cos_address=Address(full_address);
		//printf("Cos Address: %d\n", int(cos_address));
	}
	if(full_address[NBITSADDRESS-2])
		*sin=-SinCosType(trigLUT[sin_address]);
	else
		*sin=SinCosType(trigLUT[sin_address]);
	if(full_address>TRIG_LUT_DEPTH & full_address<3*TRIG_LUT_DEPTH)//if((full_address[NBITSADDRESS-3])^(full_address[NBITSADDRESS-2]))
		*cos=-SinCosType(trigLUT[cos_address]);
	else
		*cos=SinCosType(trigLUT[cos_address]);

	//printf("%f\n", float(*cos));

	phaseAcc+=(PhaseAcc(phaseInc));
	if(phaseAcc>=TRIG_LUT_DEPTH_FULL_CYCLE)
		phaseAcc=phaseAcc-TRIG_LUT_DEPTH_FULL_CYCLE;
 	return;
}
