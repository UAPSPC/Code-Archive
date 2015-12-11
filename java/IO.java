/* Java Template: IO Reference
   =================================================================
   Description: This document is a reference for the use of the
                java for regular IO purposes.  It covers stdin and
                stdout as well as file IO.  It also shows how to use
                StringTokenizer for parsing.
   
   -----------------------------------------------------------------
   Author:      Patrick Earl
   Date:        Nov 14, 2002
   References:  Java API Documentation
   -----------------------------------------------------------------
   Reliability: 0
*/

import java.util.*;
import java.io.*;

class IO {
    public static void main(String[] args) {
        try {
            /*
            BufferedReader in=new BufferedReader(
                                new FileReader("prob1.dat"));
            PrintWriter out=new PrintWriter(
                              new BufferedWriter(
                                new FileWriter("prob1.out")));
            */

            /* For stdin/stdout IO, use: */
            PrintStream out = System.out;
            BufferedReader in = new BufferedReader(
                                  new InputStreamReader(System.in));
        
            String line;
            int num=0;

            StringTokenizer st;
        
            while(true) {
                /* Newlines are removed by readLine(). */
                line = in.readLine();
                if(line == null) break;
                num++;

                /* Print out line number. */
                out.println("Line #" + num);

                /* Split on whitespace */
                st = new StringTokenizer(line);
                while(st.hasMoreTokens()) {
                    out.print("Token: ");
                    out.println(st.nextToken());
                }

                /* To split on something else, use:
                     st = new StringTokenizer(line, delim);
                   Or use this to change in the middle of parsing:
                     line = st.nextToken(delim);
                */
            }

            /* You must flush for files! */
            out.flush();
        } catch(Exception e) {
            System.err.println(e.toString());
        }
    }
}
