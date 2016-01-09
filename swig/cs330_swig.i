/* -*- c++ -*- */

#define CS330_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "cs330_swig_doc.i"

%{
#include "cs330/complex_clamp.h"
#include "cs330/convolutional_encoder.h"
#include "cs330/constellation_mapping.h"
#include "cs330/constellation_demodulation.h"
#include "cs330/ofdm_subcarrier_allocator.h"
#include "cs330/ofdm_demodulator.h"
%}

%include "cs330/complex_clamp.h"
GR_SWIG_BLOCK_MAGIC2(cs330, complex_clamp);
%include "cs330/convolutional_encoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330, convolutional_encoder);
%include "cs330/constellation_mapping.h"
GR_SWIG_BLOCK_MAGIC2(cs330, constellation_mapping);
%include "cs330/constellation_demodulation.h"
GR_SWIG_BLOCK_MAGIC2(cs330, constellation_demodulation);
%include "cs330/ofdm_subcarrier_allocator.h"
GR_SWIG_BLOCK_MAGIC2(cs330, ofdm_subcarrier_allocator);
%include "cs330/ofdm_demodulator.h"
GR_SWIG_BLOCK_MAGIC2(cs330, ofdm_demodulator);
