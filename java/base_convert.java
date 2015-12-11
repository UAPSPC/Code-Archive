/* Number Theory: Converting between bases (arbitrary precision)
   =================================================================
   Description: Given a starting base b1, and a target base b2,
                and a string representive a nonnegative number N
		in base b1, returns the base b2 representation of
		N as a string.

		The digit sequence i.e. "0123456789ABCDEF" is
		specificed as a string and passed in as an argument
		as well
   
   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 26, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 
   Notes:       - the string returned will not have any leading
                  zeroes.
*/

import java.math.*;
import java.io.*;
import java.util.*;

class base_convert{
  // invalid is the string that is returned if the N is not valid
  static String invalid = new String("Number is not valid");
    
  private static String convert_base(int base1, int base2,
				     String n, String key){
    int i, x;
    String n2 = "", n3 = "";
    BigInteger 
	a = BigInteger.ZERO,
	b1 = BigInteger.valueOf(base1),
	b2 = BigInteger.valueOf(base2);
	
    for(i = 0; i < n.length(); i++){
	a = a.multiply(b1);
	x = key.indexOf(n.charAt(i));
	if(x == -1 || x >= base1) return invalid;
	a = a.add(BigInteger.valueOf(x));
    }
    while(a.signum() == 1){
	BigInteger r[] = a.divideAndRemainder(b2);
	n2 += key.charAt(r[1].intValue());
	a = r[0];
    }
    for(i = n2.length()-1; i >= 0; i--) n3 += n2.charAt(i);
    if(n3.length() == 0) n3 += '0';
    return n3;
  }
    
  public static void main(String[] args){
try{
    String line, n;
    int tnum, base1, base2;
    StringTokenizer st;
	
    // key is the base system that you may change as needed  
    String key = new 
	String("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    // Standard IO
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintStream out = System.out;
    
    // File IO
    // BufferedReader in = new BufferedReader(new FileReader("prob1.dat"));
    // PrintWriter   out = new BufferedWriter(new FileWriter("prob1.out"));

    line = in.readLine();                 // Get number of test cases 
    st = new StringTokenizer(line);
    tnum = Integer.parseInt(st.nextToken());
    
    for(int t = 0; t < tnum; t++){
	line = in.readLine();
	st = new StringTokenizer(line);
	base1 = Integer.parseInt(st.nextToken());
	base2 = Integer.parseInt(st.nextToken());
	n = st.nextToken();
	String result = convert_base(base1, base2, n, key2);
	out.println(result);
    }
} catch(Exception e){
    System.err.println(e.toString());
}}}
