# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    cs330_complex_clamp.xml
    cs330_convolutional_encoder.xml
    cs330_constellation_mapping.xml
    cs330_constellation_demodulation.xml
    cs330_ofdm_subcarrier_allocator.xml
    cs330_ofdm_demodulator.xml
    cs330_hamming_encoder.xml
    cs330_hamming_decoder.xml
    cs330_block_interleaver.xml
    cs330_block_deinterleaver.xml DESTINATION share/gnuradio/grc/blocks
)
