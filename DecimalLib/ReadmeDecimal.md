Decimal struct consists of 4 int number where first 3 represent mantissa or integer part of number

    `bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

Last int should be read in bits.

    - `bits[3]` contains the scale factor and sign, and consists of following parts:

    - Bits 0 to 15, the lower word, are unused and must be zero.

    - Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
    
    - Bits 24 to 30 are unused and must be zero.

    - Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.


Example:
10 3 45 2147876864

    - 10 3 45 means: 10 * (2^32)^0 + 3 * (2^32)^1 + 45 * (2^32)^2 = 830103483329814724618
        - So maximum number will be (2^32)^3 = 2^96
    - 2147876864 in binary 10000000 00000110 00000000 00000000 (left is the highest bit)
        exponent would be 00000110 or 6
        sign = '-' since 31st bit is 1

result  -830103483329814724618e-6