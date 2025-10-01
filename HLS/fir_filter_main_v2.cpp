#define taps 47
#include "ap_int.h"
//taps is the number of taps made by matlab. 
//ap_int.h is apparently and arbitrary integer type 

typedef int coeff_t;
typedef int data_t;
typedef int acc_t;
//these are all typedefs whats is a type define again? 

void fir(data_t *y, data_t x){
    coeff_t coefficients[taps] ={25,48,59,24,-84, -260,-453,-569,-514,
  -246,173,576,742,510,-114,-904,-1456,-1341,-295,1619,3984,6141,7425,7425,6141,3984, 1619,-295, -1341,-1456, -904,-114,510,742,576,173,-246,514,-569,-453,-260,-84,24,59,48,25   
    };
    //coeff_t coefficients[taps] is an array of the filter coefficients changed from floating point to 16 bit integers this will probably cause significant degradation of the filter performance. I would prefer if it were eight bit though. 
    static data_t shift_register[taps];

    //shift register is the basic component of the digital filter it stores all the z's 
    acc_t accumulate;
    //so a digital filter basically does three things. Shift Multiply Accumulate. So the shift register stores
    //the samples. then we multiply each sample by its prospective taps and then SHIFT. hence shift multiply accumulate.
    int i; 
    accumulate = 0;
    Shift_Accumulate_Loop:
    for(i=taps-1;i>0;i--){
        shift_register[i]=shift_register[i-1];
        accumulate += shift_register[i]*coefficients[i];
    }
    accumulate += x*coefficients[0];
    shift_register[0] = x;
    *y = accumulate;


}
