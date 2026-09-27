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
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x&y))&(~((~x)&(~y)));
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
    if(x&&!y) return 0;
    if(!x&&y) return 0;
    return !(((x>>31)&1)^((y>>31)&1));
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
    int result;
    int shift;
    result=(v>0xFFFF)<<4;
    v=v>>result;
    shift=(v>0xFF)<<3;
    result=result|shift;
    v=v>>shift;
    shift=(v>0xF)<<2;
    result=result|shift;
    v=v>>shift;
    shift=(v>0x3)<<1;
    result=result|shift;
    v=v>>shift;
    result=result|(v>>1);
    return result;
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
    n=n<<3;
    m=m<<3;
    int N=(x>>n)&0xFF;
    int M=(x>>m)&0xFF;
    int blank=(~(0xFF<<n))&(~(0xFF<<m));
    int new=x&blank;
    int add=(N<<m)|(M<<n);
    int result=add|new;
    return result;
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
    int i=0;
    while(!(i>>4)){
        int j=31-i;
        int ri=(v>>i)&1;
        int le=(v>>j)&1;
        int blank=~((1<<j)|(1<<i));
        int wait=v&blank;
        int write=(ri<<j)|(le<<i);
        v=wait|write;
        i++;
    }
    return v;
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
    int mask = ~(((1<<31)>>n)<<1);
    return (x>>n)&mask;
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
    int n=~x;
    int r1=(!(n>>16))<<4;
    n=n<<r1;
    int r2=(!(n>>24))<<3;
    n=n<<r2;
    int r3=(!(n>>28))<<2;
    n=n<<r3;
    int r4=(!(n>>30))<<1;
    n=n<<r4;
    int r5=!(n>>31);
    n=n<<r5;
    int r6=!(n>>31);
    return r1+r2+r3+r4+r5+r6;
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
    if(x==0){
        return 0;
    }
    unsigned s=x&0x80000000;
    unsigned xx=x;
    if(s){
        xx=~x+1;
    }
    int i=0;
    while((xx>>i)>1){
        i++;
    }
    unsigned m;
    if(i<=23){
        m=xx<<(23-i);
    }
    else{
        int shift=i-23;
        unsigned aba=xx&((1<<shift)-1);
        m=xx>>shift;
        unsigned half=1<<(shift-1);
        if(aba>half){
            m=m+1;
        }        
        else{
            if(aba==half){
                if(m&1){
                    m=m+1;
                }
            }
        }
    }
    return s|(((i+127)<<23)+m-(1<<23));
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
    unsigned s=uf&0x80000000;
    unsigned e=(uf>>23)&0xFF;
    unsigned m=uf&0x7FFFFF;
    if(e==0xFF){
        return uf;
    }
    else{
        if(e==0){
            m=m<<1;
        }
        else{
            e=e+1;
            if(e==0xFF){
                m=0;
            }
        }
    }
    return s|((e<<23)|m);
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
    int e=(uf2>>20)&0x7FF;
    if(e<=0x7FF){
        if(e>=0x7FF){
            return 0x80000000;
        }
    }
    e=e-1023;
    if(e<0){
        return 0;
    }
    if(e>=31){
        return 0x80000000;
    }
    unsigned x=(uf2&0xFFFFF)|0x100000;
    if(e<=20){
        x=x>>(20-e);
    }
    else{
        x=(x<<(e-20))|(uf1>>(52-e));
    }
    if(uf2>>31){
        x=~x+1;
    }
    return x;
    return 2;
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
    if(x<-149){
        return 0;
    }
    if(x<-126){
        return 1<<(x+149);
    }
    if(x<=127){
        return(x+127)<<23;
    }
    
    return 0x7F800000;
}
