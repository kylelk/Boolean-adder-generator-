#here are the two numbers that you are adding.
number1 = "98530"
number2 = "84309"

number1 = '{0:b}'.format(int(number1))
number2 = '{0:b}'.format(int(number2))
count = len(number1)

number1 = str(number1)
number2 = str(number2)


print """#include <stdio.h>

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

"""
print "void fourbitsadder(",
for n in range(0,count):
    print "IN "+"a"+str(n)+", ",
print "\n\t\t\t\t\t",
for n in range(0,count):
    print "IN "+"b"+str(n)+", ",
print "\n\t\t\t\t\t",
for n in range(0,count):
    print "OUT "+"o"+str(n)+", ",
print "\n\t\t\t\t\t",
print "OUT overflow)"

print """
{
\tPIN(zero); V(zero) = 0;
"""
print "\t",
for num in range(0,count):
    print "PIN(tc"+str(num)+");",

print "\n\tfulladder(/*INPUT*/a0, b0, zero, /*OUTPUT*/o0, tc0);"

for num in range(1,count-1):
    print "\t"+"fulladder(/*INPUT*/"+"a"+str(num)+", "+"b"+str(num)+", "+"tc"+str(num-1)+", "+"/*OUTPUT*/"+"o"+str(num)+", "+"tc"+str(num)+");"

print "\tfulladder(/*INPUT*/a"+str(count-1)+", "+"b"+str(count-1)+", "+"tc"+str(count-2)+", /*OUTPUT*/o"+str(count-1)+", "+ "overflow);"
print "}"

print """
int main()
{
"""
print "\t",
for num in range(0,count):
    print "PIN(a"+str(num)+");",
print "\n\t",
for num in range(0,count):
    print "PIN(b"+str(num)+");",
print "\n\t",
for num in range(0,count):
    print "PIN(s"+str(num)+");",
print "\n\t",

print "\n\tPIN(overflow);"

for num in range(0,count):
    print "\t"+"V(a"+str(count-num-1)+") = "+str(number1[num])+"; V(b"+str(count-num-1)+") = "+str(number2[num])+";"


print "\n\tfourbitsadder(",
for num in range(0,count):
    print "a"+str(num)+", ",

print "\n\t\t\t\t  ",
for num in range(0,count):
    print "b"+str(num)+", ",

print "\n\t\t\t\t  ",
for num in range(0,count):
    print "s"+str(num)+", ",

print "overflow);"

print "\tprintf(\""+count*"%d"+" + "+count*"%d"+" = "+(count+1)*"%d"+"\","

print "\t",
for num in range(0,count):
    print "V(a"+str((count-1)-num)+"), ",
print "\n\t",
for num in range(0,count):
    print "V(b"+str((count-1)-num)+"), ",
print "\n\t",
print "V(overflow),",

for num in range(0,count-1):
    print "V(s"+str((count-1)-num)+"), ",

print "V(s0)",
print ");\n"
#print "V(overflow));"

print "\tprintf(\"\\n\");"
print "\treturn 0;"
print "}"
