/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x && !y) return 1;
    if (!x && y) return 0;
    if (x && !y) return 0;
    return !((x>>31)^(y>>31));

}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res = 0;
    int shift = 0;
    shift=(v>0xFFFF)<<4;
    v=v>>shift;
    res|=shift;
    shift=(v>0xFF)<<3;
    v=v>>shift;
    res|=shift;
    shift=(v>0xF)<<2;
    v=v>>shift;
    res|=shift;
    shift=(v>0x3)<<1;
    v=v>>shift;
    res|=shift;
    shift=(v>0x1);
    v=v>>shift;
    res|=shift;
    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) { 
    int value = 0xFF;
    n = n << 3;      
    m = m << 3;       
    int x1 = (x >> n) & value;  
    int x2 = (x >> m) & value; 
    x = x & ~(value << n); 
    x = x & ~(value << m);           
    x = x | (x1 << m);          
    x = x | (x2 << n);          
    return x;

}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned res = 0;
    int i = 0;
    while (i - 32) {
        res = (res << 1) | ((v>>i)&1);
        i++;
    }
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x>>=n;
    int m=~(((1<<31)>>n)<<1);
    return x&m;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int res=0;
    int shift=0;
    shift=!(~x>>16)<<4;
    res+=shift;
    x<<=shift;
    shift=!(~x>>24)<<3;
    res+=shift;
    x<<=shift;
    shift=!(~x>>28)<<2;
    res+=shift;
    x<<=shift;
    shift=!(~x>>30)<<1;
    res+=shift;
    x<<=shift;
    shift=!(~x>>31);
    res+=shift;
    x<<=shift;
    shift=!(~x>>31);
    res+=shift;
    return res;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0, exp = 0, frac, abs_x, lost, half;
    if (!x) return 0;
    if (x < 0) { sign = 1; abs_x = -x; }
    else abs_x = x;
    unsigned temp = abs_x;
    while (temp >> 1) { temp >>= 1; exp++; }
    if (exp > 23) {
        unsigned shift = exp - 23;
        frac = (abs_x >> shift) & 0x7FFFFF;
        lost = abs_x & ((1u << shift) - 1);
        half = 1u << (shift - 1);
        if (lost + (frac & 1) > half) frac++;
        exp += frac >> 23;
        frac &= 0x7FFFFF;
    } else {
        frac = (abs_x << (23 - exp)) & 0x7FFFFF;
    }
    exp += 127;
    return (sign << 31) | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp,frac,sign;
    sign=uf&0x80000000;
    exp=(uf&0x7F800000)>>23;
    frac=(uf&0x7FFFFF);
    if(exp==255) return uf;

    if(exp==0){
        frac<<=1;
        if (frac & 0x800000) {    
            exp = 1;                   
            frac &= 0x7FFFFF;          
        }
        return sign | (exp << 23) | frac;
    }
    exp+=1;
    if (exp == 255) {                
        return sign | (255 << 23);  
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exp = (uf2 >> 20) & 0x7FF;
    int e_true= exp - 1023;
    if(!(exp-0x7FF)) return 0x80000000;
    if(!exp) return 0;
    if(e_true<0) return 0;
    unsigned frac_high=(uf2&0xFFFFF)|0x100000;
    unsigned frac_low=uf1;
    int shift=52-e_true;
    unsigned int result;

    if (shift >= 32) {
        result = frac_high >> (shift-32);
    } else if (shift > 0) {
        result = (frac_high << (32 - shift)) | (frac_low >> shift);
    } else {
        int ls = -shift;
        if (ls >= 32) {
            return 0x80000000;
        } else {
            if (ls >= 11) {
                if (frac_high >> (32 - ls)) return 0x80000000;
            }
            result = (frac_high << ls) | (frac_low >> (32 - ls));
        }
    }

    if (sign) {
        if (result > 0x80000000) return 0x80000000;
        return -result;
    } else {
        if (result >= 0x80000000) return 0x80000000;
        return result;
    }

}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127) return 0x7F800000;
    if(x<-149) return 0;
    if(x>=-149&&x<=-127) return 1u<<(x+149);
    return(x+127)<<23;
}
