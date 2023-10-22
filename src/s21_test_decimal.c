#include <stdio.h>
#include "s21_decimal.h"
#include "utilits/s21_utility.h"

int pi(long iterations);
int test();

int main() {
    pi(10000000);

    return 0;
}

int blobick() {
    s21_decimal f1, f2;
    double lf1 = 12.678912, lf2 = 0.000432;
    init_decimal(&f1), init_decimal(&f2);

    s21_from_float_to_decimal(lf1, &f1);
    s21_from_float_to_decimal(lf2, &f2);

    s21_mul(f1, f2, &f1);
    s21_mul(f1, f2, &f1);
    s21_mul(f1, f2, &f1);

    print_str_decimal_std(f1);
    printf("%.30lf\n", lf1 * lf2 * lf2 * lf2);

    return 0;
}

int pi(long iterations) {
    s21_decimal one, two, sum, number;
    s21_from_int_to_decimal(1, &number);
    s21_from_int_to_decimal(1, &one);
    s21_from_int_to_decimal(2, &two);
    s21_from_int_to_decimal(0, &sum);

    s21_decimal tmp1;
    for (long i = 0; i < iterations; ++i) {
        s21_div(one, number, &tmp1);
        s21_add(sum, tmp1, &sum);

        s21_add(number, two, &number);
        s21_negate(number, &number);

        s21_negate(two, &two);
    }

    // printf("%d - %d\n\n", get_sign_bit(sum), get_exponent_rang(sum));
    s21_mul(sum, two, &sum);
    s21_mul(sum, two, &sum);

    print_str_decimal_std(sum);
    return 0;
}

int test() {
    double x = 11111.123;

    s21_decimal decimal;
    s21_from_float_to_decimal(x, &decimal);

    print_binary_representation_std(decimal);

    s21_decimal_alt alt = s21_convert_std_to_alt(decimal);
    print_binary_representation_alt(alt);
    print_str_decimal_std(decimal);

    return 0;
}