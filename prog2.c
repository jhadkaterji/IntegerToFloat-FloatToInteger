//Jhad Katerji
//CS520 Lab 3
//Due 9/15/18

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

////////////NECESSARY VARIABLES////////////
int in2;
int sign;
int storedExp;
int significand;
int actualExp;
int finalNum;
int origCopy;
int stickyBits;
int guardBits;
int usefulBits;
int rightMostStoreBit;
int normalizedNumber;
int shifter;
int normalizedNumber2;
int shiftDirection;
/////////////TESTING AND PRINTING VARIABLES////////////
int origCopy2;
int origCopy3;
int counter;
int usefulBits2;
int testV;
int top24;
int testV2;
int stickyBitInt;
int testV3;
unsigned int testV4;

// f2i
//   Parameter: 32-bit value that should be interpreted as an IEEE
//     single-precision floating-point value.
//   Return value: 32-bit two's complement integer value produced by
//     converting the parameter to integer.
//   Note: This routine should duplicate what the Intel 64 hardware
//     does when converting floats to ints. Be sure to consider NaNs,
//     denormalized numbers, infinities, overflow, etc.
int32_t f2i(uint32_t in)
{
shifter = 0;
shiftDirection = 0;
    ////////////FIND THE SIGNIFICAND////////////
    significand = in & 0x7FFFFF;
    
    
    ////////////FIND THE STORED EXPONENT////////////
    in2 = (in>>23);
    storedExp = in2 & 0xFF;
    
    
    ////////////FIND THE SIGN//////////// 
    in2 = (in2>>8);
    sign = in2 & 0x1;
    
    ////////////FIND THE ACTUAL EXPONENT////////////
    actualExp = storedExp - 127;
    //printf ("actual exponent: %d\n", actualExp);
    
    
    ////////////CASE1////////////
    if (actualExp < 0)
    {
        return 0;
    }
    else if ((in==0x00000000) | (in == 0x80000000))
    {
        return 0; 
    }
    ////////////CASE2////////////
    else if ((storedExp == 0)&&(significand != 0))
    {
        return 0;       
    } 
    ////////////CASE3////////////
    else if ((storedExp == 0xff) && (significand == 0))
    {
        return 0x80000000;     
    }
    ////////////CASE4////////////
    else if ((storedExp == 0xff) && (significand != 0))
    {
     return 0x80000000;  
    }
    ////////////CASE5////////////
    else if (storedExp < 127)
    {
        return 0;  
    }
    ////////////OVERFLOW CASE////////////
    else if (actualExp >=31)
    {
        return 0x80000000;
    }
  
    ////////////THIS IS FOR NON-SPECIAL CASES////////////
   else
   {
       sign = 0;
       ////////////CHECKING FOR NEGATIVE, IF IT'S NEGATIVE, IGNORE IT///////////
       if ((in & 0x80000000) != 0)
       {
           sign = 1;
           in = (in - 0x80000000);
       }
       ////////////GETTING THE SHIFT DIRECTION////////////
       shifter = (actualExp - 23);
       if (shifter < 0)
            {
                shiftDirection = 1;
                shifter = -shifter;

            }
        else
            {
                shiftDirection = 0;
            }

    //ADD THE ONE THAT NEEDS TO BE IN FRONT ALL THE TIME. 
       significand = significand + 0x800000;

    //SHIFT BASED OFF OF DIRECTION
    if (shiftDirection == 0)
    {
        significand = significand << (shifter);
    }
    if (shiftDirection == 1)
    {
         significand = significand >> (shifter);
    }

////////////NEGATING THE ANSWER IF IT WAS NEGATIVE TO START////////////
       if (sign == 1)
        {
            significand = -significand;
        }
////////////FINALLY RETURNING THE VALUE////////////
       return significand; 
   }
}








//--------------------//-----------------//-------------------//-----------------




