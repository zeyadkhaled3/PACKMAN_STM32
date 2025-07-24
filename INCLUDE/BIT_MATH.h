
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET(a,b) a=a|(1<<b)

#define CLR(a,b)  a=a&(~(1<<b))

#define TGL(a,b)  a=a^(1<<b)

#define GET(a,b)   (a>>b)&1

#endif
