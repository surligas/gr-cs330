

# Examples

This folder contains several working examples to play with and experiment.
* `simple_example.grc`: Basic flowgraph visualizing two sine waves. You can
change the frequency of both of them and see the result
* `simple_example_iq.grc`: The same with the previous example, but the 
signals now are in I-Q complex form. Phase shifts are also possible.
* `fm_receiver.grc`: A COMPLETE radio tuner!!! You can tune in any radio
station and listen to the music. Several visualizing blocks help you to
understand what is going on. Probably you will not have access to a SDR hardware
device to capture radio signals. Don't worry! We did that for you. 
Download a signal capture from this [link](https://drive.google.com/open?id=0B2PEM30YcjHXYU5zaFZaQVNjeEk)
* `quantization.grc`: See how the quantization noise changes with respect to
the quantization resolution and frequency
* `basic_filtering.grc`: This example provides an example to start explore the parameters of various filters.
* `simple_audio_filtering.grc`: A very simple audible example to get familiar with the effects of a filter. You can play also with the transition width.
* `horizonta_sum.grc`: A simple example using the horizontal sub block that we created during a lecture.

# Captured Signal files
All captured signal files will have the following naming convention:
`whatever_name_XYSPS_T.dat` where:

1. X corresponds to a number
2. Y corresponds to a letter indicating the scale of the Samples Per Second (SPS)
  * (none)
  * K: Kilo
  * M: Mega
  * G: Giga
3. T corresponds to the GNU Radio data type that the capture was performed
  * float
  * complex
  * short
  * int
  * byte
