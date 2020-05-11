// p2.cl
//  Example Clite program to test lexer and parser

int main () {
   int c, k;
   float b;
   b = 2.34;
   c = 1;
   k = 0;
   b = -float(c);
   if ( c >= 52 && c == 60 * 2 || b <= 5.6 + 3.456 ) {
      c = int(c) * 6 / 9;
      while (k < 10)
          k = k + 1;
   }
   else
     c = k - 1;
}