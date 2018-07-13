
import numpy
import numpy.fft
import detectbirds

import pytest
import numpy.testing

def test_rfft_simple():
    ss = numpy.arange(0, 1024)
    ref = numpy.fft.fft(ss, n=1024).real
    out = detectbirds.rfft(ss)
    numpy.testing.assert_allclose(out, ref)

def test_rfft_not_power2_length():
    with pytest.raises(Exception) as e:
        detectbirds.rfft(numpy.array([1,3,4,5]))
