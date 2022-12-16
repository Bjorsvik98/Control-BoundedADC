#include <stdint.h>
#include "include/coefficients.h"
// #define USE_MYSTDLIB 1

#ifdef USE_MYSTDLIB
   // #include "include/stdlib.h"
#else
   #include <stdio.h>
   #include <stdlib.h>
   // #include "include/stdlib.h"
   #include <string.h>
#endif

int main() {
   // printf("outArray\n");

   // Init fir filter variables
   int32_t outArray[S_Height] = {0};

   // printf("%p\n", (void *)&outArray);
   // printf("Value = %d\n", *((int32_t*)0x7ffd33e1c4b0));
   //initialize outarray to 0 with length samples
   // printf("outArray2\n");

   // for (int i = 0; i < samples; i++) {
   //    outArray[i] = 0;
   // }

   // Fir filter algorithm
   // for (int k = 0; k < (samples/DSR - K1); k++ ) {
   for (int k = 0; k < (S_Height-K); k++ ) {
      for (int i = 0; i < K; i++) { 
         for (int j = 0; j < H_Width; j++) {
            if (S[(k*DSR)+i][j] == 1) {
               outArray[k] += H[i][j];
            } else {
               outArray[k] -= H[i][j];
            }
            // printf("outarray[%d] = %d k = %d \n", i, outArray[k], k);
         }
      }
   }

    
   #ifdef USE_MYSTDLIB
      return outArray[0];
   #else
      FILE *fp;
      fp=fopen("result.txt","w+");
      for(int i=0;i<S_Height;i++)
      {
         // printf("out[%d] = %d \n", i, outArray[i]);
         fprintf(fp,"%d\n", outArray[i]);
      }
      fclose(fp); 
      return 0;
   #endif
   
   
}



