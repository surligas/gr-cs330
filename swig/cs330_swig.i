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
#include "cs330/hamming_encoder.h"
#include "cs330/hamming_decoder.h"
#include "cs330/block_interleaver.h"
#include "cs330/block_deinterleaver.h"
#include "cs330/horizontal_sum_c.h"
#include "cs330/psk_modulator.h"
#include "cs330/psk_demodulator.h"
#include "cs330/msg_source.h"
%}

%include "cs330/complex_clamp.h"
GR_SWIG_BLOCK_MAGIC2(cs330, complex_clamp);
%include "cs330/convolutional_encoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330, convolutional_encoder);
%include "cs330/constellation_mapping.h"
GR_SWIG_BLOCK_MAGIC2(cs330, constellation_mapping);
%include "cs330/constellation_demodulation.h"
GR_SWIG_BLOCK_MAGIC2(cs330, constellation_demodulation);


%include "cs330/hamming_encoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330, hamming_encoder);
%include "cs330/hamming_decoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330, hamming_decoder);
%include "cs330/block_interleaver.h"
GR_SWIG_BLOCK_MAGIC2(cs330, block_interleaver);
%include "cs330/block_deinterleaver.h"
GR_SWIG_BLOCK_MAGIC2(cs330, block_deinterleaver);
%include "cs330/horizontal_sum_c.h"
GR_SWIG_BLOCK_MAGIC2(cs330, horizontal_sum_c);
%include "cs330/psk_modulator.h"
GR_SWIG_BLOCK_MAGIC2(cs330, psk_modulator);
%include "cs330/psk_demodulator.h"
GR_SWIG_BLOCK_MAGIC2(cs330, psk_demodulator);
%include "cs330/msg_source.h"
GR_SWIG_BLOCK_MAGIC2(cs330, msg_source);
