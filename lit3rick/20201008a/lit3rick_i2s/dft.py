#!/usr/bin/python3

import numpy as np


class DFT:
    '''
    Window DFT implementation.
    Based on SDFT (https://www.comm.utoronto.ca/~dimitris/ece431/slidingdft.pdf,
    https://www.dsprelated.com/showarticle/776.php),
    but windows are not overlapped.
    '''
    def __init__(self, N):
        self.N = N
        self.twiddles = [np.exp(2j * np.pi * i / N) for i in range(N)]
        self.flush_hist()

    def flush_hist(self):
        self.freq_hist = np.zeros(self.N, dtype=np.complex64)

    def step(self, s):
        for k in range(self.N):
            self.freq_hist[k] = (s + self.freq_hist[k]) * self.twiddles[k]

    def calc(self, seq):
        self.flush_hist()
        for n in range(seq.size):
            self.step(seq[n])
        return self.freq_hist


class DFTI:
    '''
    Window DFT integer implementation.
    Based on SDFT (https://www.comm.utoronto.ca/~dimitris/ece431/slidingdft.pdf,
    https://www.dsprelated.com/showarticle/776.php),
    but windows are not overlapped.
    '''
    complex_int32 = np.dtype([('re', np.int32), ('im', np.int32)])

    def __init__(self, N):
        self.N = N
        self.flush_hist()
        twiddles_float = [np.exp(2j * np.pi * i / N) for i in range(N)]
        self.twiddles = np.zeros(N, dtype=self.complex_int32)
        for i in range(N):
            self.twiddles[i] = self.twiddle_conv(twiddles_float[i])

    def flush_hist(self):
        self.freq_hist = np.zeros(self.N, dtype=self.complex_int32)

    def complex_mul(self, a, b):
        res = np.zeros(1, dtype=self.complex_int32)
        A = a['re'] * b['re']
        B = a['re'] * b['im']
        C = a['im'] * b['re']
        D = a['im'] * b['im']
        res['re'] = A - D
        res['im'] = B + C
        return res

    def complex_add(self, a, b):
        res = np.zeros(1, dtype=self.complex_int32)
        res['re'] = a['re'] + b['re']
        res['im'] = a['im'] + b['im']
        return res

    def complex_shiftr(self, a, shift_val):
        res = np.zeros(1, dtype=self.complex_int32)
        res['re'] = a['re'] >> shift_val
        res['im'] = a['im'] >> shift_val
        return res

    def twiddle_conv(self, complex_arg):
        def mul_sat16(a, b):
            if (a * b >= 32767):
                res = np.int32(32767)
            elif (a * b <= -32768):
                res = np.int32(-32768)
            else:
                res = np.int32(np.around(a * b))
            return res
        res = np.zeros(1, dtype=self.complex_int32)
        res['re'] = mul_sat16(complex_arg.real, 2**15)
        res['im'] = mul_sat16(complex_arg.imag, 2**15)
        return res

    def to_np_complex(self, a):
        return a.view(np.int32).astype(np.float32).view(np.complex64)

    def step(self, s):
        s_complex = np.zeros(1, dtype=self.complex_int32)
        s_complex['re'] = s
        #print("s_complex=", s_complex)

        for k in range(self.N):
            add_res = self.complex_add(s_complex, self.freq_hist[k])
            mul_res = self.complex_mul(add_res, self.twiddles[k])
            #if (k in [1, 2, 3]):
            #    print("k=", k)
            #    print("self.freq_hist[k] before", self.freq_hist[k])
            #    print("self.twiddles[k]", self.twiddles[k])
            #    print("add_res", add_res)
            #    print("mul_res", mul_res)
            self.freq_hist[k] = self.complex_shiftr(mul_res, 15)
            #if (k in [1, 2, 3]):
            #    print("!self.freq_hist[k] after", self.freq_hist[k])

        return self.freq_hist

    def calc(self, seq):
        self.flush_hist()
        for n in range(self.N):
            #print("***n=", n)
            #print(self.freq_hist[1:4])
            self.step(seq[n])
        return self.to_np_complex(self.freq_hist)


def nrsqrt(D, DATA_W=32):
    '''
    Non-Restoring Square Root Algorithm
    "An FPGA Implementation of a Fixed-Point Square Root Operation", Krerk Piromsopa, 2002
    https://www.researchgate.net/publication/2532597_An_FPGA_Implementation_of_a_Fixed-Point_Square_Root_Operation
    '''
    Q = np.uint32(0)
    R = np.int32(0)
    for i in reversed(range(DATA_W // 2)):
        if (R >= 0):
            R = (R << 2) | ((D >> (i + i)) & 3)
            R = R - ((Q << 2) | 1)
        else:
            R = (R << 2) | ((D >> (i + i)) & 3)
            R = R + ((Q << 2) | 3)
        if (R >= 0):
            Q = (Q << 1) | 1
        else:
            Q = (Q << 1) | 0
    return Q


def complex_abs(data):
    '''
    input: np.complex number
    output: np.uint16 result = sqrt(data.re^2 + data.im^2)
    '''
    mul_0 = np.uint32(np.int32(data.real) ** 2)
    mul_1 = np.uint32(np.int32(data.imag) ** 2)
    sum_val = mul_0 + mul_1
    result = np.uint16(nrsqrt(sum_val))
    return result


def preproc(x):
    '''
    input: np.array(M, N) - input points divided into chunks
           where M - Number of chunks,
                 N - Number of points in the chunk
           e.g. np.array(256,32)
    output: np.array(M, N/2) result, where every 2 points in the chunk were averaged
    '''
    temp_x = x.flatten()
    res = np.zeros(temp_x.size // 2)
    for i in range(0, temp_x.size, 2):
        res[i // 2] = (temp_x[i] + temp_x[i + 1]) // 2
    return res.reshape(x.shape[0], -1)


def postproc(ft_res):
    '''
    input: np.array(M, N) - FFT output frequency bins for every chunk
           where M - Number of chunks,
                 N - Number of frequency bins in the chunk
           e.g. np.array(256,32)
    output: np.array(M) result of (abs(F1)+abs(F2)+abs(F3))/(N/2) for every chunk,
            where Fi - complex frequency
    '''
    divider = ft_res.shape[1] // 2
    postproc_res = np.zeros(ft_res.shape[0], dtype=np.int32)
    for idx, res in enumerate(ft_res[:, 1:4]):
        postproc_res[idx] = ((np.uint32(complex_abs(res[0])) +
                              np.uint32(complex_abs(res[1])) +
                              np.uint32(complex_abs(res[2]))) // divider)
    return postproc_res


def dft_python_model(x):
    '''
    input: np.array(M, N) - input points divided into chunks
           where M - Number of chunks,
                 N - Number of points in the chunk
           e.g. np.array(256,32)
    output: np.array(M) result of (abs(F1)+abs(F2)+abs(F3))/(N/2) for every chunk
    '''
    preproc_x = preproc(x)
    dfti_res = np.zeros(preproc_x.shape, dtype=np.complex64)
    dfti = DFTI(preproc_x.shape[1])
    for i in range(preproc_x.shape[0]):
        dfti_res[i] = dfti.calc(preproc_x[i])
    postproc_res = postproc(dfti_res)
    return postproc_res
