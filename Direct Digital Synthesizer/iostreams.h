#ifndef NEWTON_RECIPROCAL_H_
#define NEWTON_RECIPROCAL_H_

#include <ap_fixed.h>
#include <hls_stream.h>

typedef ap_fixed<14,8> data_t;

void iostreams(hls::stream<data_t >  &in, hls::stream<data_t > &recipOut);

#endif
