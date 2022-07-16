#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10000+1
#define BASE 3
#define EXP 2022

#define time_it(X) { \
    printf("============== %s begin\n", #X); \
    clock_t timer; double cpu_time_used; \
    timer = clock(); X(); timer = clock() - timer;\
    cpu_time_used = ((double) timer) / CLOCKS_PER_SEC; \
    printf("============== %s end, Time Spent: %f seconds\n\n\n",  #X, cpu_time_used); \
}
mpz_t a[NUM];
mpz_t target; // 3^2022

void init();
void compute_array();
void deallocate_array();
void q1();
void q2_1();
void q2_2();
void q2_3();

int main(int argc, char** argv) {
    init();
    time_it(compute_array);
    
    time_it(q1);
    time_it(q2_1);
    time_it(q2_2);
    time_it(q2_3);
 
    deallocate_array();
}

void q1(){
    for (int i = 3; i <= 6; i++) {
        gmp_printf ("a[%d] = %Zd\n", i, a[i]);
    }
}

void q2_1() {
    mpz_t sum, mod2;
    mpz_init(sum);
    mpz_init(mod2);

    mpz_add(sum, a[20], a[21]);
    mpz_mod_ui(mod2, sum, 2);
    
    gmp_printf ("a[20] + a[21] = %Zd\n", sum);
    gmp_printf ("( a[20] + a[21] ) \% 2 = %Zd\n", mod2);
}

void q2_2() {
    printf("Prove by induction that a[m] mod 3 != 0 for all m holds.\n");
    printf("So no m satisfies a[m] == 2022.\n");
}
void q2_3() {
    int found_flag = 0;
    mpz_t temp1, temp2;
    mpz_init(temp1);
    mpz_init(temp2);
    for (int i = 1; i < NUM; i ++) {
        for (int j = 1; j < NUM; j ++) {
            // compute a[i]^2 + 2a[j]^2
            mpz_mul(temp1, a[i], a[i]);
            mpz_mul(temp2, a[j], a[j]);
            mpz_mul_ui (temp2, temp2, 2);
            mpz_add(temp1, temp1, temp2);
            if (mpz_cmp(temp1, target) == 0) {
                printf("i, j = %d, %d\n", i, j);
                found_flag = 1;
                break;
            }
        }
        if (found_flag == 1) break;
    }
    if (found_flag==0) printf("No such i, j.\n");

}

void init() {
    for (int i = 0; i < NUM; i++) {
        mpz_init(a[i]);
        mpz_set_si(a[i],0);
    }
    mpz_set_si(a[1],1);
    mpz_set_si(a[2],2);
    mpz_init(target);
    mpz_ui_pow_ui(target, BASE, EXP);
}

void compute_array() {
    printf("Computing a[1] to a[%d]\n", NUM - 1);
    mpz_t temp1, temp2;
    mpz_init(temp1);
    mpz_init(temp2);
    for (int i = 3; i < NUM; i+=2) {
        // calculate a[i]
        mpz_mul_si(temp1, a[i-1], -4);
        mpz_add(a[i], temp1, a[i-2]);

        // calculate a[i+1]
        mpz_mul_si(temp1, a[i], 2);
        mpz_mul_si(temp2, a[i-1], 9);
        mpz_add(a[i+1], temp1, temp2);
    }
}

void deallocate_array() {
    for (int i = 0; i < NUM; i++) {
        mpz_clear(a[i]);
    }
}