// i2f
//   Parameter: 32-bit two's complement integer value.
//   Return value: 32-bit value that should be interpreted as an IEEE
//     single-precision floating-point value produced converting the
//     parameter to floating point.
//   Note: This routine should duplicate what the Intel 64 hardware
//     does when converting ints to floats.
uint32_t i2f(int32_t in)
{ 
    sign = 0;
    stickyBits = 0;
    counter = 0;
////////////CHECK FOR THE 0 CASE////////////
    if (in == 0)
    {
        return 0;
    }
    if (in == 0x80000000)
    {
        return 3472883712;
    }
    
////////////CHECK IF NEGATIVE, IF IT IS, NEGATE IT////////////
sign = (in & 0x80000000);
    if (sign != 0)

    {
        in = (-in);
        sign = 1;
    }
    //printf ("SIGN BIT: %d\n", sign);
    //printf ("Negated in: %d\n", in);
    
////////////MAKE SOME COPIES OF THE NUMBER TO MANIPULATE///////////
    origCopy = in;
    origCopy2 = in;
    testV = in;
          
////////////FIND THE ACTUAL EXPONENT////////////
actualExp = 0;
    while (in > 0)
    {
        in = in>>1;
        actualExp ++;
    }
    actualExp = (actualExp - 1);
    //printf ("ACTUAL EXPONENT: %d\n",actualExp);
    shifter = actualExp-23;
    if (actualExp<=23)
    {
        shifter = 0;
    }

//////////FIND THE STORED EXPONENT///////////
    storedExp = (actualExp  + 127);
    //printf ("STORED EXPONENT: %d\n", storedExp);
    finalNum = storedExp << 23;
    
////////////FIND THE STICKY BITS, GUARD BITS, AND 23 USEFUL BITS////////////
    origCopy = origCopy | (1<<actualExp);
    normalizedNumber = origCopy;
    normalizedNumber2 = origCopy;
    //printf ("NORMALIZED NUMBER: %d\n", origCopy);
    
    //USEFUL 23 BITS
    usefulBits = (normalizedNumber >> (shifter));
    top24 = usefulBits ; 
    //printf("24 USEFUL BITS: %d\n", top24);
    usefulBits = usefulBits & 0x7FFFFF;
    if (actualExp<=23)
    {
        usefulBits = (usefulBits << (23-actualExp));
        usefulBits = usefulBits - 0x800000;
    }
       if(actualExp == 23)
    {
        usefulBits = normalizedNumber - 0x800000;
    }
        //printf ("23 USEFUL BITS: %d\n", usefulBits);
    
    //FINDING THE GUARD BITS
    testV2 = ((normalizedNumber2) >> (shifter-2));
    
    if (shifter < 2)
        {
            testV2 = ((normalizedNumber2) >> (shifter-1));
        }
        
    //printf ("NUMBER WITH JUST GUARD BITS: %d\n", testV2);
    guardBits = testV2 & 0x3;
        if (actualExp<=23)
    {
        guardBits = 0;
    }
      if (shifter < 2)
        {
            if ((testV2 &1) == 1)
            {
                guardBits = 2;
            }
                if ((testV2 & 1) == 0)
                {
                    guardBits = 0;
                }
        }
    //printf ("GUARD BITS: %d\n", guardBits);
    
    //FINDING THE STICKY BITS
    while (normalizedNumber2 != testV2)
    {
        counter++;
        stickyBitInt = normalizedNumber2 & 0x1;
        if (stickyBitInt != 0)
        {
            stickyBits = 1;
        }  
        normalizedNumber2 = normalizedNumber2 >> 1;
    }
    //printf ("STICKY BITS: %d\n", stickyBits) ; 
    //printf ("SHIFTER: %d\n", shifter);
    //printf ("COUNTER WHICH SHOULD BE SHIFTER -2: %d\n", counter);
    
////////////FIND A FINAL ANSWER BY PUTTING ALL THE PIECES TOGETHER////////////
    finalNum = storedExp << 23;
    finalNum = finalNum + usefulBits;
    
////////////ROUND MY NUMBERS USING STICKY AND GUARD BITS////////////
    rightMostStoreBit = usefulBits & 1;
    //printf ("RIGHTMOST BIT: %d\n", rightMostStoreBit);

//FOR WHEN GUARD BITS ARE 10
    if (guardBits == 2)
    {
        if (stickyBits == 0 )
        {
            if (rightMostStoreBit == 1 )
            {
                finalNum = finalNum+1;
            }
            else
            {
                finalNum = finalNum;
            }
        }
        if (stickyBits != 0)
        {
            finalNum = finalNum+1;
        }
    }

//FOR WHEN GUARD BITS ARE 11
    if (guardBits == 3)
    {
        finalNum = finalNum+1;
    }
    
////////////IF IT WAS NEGATIVE, SET THE SIGN BIT TO 1////////////
    if (sign == 1)
    {
        finalNum = finalNum + 0x80000000;
    }    
  return finalNum; // just a stub for now; always return all zero bits
}
