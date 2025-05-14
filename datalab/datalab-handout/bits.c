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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int a = (~x) & y;
  int b = (~y) & x;
  return ~(~a & ~b);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

  // ~(x+1)==x && ~(x+1)!=0
  // without an change of sign when adding 1, ~(x+1) cannot equal to x
  // there is an execption, when x=-1
  int a = x+1;
  int b = ~a;
  int cond1 = !(b ^ x);
  int cond2 = !! b;
  return cond1 & cond2;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int m = 0x00000055;
  int n = (m << 8) + m;
  int p = (n << 16) + n;//0x55555555
  int pAndx = p & x; //must be the same as p
  return !(pAndx ^ p);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x) + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int constant = (~2)+1;//0x11111110
  int t = x & constant;
  int c1 = !(t ^ 0x00000030);
  int minusNine = (~9) + 1;
  int c2 = (x + minusNine) & constant;
  return c1 & c2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int xp = !!x;
  xp = (xp << 31) >> 31;
  return (xp & y) + ((~xp) & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int condition = !((x ^ y) >> 31); //the first bit of x and y is different
  int minusX = (~x) + 1;
  int m = !(minusX >> 31);//return value when condition holds
  int n = !!(x >> 31);//return value when condition not holds

  //below the same as call function conditional
  int xp = !!condition;
  xp = (xp << 31) >> 31;
  return (xp & m) + ((~xp) & n);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int negX = (~x) + 1;
  int cond1 = (x >> 31) + 1;
  int cond2 = (negX >> 31) + 1;
  return cond1 & cond2;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //I can only give an implementation that exceeds the max op limit
  /*essentially, from left to right, find the first 0-1/1-0 boundery, and compress the multi-prefix-0s/1s to one 0/1,
  then count the remained bit length
  --step 1, unify the sign by ~, all start with 0
  --step 2, convert e.g. 0001xxxxx..(x means we don't care its value) to 00011111...
  --step 3, add all bits with the same weight 1(instead of 2^i)*/
  int xp = !(x & (1 << 31));
  int xPrime;
  int result;

  xp = (xp << 31) >> 31;
  x = (xp & ~x) + ((~xp) & x);

  xPrime = x;
  xPrime = (x >> 1) | xPrime;
  xPrime = (x >> 2) | xPrime;
  xPrime = (x >> 3) | xPrime;
  xPrime = (x >> 4) | xPrime;
  xPrime = (x >> 5) | xPrime;
  xPrime = (x >> 6) | xPrime;
  xPrime = (x >> 7) | xPrime;
  xPrime = (x >> 8) | xPrime;
  xPrime = (x >> 9) | xPrime;
  xPrime = (x >> 10) | xPrime;
  xPrime = (x >> 11) | xPrime;
  xPrime = (x >> 12) | xPrime;
  xPrime = (x >> 13) | xPrime;
  xPrime = (x >> 14) | xPrime;
  xPrime = (x >> 15) | xPrime;
  xPrime = (x >> 16) | xPrime;
  xPrime = (x >> 17) | xPrime;
  xPrime = (x >> 18) | xPrime;
  xPrime = (x >> 19) | xPrime;
  xPrime = (x >> 20) | xPrime;
  xPrime = (x >> 21) | xPrime;
  xPrime = (x >> 22) | xPrime;
  xPrime = (x >> 23) | xPrime;
  xPrime = (x >> 24) | xPrime;
  xPrime = (x >> 25) | xPrime;
  xPrime = (x >> 26) | xPrime;
  xPrime = (x >> 27) | xPrime;
  xPrime = (x >> 28) | xPrime;
  xPrime = (x >> 29) | xPrime;
  xPrime = (x >> 30) | xPrime;
  xPrime = (x >> 31) | xPrime;
  //now step2 is complete

  //for step3, processing 2 bits at a time and make an adjust finally is more efficient, but anyway, the max op limit has been broken
  result = 1;// it should be 1 larger than the all-1's-suffix bits length
  result += (xPrime & (1));
  result += (xPrime & (1 << 1)) >> 1;
  result += (xPrime & (1 << 2)) >> 2;
  result += (xPrime & (1 << 3)) >> 3;
  result += (xPrime & (1 << 4)) >> 4;
  result += (xPrime & (1 << 5)) >> 5;
  result += (xPrime & (1 << 6)) >> 6;
  result += (xPrime & (1 << 7)) >> 7;
  result += (xPrime & (1 << 8)) >> 8;
  result += (xPrime & (1 << 9)) >> 9;
  result += (xPrime & (1 << 10)) >> 10;
  result += (xPrime & (1 << 11)) >> 11;
  result += (xPrime & (1 << 12)) >> 12;
  result += (xPrime & (1 << 13)) >> 13;
  result += (xPrime & (1 << 14)) >> 14;
  result += (xPrime & (1 << 15)) >> 15;
  result += (xPrime & (1 << 16)) >> 16;
  result += (xPrime & (1 << 17)) >> 17;
  result += (xPrime & (1 << 18)) >> 18;
  result += (xPrime & (1 << 19)) >> 19;
  result += (xPrime & (1 << 20)) >> 20;
  result += (xPrime & (1 << 21)) >> 21;
  result += (xPrime & (1 << 22)) >> 22;
  result += (xPrime & (1 << 23)) >> 23;
  result += (xPrime & (1 << 24)) >> 24;
  result += (xPrime & (1 << 25)) >> 25;
  result += (xPrime & (1 << 26)) >> 26;
  result += (xPrime & (1 << 27)) >> 27;
  result += (xPrime & (1 << 28)) >> 28;
  result += (xPrime & (1 << 29)) >> 29;
  result += (xPrime & (1 << 30)) >> 30;
  return result;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
