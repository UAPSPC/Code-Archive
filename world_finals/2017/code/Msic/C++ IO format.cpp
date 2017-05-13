#include <iostream> #include <iomanip> #include <cmath>
freopen("test.in","r",stdin);
freopen("test.out","w",stdout);
cout << fixed << setprecision(7) << M_PI << endl; // 3.1415927
cout << scientific << M_PI << endl; // 3.1415927e+000
int x=15, y=12094;
cout << setbase(10) << x << " " << y << endl; // 15 12094
cout << setbase(8)  << x << " " << y << endl; // 17 27476
cout << setbase(16) << x << " " << y << endl; // f 2f3e
x=5; y=9;
cout << setfill('0') << setw(2) << x << ":" << setw(2) << y <<
endl; // 05:09
printf ("%10d\n", 111); //       111
printf ("%010d\n", 111); //0000000111
printf ("%d %x %X %o\n", 200, 200, 200, 200); //200 c8 C8 310
printf ("%010.2f %e %E\n", 1213.1416, 3.1416, 3.1416);
//0001213.14 3.141600e+00 3.141600E+00
printf ("%*.*d\n",10, 5, 111); //     00111
printf ("%-*.*d\n",10, 5, 111); //00111
printf ("%+*.*d\n",10, 5, 111); //    +00111
char in[20]; int d;
scanf ("%s %*s %d",in,&d); //<- it's number 5
printf ("%s %d \n", in,d); //it's 5
