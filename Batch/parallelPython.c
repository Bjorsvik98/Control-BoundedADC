#include <stdint.h>

#include "include/filter.h"
#include "include/coefficients.h"
#ifdef USE_MYSTDLIB
   // #include "include/stdlib.h"
#else
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
#endif



#define OFFSET 200

int main(int CORE) {
 
    
    int32_t output[K1] = {0};
    int32_t real_fM[K1+2][N] = {0};
    int32_t imag_fM[K1+2][N] = {0};
    int32_t real_bM[K1+2][N] = {0};
    int32_t imag_bM[K1+2][N] = {0};
   


    int k3 = 0;
    // if (CORE == 1){
    for (int n = 0; n < N; n++){  // To do in parallel
    // int n = CORE-1;
        for (int k2 = 1; k2 <= K1; k2++){
            int32_t tempRealFBS = 0;
            int32_t tempImagFBS = 0; 

            for (int m = 0; m < forward_b_Height; m++){
                if (S[k2-1][m] == 1){
                    tempRealFBS += real_forward_b[n][m];
                    tempImagFBS += imag_forward_b[n][m];
                } else if (S[k2-1][m] == 0){
                    tempRealFBS -= real_forward_b[n][m];
                    tempImagFBS -= imag_forward_b[n][m];
                }      
            }
            real_fM[((k2))][n] = (multiply(real_forward_a[n], real_fM[(k2-1)][n]) - multiply(imag_forward_a[n], imag_fM[(k2-1)][n])) + tempRealFBS;
            imag_fM[((k2))][n] = (multiply(real_forward_a[n], imag_fM[(k2-1)][n]) + multiply(real_fM[(k2-1)][n], imag_forward_a[n])) + tempImagFBS;

            k3 = K1 - k2 + 1; // should maby be -1
            // printf("k3: %d, k2: %d\n", k3, k2);
            int32_t tempRealBBS = 0;
            int32_t tempImagBBS = 0;
            // tempRealBBS = 0;
            // tempImagBBS = 0;
            for (int m = 0; m < backward_b_Width; m++){
                if (S[k3][m] == 1){
                    tempRealBBS += real_backward_b[n][m];
                    tempImagBBS += imag_backward_b[n][m];
                } else if (S[k3][m] == 0){
                    tempRealBBS -= real_backward_b[n][m];
                    tempImagBBS -= imag_backward_b[n][m];
                }      
            }
            real_bM[(k3)][n] = (multiply(real_backward_a[n], real_bM[((k3 + 1))][n]) - multiply(imag_backward_a[n], imag_bM[((k3 + 1))][n])) + tempRealBBS;
            imag_bM[(k3)][n] = (multiply(real_backward_a[n], imag_bM[((k3 + 1))][n]) + multiply(real_bM[((k3 + 1))][n], imag_backward_a[n])) + tempImagBBS;
            // printf("real_backward_a[%d] = %d real_bM[((%d))][%d] = %d ", n, real_backward_a[n], k3, n, real_bM[((k3 + 1))][n]); 
            // printf("real_bM[(%d)][%d] = %d \n", k3, n, real_bM[(k3)][n]);
            // printf("k2 = %d, k3 = %d\n", k2, k3);
        }    
    // }
    }


    for (int k4 = 0; k4 < K1; k4 = k4 + 1){ // To do in parallel
    // for (int k4 = CORE-1; k4 < K1; k4 = k4 + N + DSR){ // To do in parallel
        int32_t tempReal = 0;
        for (int n = 0; n < N; n++){
            int32_t tempRealFWFM = 0;
            tempRealFWFM = (multiply(real_forward_w[0][n], real_fM[(k4)][n]) - multiply(imag_forward_w[0][n], imag_fM[(k4)][n]));

            int32_t tempRealBWFM = 0;
            tempRealBWFM = (multiply(real_backward_w[0][n], real_bM[(k4)][n]) - multiply(imag_backward_w[0][n], imag_bM[(k4)][n]));
   
            tempReal += tempRealFWFM;
            tempReal += tempRealBWFM;
        }
        // output[k4/DSR] = (tempReal);
        output[k4] = (tempReal);
    }


    // printf("real_fM = \n");
    // for (int i = 0; i < K1+1; i++){
    //     for (int j = 0; j < N; j++){
    //         printf("%d \n", real_fM[i][j]);
    //     }
    // }
    // printf("imag_fM = \n");
    // for (int i = 0; i < K1+1; i++){
    //     for (int j = 0; j < N; j++){
    //         printf("%d \n", imag_fM[i][j]);
    //     }
    // }
    // printf("real_bM = \n");
    // for (int i = 0; i < K1+1; i++){
    //     for (int j = 0; j < N; j++){
    //         printf("%d \n", real_bM[i][j]);
    //     }
    // }
    // printf("imag_bM = \n");
    // for (int i = 0; i < K1+1; i++){
    //     for (int j = 0; j < N; j++){
    //         printf("%d \n", imag_bM[i][j]);
    //     }
    // }


    // printf("output = \n");
    // for (int i = 0; i < K1; i++){
    //     printf("%d \n", output[i]);
    // }
    #ifdef USE_MYSTDLIB
        return output[0];
    #else
        FILE *fp;
        fp=fopen("result.txt","w+");
        for(int i=0;i<K1;i++)
        {
            // printf("%d\n",output[i]);
            fprintf(fp,"%d\n", output[i]);
        }
        fclose(fp); 
        return 0;
    #endif
}

// int main() {
//     parallel(1);
//     // __asm__ ("lui sp,0xe");
//     parallel(2); 
//     // __asm__ ("lui sp,0xd");
//     parallel(3);

//     return 0;
// }
