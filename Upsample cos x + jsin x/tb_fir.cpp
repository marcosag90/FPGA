#include <iostream>
#include <fstream>
#include "design.h"
#include "fir.h"
#define M 1000
float rms_error(unsigned long n, float e);


int main(void)
{
	//////////////////////////////////////////////////////////////
	//					Variable Declaration and
	//						Initialization
	//////////////////////////////////////////////////////////////
	odata_t out_filter_real[int(M)+1];
	odata_t out_filter_imag[int(M)+1];
	FILE *data_export;
	static const idata_t data_in[] =
		{
				#include "filter_input.dat"
		};

	static const odata_t out_real_reference[] =
		{
			#include "filter_output_Real_reference.dat"
		};
	static const odata_t out_imaginary_reference[] =
			{
				#include "filter_output_Imaginary_reference.dat"
			};
	float temp1, temp2, ereal=0.0, eimag=0.0;

	////////////////////////////////////////////////////////////////
	//						Filtering
	////////////////////////////////////////////////////////////////
	Filter:for(int i=0, j=0; i<M; i+=4, j++)
	{
			fir(data_in[i], data_in[i+1],data_in[i+2],data_in[i+3], &out_filter_real[j], &out_filter_imag[j]);

	}

	/////////////////////////////////////////////////////////////////
	//						Error Calculation
	/////////////////////////////////////////////////////////////////
	for(int i=1; i<M/4; i++)
	{
		temp1=float(out_real_reference[i]);
		temp2=float(out_filter_real[i]);
		ereal+=(temp1-temp2)*(temp1-temp2);
		temp1=float(out_imaginary_reference[i]);
		temp2=float(out_filter_imag[i]);
		eimag+=(temp1-temp2)*(temp1-temp2);
	}

	/////////////////////////////////////////////////////////////////
	//						Result Printing
	//////////////////////////////////////////////////////////////////
	printf("Real Output filter\t Real Output Reference\t Imaginary Output Filter\t Imaginary Output Reference\n");
	data_export=fopen("Z:\\FPGA\\Final_Part_2\\Output_Vivaldo.dat", "w+");
	for(int i=0; i<M/4; i++)
	{
		fprintf(data_export, "%f\n%f\n", float(out_filter_real[i]), float(out_filter_imag[i]));
		printf("%f\t\t\t\t %f\t\t\t\t %f\t\t\t\t %f\n", float(out_filter_real[i]), float(out_real_reference[i]), float(out_filter_imag[i]), float(out_imaginary_reference[i]));
	}
	fclose(data_export);
	printf("The rms error for the real part is is equal to %f\n", rms_error(M/4,ereal));
	printf("The rms error for the imaginary part is is equal to %f\n", rms_error(M/4,eimag));
	return 0;
}


float rms_error(unsigned long n, float e)
{
	return sqrt(e/n);

}
