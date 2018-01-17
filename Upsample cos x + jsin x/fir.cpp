#include "fir.h"
#include "design.h"

void fir(idata_t xr, idata_t xi, idata_t xr2, idata_t xi2, odata_t *yr, odata_t *yi)
{
	fir_real(xr, xr2, yr);
	fir_imag(xi,xi2, yi);
}

void fir_real (idata_t x, idata_t x2, odata_t *y)
{

	static const Coeff coeff[] =
			{
				#include "hband_fltr_coeff.dat"		//Even coeficients will belong to one filter
			};											//Odd coeficients will belong to the other one

			static idata_t shift_reg[N], shift_reg2[N];
			Acc acc1=0, acc2=0;
			int i, j, n=6;

			shift_reg[0] = x;
			shift_reg2[0] = x2;

		 	AccumLoopH1: for (i=0, j=0; i<n; i++, j+=2)
		  	{
		 		 	acc1 +=Acc( Acc((shift_reg[i]+shift_reg[12-1-i]))*Acc(coeff[j]));		//Implement symetry here

		 	}
		 	acc2 = shift_reg2[n];

		 	MemUpdate: for (i=N-1; i>0; i--)
			 {
				shift_reg[i] = shift_reg[i-1];
				shift_reg2[i] = shift_reg2[i-1];
			 }

		 	*y=odata_t(acc1)+odata_t(acc2);
}
void fir_imag (idata_t x, idata_t x2, odata_t *y2)
{
	static const Coeff coeff[] =
		{
			#include "hband_fltr_coeff.dat"		//Even coeficients will belong to one filter
		};											//Odd coeficients will belong to the other one

		static idata_t shift_reg[N], shift_reg2[N];
		Acc acc1=0, acc2=0;
		int i, j, n=6;

		shift_reg[0] = x;
		shift_reg2[0] = x2;

	 	AccumLoopH1: for (i=0, j=0; i<n; i++, j+=2)
	  	{
	 		 	acc1 += Acc((shift_reg[i]+shift_reg[12-1-i]))*Acc(coeff[j]);		//Implement symetry here

	 	}
	 	acc2 = shift_reg2[6];

	 	MemUpdate: for (i=N-1; i>0; i--)
		 {
			shift_reg[i] = shift_reg[i-1];
			shift_reg2[i] = shift_reg2[i-1];
		 }

	 	*y2=odata_t(acc1)+odata_t(acc2);
}
