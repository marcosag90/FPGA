#include <stdio.h>

#include "dds.h"
#define SIMSIZE 8192

int main(void)
{
	float phase=0.0;
	float samples_period=FS/F;
	float increment=TRIG_LUT_DEPTH_FULL_CYCLE/samples_period;
	FILE *f;
	f=fopen("Z:\\FPGA\\Project5\\SinOutput1.dat", "w");
	SinCosType sin[SIMSIZE], cos[SIMSIZE];
	Address test=0;

	printf("Phase Inc = %f", float(increment));

	for(int i=0; i<SIMSIZE; i++)
	{
		dds(PhsInc(increment), &sin[i], &cos[i]);
		//samples_period/TRIG_LUT_DEPTH_FULL_CYCLE)
		//printf("%f\t%f\n", float(sin[i]), float(cos[i]));
		fprintf(f, "%f\t %f\n", float(sin[i]), float(cos[i]));
	}
	fclose(f);
	return 0;
}
