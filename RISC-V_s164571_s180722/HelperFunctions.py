# Slicing a string of bits from a given instruction
import numpy as np

def bits_slice(value: np.uint32,
               least_significand: np.int8,
               most_significand: np.int8):
    if least_significand > most_significand:
        print("error: least_significand < most_significand")
    return (value & (2**(most_significand + 1) - 2**least_significand)) >> least_significand


# Sign extender function
def sign_extender(extend_me: np.uint32, length: np.int8):
    if bits_slice(extend_me, length-1, length-1) == 1:
        return np.int32 (extend_me | bits_slice(2**31-1, length-1, 31) << length)
    if bits_slice(extend_me, length-1, length-1) == 0:
        return np.int32 (extend_me)


# Create a number having the right sequence of 0 and 1
def bitmask(start, end):
    return bits_slice(np.uint32(2**end)-1, start, end)

