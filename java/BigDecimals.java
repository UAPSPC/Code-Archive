/* Java Template: BigDecimal Reference
   =================================================================
   Description: This document is a reference for the use of the
                BigDecimal class in Java.  It contains sample code
                that computes the reciprocal of a number with
                50 digits after the decimal point.
   
   -----------------------------------------------------------------
   Author:      Patrick Earl
   Date:        Nov 14, 2002
   References:  Java API Documentation
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
   
   Constants:
   ----------
   Common:

   BigDecimal.ROUND_HALF_UP - Round towards nearest neighbour.
                              If equidistant, round away from zero.
                              This is the "typical" rounding method.
   BigDecimal.ROUND_HALF_EVEN - Round towards nearest neighbour.
                                If equidistant, round to make the
                                last digit even.  This mode does the
                                same rounding as a C printf().  It
                                also most reduces calc errors.
   BigDecimal.ROUND_UNNECESSARY - The operation should have an exact
                                  result.  If it does not, an
                                  ArithmeticException is thrown.

   Less used:

   BigDecimal.ROUND_UP - Always round away from zero.
   BigDecimal.ROUND_DOWN - Always round towards zero.
   BigDecimal.ROUND_CEILING - Round towards positive infinity.
   BigDecimal.ROUND_FLOOR - Round towards negative infinity.
   BigDecimal.ROUND_HALF_DOWN - Round towards nearest neighbour.
                                If equidistant, round towards zero.

   Creating BigDecimals
   -------------
   1. From Strings
      a) BigDecimal(String val);

   2. From BigIntegers
      a) BigDecimal(BigInteger val);
      b) BigDecimal(BigInteger val, int scale);

   3. From Double
      a) BigDecimal(double val)
      NOTE:  BigDecimal(".1") is exact, where BigDecimal(.1) is not.

   4. From a long integer
      a) static BigDecimal BigDecimal.valueOf(long val)
      b) static BigDecimal BigDecimal.valueOf(long val, int scale)

   Math operations:
   ----------------
   A + B = C              -->  C = A.add(B);
   A - B = C              -->  C = A.subtract(B);
   A * B = C              -->  C = A.multiply(B);
   A / B = C              -->  C = A.divide(B, roundingMode);
                                   Where C.scale() == A.scale()
   A / B = C              -->  C = A.divide(B, scale, roundingMode);
                                   Where C.scale() == scale
   abs(A) = C             -->  C = A.abs();
   -(A) = C               -->  C = A.negate();
   
   max(A,B) = C           -->  C = A.max(B);
   min(A,B) = C           -->  C = A.min(B);

   Scale Manipulation Operations
   -----------------------------

   movePointLeft(int n)   -->  Moves decimal point right or left
                               depending on value of n.
   movePointRight(int n)  -->  Opposite of Left.

   int scale()            -->  Returns current scale.

   setScale(scale)        -->  Used to increase precision.
   setScale(scale, roundingMode)  -->  Round to scale digits after
                                       decimal point.

   Comparison Operations
   ---------------------
   A < B                  -->  A.compareTo(B) == -1;
   A == B                 -->  A.compareTo(B) ==  0 
   A > B                  -->  A.compareTo(B) ==  1;

   A == B && A.scale() == B.scale() --> A.equals(B);

   A < 0                  -->  A.signum() == -1;
   A == 0                 -->  A.signum() ==  0;
   A > 0                  -->  A.signum() ==  1;

   Conversion:
   -----------
   double                 -->  A.doubleValue();
   float                  -->  A.floatValue();
   int                    -->  A.intValue();
   long                   -->  A.longValue();
   String                 -->  A.toString();
   BigInteger             -->  A.toBigInteger();
   BigInteger             -->  A.unscaledValue();

   -----------------------------------------------------------------*/
   
/* Reads in lines of input until EOF is encountered.  For each line
   of input it will interpret it as a single number.  The reciprocal
   of that number will be computed and printed. */

import java.math.*;
import java.io.*;
import java.util.*;

class BigDecimals {
    public static void main(String[] args) {
        BufferedReader in = new BufferedReader(
				new InputStreamReader(System.in));
        BigDecimal one = new BigDecimal("1");
	BigDecimal a, b;
        String line;

	try {
	    while(true) {
                line = in.readLine();
                if(line == null) break;

		a = new BigDecimal(line);
                b = one.divide(a, 50, BigDecimal.ROUND_HALF_EVEN);

		System.out.println(b);
	    }
	} catch(Exception e) {
            System.err.println(e.toString());
	}
    }
}
