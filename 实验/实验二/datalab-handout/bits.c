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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//德摩根律，用按位或和按位取反实现按位与
	return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	//在x中提取第n个字节的值，n为0-3
	return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	//实现逻辑右移，左侧补充0
	//1<<31变成100...00，符号位变1,右移n位前面补1
	//再左移一位，取反，实现高位n位为0,其余为1
	int mask = ~(((1 << 31) >> n) << 1);
	return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
	 
int bitCount(int x) {
	//求出x二进制中有多少个1
	//它首先将相邻的位对半加起来
	//然后再将相邻的两位组合成四位，以此类推
	//直到整个字中每相邻的 16 位被相加
	//最后，返回结果中的最后 6 位，即为原始数中包含的 1 的个数
	
  int tempmask1 = 0x55 | (0x55 << 8);
  //得到掩码 01010101...01010101
  int mask1 = tempmask1 | (tempmask1 << 16);
  int tempmask2 = 0x33 | (0x33 << 8);
  //得到掩码 00110011...00110011
  int mask2 = tempmask2 | (tempmask2 << 16);
  int tempmask3 = 0x0f | (0x0f << 8);
  //得到掩码  00001111...00001111
  int mask3 = tempmask3 | (tempmask3 << 16);
  //得到掩码  0000 0000 1111 1111 0000 0000 1111 1111
  int mask4 = 0xff | (0xff << 16);
  //得到掩码： 0000 0000 0000 0000 1111 1111 1111 1111
  int mask5 = 0xff | (0xff << 8);
	//前后加起来
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask3) + ((x >> 4) & mask3);
  x = (x & mask4) + ((x >> 8) & mask4);
  x = (x & mask5) + ((x >> 16) & mask5);

  return x & 0xff;
}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	//如果 x 为零则返回1，否则返回0
	//这里不用像上一题那样计算数量，只用用`|`来保证有1就行了
	int or16, or8, or4, or2, or1;
	or16 = x | x >> 16;
	or8 = or16 | or16 >> 8;
	or4 = or8 | or8 >> 4;
	or2 = or4 | or4 >> 2;
	or1 = or2 | or2 >> 1;
	return (or1 & 0x01) ^ 0x01;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	//返回补码表示的最小整数
	return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	//判断一个整数 x 是否可以用 n 位的补码表示
	//计算32-n
	int shift = 32 + (~n + 1);
	return !(((x << shift) >> shift) ^ x);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	//计算x/(2^n)，其中0 <= n <= 30
	//整数除法的性质：当被除数和除数都为正数时，结果向下取整；
	//当被除数和除数异号时，结果向零取整
	//对于正数 x，可以直接右移 n 位来实现除法
	//如果 x 为负，我们需要先加上2^n - 1然后再右移 n 位。
	int sign = x >> 31;               // 获取符号位
	int bias = (1 << n) + ~0;         // 计算 2^n - 1
	return (x + (sign & bias)) >> n;  // 根据符号位来调整结果
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	//计算-x
	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	//判断x是否大于0
	//x >> 31 是获取 x 的符号位
	//!x 是判断 x 是否为 0
	return !((x >> 31) | !x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	//判断 x 是否小于等于 y
	//考虑两种情况：
	//一种是 x 和 y 同号，此时只需比较它们的差是否小于等于 0；
	//另一种是 x 和 y 异号，此时只需判断 x 的符号位
	int signX = x >> 31 & 1;   // x 的符号位
  int signY = y >> 31 & 1;   // y 的符号位
  int signEqual = !(signX ^ signY);  // x和y的符号是否相同
  int diff = y + (~x + 1);   // y - x
	//如果符号相同，则只需判断即差值的符号位是否为1
	//如果符号不相同，则只需判断 x 的符号位是否为 1
  return (signEqual & (!(diff >> 31))) | ((!signEqual) & signX);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	//计算一个正数 x 的以 2 为底的对数
	//如果 x 的最高位在第 n 位，则返回的结果为 n
	//可以从高位开始逐渐检查每个位，找到最高位的位置
	//这可以通过先将 x 右移一半的位数
	//然后不断将右移的位数减半来实现
  int shift = 0;
  // 判断最高 16 位是否有值，并将结果左移 4 位
  shift = (!!(x >> 16)) << 4;    
  // 判断最高 8 位是否有值，并将结果左移 3 位
  shift = shift + ((!!(x >> (shift + 8))) << 3);
  // 判断最高 4 位是否有值，并将结果左移 2 位
  shift = shift + ((!!(x >> (shift + 4))) << 2);
  // 判断最高 2 位是否有值，并将结果左移 1 位
  shift = shift + ((!!(x >> (shift + 2))) << 1); 
  // 判断最高 1 位是否有值
  shift = shift + (!!(x >> (shift + 1)));           
  return shift;;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	//返回浮点数 f 的相反数的位级表示
	//如果 f 是 NaN（非数字），则返回 f 本身的位级表示
	unsigned exp = (uf >> 23) & 0xFF;  // 提取指数域
  unsigned frac = uf & 0x7FFFFF;     // 提取尾数域
  // 如果指数域全为 1 且尾数域不全为 0，则为 NaN，直接返回 uf
  if (exp == 0xFF && frac != 0) {
      return uf;
  }
  // 取反符号位得到相反数的位级表示
  return uf ^ 0x80000000;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    int s;
    int exp;
    int frac;
    int ans;
    int front_zero_cnt;
    int low_9;

    if (x == 0) return 0;
    if (x == 0x80000000) return 0xcf000000; // 负零的位级表示

    s = x & 0x80000000; // 提取符号位
    if (x < 0) x = -x; // 将输入的整数变成正数

    front_zero_cnt = 0;
    while (!(x & 0x080000000)) {
        front_zero_cnt++;
        x = x << 1;
    }

    exp = (127 + 32 - front_zero_cnt - 1) << 23; // 计算指数部分
    x = x << 1; // 去除尾数省略的那个 1
    frac = x >> 9 & 0x007fffff; // 提取尾数部分

    ans = s + exp + frac;

    low_9 = x & 0x000001ff; // 低 9 位
    if (low_9 > 0x00000100) ans++; // 进位
    if ((low_9 == 0x00000100) && (ans & 0x1)) ans++; // 检查是否需要额外的进位

    return ans;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	//计算浮点数 f 的两倍，并返回其位级表示
	unsigned sign = uf & 0x80000000;    // 符号位
  unsigned exp = uf & 0x7F800000;      // 指数域
  unsigned frac = uf & 0x7FFFFF;       // 尾数域
  // 如果 f 是正无穷大或负无穷大，直接返回 f 的位级表示
  if (exp == 0x7F800000) {
      return uf;
  }
  // 如果 f 是 NaN，直接返回 f 的位级表示
  if (exp == 0x7F800000 && frac != 0) {
      return uf;
  }
  //非规格化数 ，从尾数左移，把移出来的1放到阶码上
  if(exp == 0) {
		uf = uf << 1;
		uf = uf + sign;
	}
	//规格化数 // 阶码 + 1
	else uf += 0x00800000;
	
	return uf;
}
