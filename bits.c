/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x&~y)&~(~x&y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask=x>>31;
  return (~x+1)&mask;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
    int srcShift = src << 3;
    int dstShift = dst << 3;
    int byteVal = (x >> srcShift) & 0xFF;
    int shiftedByte = byteVal << dstShift;
    int mask = ~(0xFF << dstShift);
    return (x & mask) | shiftedByte;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
    int arith = x >> n;
    int mask = ~((1 << 31) >> n << 1);
    return arith & mask;
}


// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
    int mask = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
    int lowNibs = x & mask;
    int highNibs = x & ~mask;
    int highShifted = (highNibs >> 4) & mask;
    return (lowNibs << 4) | highShifted;
}
// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
    int notx = ~x;
    int lsb = notx & (~notx + 1);
    int rest = notx ^ lsb;
    return rest & (~rest + 1);
}
// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
    int s = n & 0x1f;
    int shift = 32 + ~s + 1;
    int mask = ~(~0 << shift);
    return ((x >> s) & mask) | (x << shift);
}
// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
    int p = 1 << n;
    int mask = p + ~0;
    int rem = x & mask;
    int half = p >> 1;
    int quo = x >> n;
    int diff = rem + ~half + 1;
    int gt = !(diff >> 31) & !!diff;
    int eq = !(rem ^ half);
    int carry = (gt | (eq & (quo & 1))) << n;
    return (x + carry) & ~mask;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int xor = x ^ y;
    int mid = (x & y) + (xor >> 1);
    int is_odd = xor & 1;
    int diff = xor >> 31;
    int x_neg = x >> 31;
    int sub = x + ~y + 1;
    int sub_neg = sub >> 31;
    int x_ge_y = (diff & ~x_neg) | (~diff & ~sub_neg);
    int sum_sign = is_odd & x_ge_y;
    return mid + sum_sign;
}
// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int diff = a ^ b;
    int sign_diff = diff >> 31;
    int sub_neg = (a + ~b + 1) >> 31;
    int a_ge_b = (sign_diff & (~a >> 31)) | (~sign_diff & ~sub_neg);

    int xor_ab = a ^ b;
    int min = a ^ (xor_ab & a_ge_b);
    int max = b ^ (xor_ab & a_ge_b);

    int diff1 = x ^ min;
    int sign_diff1 = diff1 >> 31;
    int sub_neg1 = (x + ~min + 1) >> 31;
    int x_ge_min = (sign_diff1 & (~x >> 31)) | (~sign_diff1 & ~sub_neg1);

    int diff2 = max ^ x;
    int sign_diff2 = diff2 >> 31;
    int sub_neg2 = (max + ~x + 1) >> 31;
    int max_ge_x = (sign_diff2 & (~max >> 31)) | (~sign_diff2 & ~sub_neg2);

    return (x_ge_min & max_ge_x) & 1;
}
// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int mul5 = (x << 2) + x;
    int overflow_4x = (x >> 29) ^ (x >> 31);
    int overflow_add = (mul5 >> 31) ^ (x >> 31);
    int overflow = overflow_4x | overflow_add;
    int mask = (overflow | (~overflow + 1)) >> 31;
    int sat_val = (x >> 31) ^ ~(1 << 31);
    return (mask & sat_val) | (~mask & mul5);
}
// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int sx = x >> 31;
    int sy = y >> 31;
    int sz = z >> 31;
    int s1 = x + y;
    int ss1 = s1 >> 31;
    int s2 = s1 + z;
    int ss2 = s2 >> 31;
    int c1 = ((~sx) & (~sy) & ss1 & 1) | (sx & sy & (~ss1));
    int c2 = ((~ss1) & (~sz) & ss2 & 1) | (ss1 & sz & (~ss2));
    return c1 + c2;
}
// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned s = uf & 0x80000000;
    unsigned e = (uf >> 23) & 0xFF;
    unsigned m = uf & 0x7FFFFF;
    unsigned T, M, mant;

    if (e == 0xFF) return uf;
    if (e == 0 && m == 0) return uf;

    if (e == 0) {
        T = m + (m << 1);      
        M = T >> 1;            
        if ((T & 1) && (M & 1)) M++; 
        if (M >= 0x800000) {   
            e = 1;
            m = M & 0x7FFFFF;
        } else {
            m = M;
        }
    } else {
        mant = m | 0x800000;
        T = mant + (mant << 1); 
        M = T >> 1;
        if ((T & 1) && (M & 1)) M++; 
        if (M >= 0x1000000) {
            e++;
            if ((M & 1) && ((M >> 1) & 1)) {
                M = (M >> 1) + 1;
            } else {
                M = M >> 1;
            }
        }
        if (e >= 0xFF) return s | 0x7F800000; 
        m = M & 0x7FFFFF;
    }
    return s | (e << 23) | m;
}
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned s = uf >> 31;
    int e = (uf >> 23) & 0xFF;
    int m = uf & 0x7FFFFF;

    if (e == 0xFF) return uf;
    if (e < 126) return s << 31;
    if (e == 126) {
        if (m == 0) return s << 31;
        return (s << 31) | (127 << 23);
    }

    int shift = e - 127;
    if (shift >= 23) return uf;

    int mant = m | 0x800000;
    int frac_bits = 23 - shift;

    int round_bit = (mant >> (frac_bits - 1)) & 1;
    int sticky_bits = mant & ((1 << (frac_bits - 1)) - 1);
    int int_lsb = (mant >> frac_bits) & 1;

    if (round_bit && (sticky_bits || int_lsb)) {
        mant += (1 << (frac_bits - 1));
    }
    mant &= ~((1 << frac_bits) - 1);

    if (mant >= 0x1000000) {
        mant >>= 1;
        e++;
    }

    return (s << 31) | (e << 23) | (mant & 0x7FFFFF);
}
// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    if (x == 0) return 0;
    unsigned sign = x & 0x80000000;
    unsigned abs_x = x;
    if (x < 0) abs_x = -x;

    int e = 31;
    while (!(abs_x >> e)) e--;

    int exp = e + 127;
    if (e <= 23) {
        abs_x <<= (23 - e);
    } else {
        int shift = e - 23;
        unsigned low = abs_x & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);
        abs_x >>= shift;
        if (low > half || (low == half && (abs_x & 1))) {
            abs_x++;
            if (abs_x == (1 << 24)) {
                abs_x >>= 1;
                exp++;
            }
        }
    }

    if (exp >= 255) return sign | 0x7F800000;
    return sign | (exp << 23) | (abs_x & 0x7FFFFF);
}
// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int mask1 = 0x55 | (0x55 << 8); mask1 = mask1 | (mask1 << 16);
    int mask2 = 0x33 | (0x33 << 8); mask2 = mask2 | (mask2 << 16);
    int mask3 = 0x0F | (0x0F << 8); mask3 = mask3 | (mask3 << 16);
    int mask4 = 0xFF | (0xFF << 16);
    int mask5 = 0xFF | (0xFF << 8);

    int count = (x & mask1) + ((x >> 1) & mask1);
    count = (count & mask2) + ((count >> 2) & mask2);
    count = (count & mask3) + ((count >> 4) & mask3);
    count = (count & mask4) + ((count >> 8) & mask4);
    count = (count & mask5) + (count >> 16);

    return count;
}
// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
    int m1 = 0x55 | (0x55 << 8); m1 = m1 | (m1 << 16);
    int m2 = 0x33 | (0x33 << 8); m2 = m2 | (m2 << 16);
    int m3 = 0x0F | (0x0F << 8); m3 = m3 | (m3 << 16);
    int m4 = 0xFF | (0xFF << 16);
    int m5 = 0xFF | (0xFF << 8);

    x = ((x >> 1) & m1) | ((x & m1) << 1);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 4) & m3) | ((x & m3) << 4);
    x = ((x >> 8) & m4) | ((x & m4) << 8);
    x = (x << 16) | ((x >> 16) & m5);
    return x;
}
