
/*
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

int32_t f2i(uint32_t);

union {
  uint32_t i;
  float f;
} u;

int main(void)
{
  for (int x = 0x7fffffff; x < 0xffffffff; x++)
  {
  uint32_t in;
  int32_t i;

  in = 0x8e3920ef;
  u.i = in;
  i = u.f;

  if (i != f2i(in))
    {
  printf("%08" PRIx32 " (%e) --> %08" PRIx32 " (my result is %08" PRIx32 ")\n",
    in, u.f, i, f2i(in));
    exit (-1);
    }
}
printf ("good job jhad!");

  

  return 0;
}
*/







//


















//THIS IS FOR TESTING i2F - PART 2 is 100 PERCENT FUNCTIONALLL!!!

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
int32_t f2i(uint32_t);
int32_t i2f(uint32_t);
union {
 uint32_t i;
 float f;
} u;

int main(void)
{
for ( int x = 0x80000000; x < 0xffffffff; x++)
{


 int32_t in= 0x894efab3 ;
float f =  in;
 uint32_t out = i2f(in);




  uint32_t output = *(uint32_t*)&f;


 if (out != output)
 {
   printf ("***BAD JOB JHAD YOU FAILED***\n");
   printf ("i2f(%08" PRIx32 ") --> %08" PRIx32 "(should be %08" PRIx32 ")\n", in, out, output );
   exit (-1);
 }

}
printf ("***** YOU DID IT JHAD! GOOD JOB!*****\n");

 return 0;
}


