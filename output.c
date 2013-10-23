#include <stdio.h>

typedef char pin_t;
#define IN const pin_t *
#define OUT pin_t *
#define PIN(X) pin_t _##X; pin_t *X = & _##X;
#define V(X) (*(X))

#define NOT(X) (~(X)&1)

#define XOR(X,Y) ((NOT(X)&(Y)) | ((X)&NOT(Y)))

void halfadder(IN a, IN b, OUT s, OUT c)
{
  V(s) = XOR(V(a), V(b));
  V(c) = V(a) & V(b);
}

void fulladder(IN a, IN b, IN ic, OUT s, OUT oc)
{
  PIN(ps); PIN(pc); PIN(tc);

  halfadder(/*INPUT*/a, b, /*OUTPUT*/ps, pc);
  halfadder(/*INPUT*/ps, ic, /*OUTPUT*/s, tc);
  V(oc) = V(tc) | V(pc);
}


void fourbitsadder( IN a0,  IN a1,  IN a2,  IN a3,  IN a4,  IN a5,  IN a6,  IN a7,  IN a8,  IN a9,  IN a10,  IN a11,  IN a12,  IN a13,  IN a14,  IN a15,  IN a16,  
					IN b0,  IN b1,  IN b2,  IN b3,  IN b4,  IN b5,  IN b6,  IN b7,  IN b8,  IN b9,  IN b10,  IN b11,  IN b12,  IN b13,  IN b14,  IN b15,  IN b16,  
					OUT o0,  OUT o1,  OUT o2,  OUT o3,  OUT o4,  OUT o5,  OUT o6,  OUT o7,  OUT o8,  OUT o9,  OUT o10,  OUT o11,  OUT o12,  OUT o13,  OUT o14,  OUT o15,  OUT o16,  
					OUT overflow)

{
	PIN(zero); V(zero) = 0;

	PIN(tc0); PIN(tc1); PIN(tc2); PIN(tc3); PIN(tc4); PIN(tc5); PIN(tc6); PIN(tc7); PIN(tc8); PIN(tc9); PIN(tc10); PIN(tc11); PIN(tc12); PIN(tc13); PIN(tc14); PIN(tc15); PIN(tc16); 
	fulladder(/*INPUT*/a0, b0, zero, /*OUTPUT*/o0, tc0);
	fulladder(/*INPUT*/a1, b1, tc0, /*OUTPUT*/o1, tc1);
	fulladder(/*INPUT*/a2, b2, tc1, /*OUTPUT*/o2, tc2);
	fulladder(/*INPUT*/a3, b3, tc2, /*OUTPUT*/o3, tc3);
	fulladder(/*INPUT*/a4, b4, tc3, /*OUTPUT*/o4, tc4);
	fulladder(/*INPUT*/a5, b5, tc4, /*OUTPUT*/o5, tc5);
	fulladder(/*INPUT*/a6, b6, tc5, /*OUTPUT*/o6, tc6);
	fulladder(/*INPUT*/a7, b7, tc6, /*OUTPUT*/o7, tc7);
	fulladder(/*INPUT*/a8, b8, tc7, /*OUTPUT*/o8, tc8);
	fulladder(/*INPUT*/a9, b9, tc8, /*OUTPUT*/o9, tc9);
	fulladder(/*INPUT*/a10, b10, tc9, /*OUTPUT*/o10, tc10);
	fulladder(/*INPUT*/a11, b11, tc10, /*OUTPUT*/o11, tc11);
	fulladder(/*INPUT*/a12, b12, tc11, /*OUTPUT*/o12, tc12);
	fulladder(/*INPUT*/a13, b13, tc12, /*OUTPUT*/o13, tc13);
	fulladder(/*INPUT*/a14, b14, tc13, /*OUTPUT*/o14, tc14);
	fulladder(/*INPUT*/a15, b15, tc14, /*OUTPUT*/o15, tc15);
	fulladder(/*INPUT*/a16, b16, tc15, /*OUTPUT*/o16, overflow);
}

int main()
{

	PIN(a0); PIN(a1); PIN(a2); PIN(a3); PIN(a4); PIN(a5); PIN(a6); PIN(a7); PIN(a8); PIN(a9); PIN(a10); PIN(a11); PIN(a12); PIN(a13); PIN(a14); PIN(a15); PIN(a16); 
	PIN(b0); PIN(b1); PIN(b2); PIN(b3); PIN(b4); PIN(b5); PIN(b6); PIN(b7); PIN(b8); PIN(b9); PIN(b10); PIN(b11); PIN(b12); PIN(b13); PIN(b14); PIN(b15); PIN(b16); 
	PIN(s0); PIN(s1); PIN(s2); PIN(s3); PIN(s4); PIN(s5); PIN(s6); PIN(s7); PIN(s8); PIN(s9); PIN(s10); PIN(s11); PIN(s12); PIN(s13); PIN(s14); PIN(s15); PIN(s16); 
	
	PIN(overflow);
	V(a16) = 1; V(b16) = 1;
	V(a15) = 1; V(b15) = 0;
	V(a14) = 0; V(b14) = 1;
	V(a13) = 0; V(b13) = 0;
	V(a12) = 0; V(b12) = 0;
	V(a11) = 0; V(b11) = 1;
	V(a10) = 0; V(b10) = 0;
	V(a9) = 0; V(b9) = 0;
	V(a8) = 0; V(b8) = 1;
	V(a7) = 1; V(b7) = 0;
	V(a6) = 1; V(b6) = 1;
	V(a5) = 1; V(b5) = 0;
	V(a4) = 0; V(b4) = 1;
	V(a3) = 0; V(b3) = 0;
	V(a2) = 0; V(b2) = 1;
	V(a1) = 1; V(b1) = 0;
	V(a0) = 0; V(b0) = 1;

	fourbitsadder( a0,  a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9,  a10,  a11,  a12,  a13,  a14,  a15,  a16,  
				   b0,  b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10,  b11,  b12,  b13,  b14,  b15,  b16,  
				   s0,  s1,  s2,  s3,  s4,  s5,  s6,  s7,  s8,  s9,  s10,  s11,  s12,  s13,  s14,  s15,  s16,  overflow);
	printf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d + %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d = %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
	V(a16),  V(a15),  V(a14),  V(a13),  V(a12),  V(a11),  V(a10),  V(a9),  V(a8),  V(a7),  V(a6),  V(a5),  V(a4),  V(a3),  V(a2),  V(a1),  V(a0),  
	V(b16),  V(b15),  V(b14),  V(b13),  V(b12),  V(b11),  V(b10),  V(b9),  V(b8),  V(b7),  V(b6),  V(b5),  V(b4),  V(b3),  V(b2),  V(b1),  V(b0),  
	V(overflow), V(s16),  V(s15),  V(s14),  V(s13),  V(s12),  V(s11),  V(s10),  V(s9),  V(s8),  V(s7),  V(s6),  V(s5),  V(s4),  V(s3),  V(s2),  V(s1),  V(s0) );

	printf("\n");
	return 0;
}
