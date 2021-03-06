==================================
Package documentation for pcm2mp3
==================================

A very simple module that converts PCM audio data in WAV, AIFF or AIFC files to compressed audio data in MP3 files, allowing choice of bitrate and the quality of the conversion process.  

The module is basically a lightweight wrapper around the LAME_ transcoder library, hiding much of the complexity (and the advanced functionality).  The purpose of the exercise is to be *quick* and *simple*.

Functions
---------

The module exposes one function **transcode** which takes PCM audio data and transcodes it to MP3 data at a specified sample rate.  The PCM audio data must:

* be encapsulated in standard WAV, AIFF or AIFC format
* have one or two channels (mono or stereo)
* be encoded as 16 or 32 bit linear integer PCM, or as 32 bit Floating Point

anything else results in an exception.  It is not necessary to tell **transcode** which format the file uses.

**transcode** may be invoked in two ways:   

``pcm2mp3`` . **transcode** (*infile*, *outfile*, *bitrate=64*, *quality=5*)

  :infile:     
    The name of the input file, *with* its file extension.  E.g. ``audio.wav`` or ``audio.aif``.  Files in 32 bit floating 
    point format are automatically normalised to the range [-1, +1] (also known as *IEEE* *Float*), so there is no
    need to worry about normalisation.

  :outfile:    
    The name to assign to the output MP3 file, *with* its file extension.  E.g. ``audio.mp3``.
    It has the same number of channels as *infile*.

  :bitrate:    
    The target bitrate (in kilobits per second) of the MP3 transcoded data.
    It must be one of the standard MP3 bitrates (expressed in kilobits per second).

    Common values include 128, 96, 64, 48, 24 and 8.  For more detail on supported rates, 
    check out documentation, e.g. the Wikipedia MP3_ page.   

    Optional: defaults to 64 (i.e. 64 kpbs).

  :quality:    
    A factor measuring the quality of the transcoding; ranges from 1 (best possible quality; very slow), 
    to 7 (acceptable quality; very fast).  See the LAME_ documentation for more details.

    Optional: defaults to 5 (high quality; quite fast).

  :Return value:
    The length of the output MP3 file in bytes (the size of *outfile*)


``pcm2mp3`` . **transcode** (*stream*, *bitrate=64*, *quality=5*)

  :stream:
    A bytes-like object (typically an instance of **bytes**) containing the raw bytes of the audio file to transcode. 
    

  :bitrate:    
    *As for file version*

  :quality:    
    *As for file version* 

  :Return value:
    A **bytes** object containing the transcoded MP3 file as raw bytes

Exceptions
  Throws a wav2mp3. **MP3Error** (see below) whenever LAME throws an exception, or else the data doesn't do what the module expects (see below).
    

Classes
-------

pcm2mp3. **MP3Error**

A child of the standard **Exception** class, reporting on errors occurring during transcoding.  Opaque.

Example
-------

::

  import pcm2mp3
  
  try:
      pcm2mp3.transcode("input.wav","output.mp3",bitrate=8)
  except pcm2mp3.MP3Error as e:
      print(str(e))


Acknowledgements
----------------

This software is a lightweight C++/Python wrapper around the LAME_ transcoder.  LAME is distributed according to the terms of the LGPL license.  All credit for transcoding, etc should go to the LAME team.

License
-------

This software is distributed under the terms of the BSD_ 3-clause license.   




.. _LAME: http://www.mp3dev.org
.. _MP3: https://en.wikipedia.org/wiki/MP3#Bit_rate
.. _BSD: https://opensource.org/licenses/BSD-3-Clause


