#include <stdio.h>
#include "s21_decimal.h"
#include "utilits/s21_utility.h"

int main() {
    double x = 11111.123;

    s21_decimal decimal;
    s21_from_float_to_decimal(x, &decimal);

    print_binary_representation_std(decimal);

    s21_decimal_alt alt = s21_convert_std_to_alt(decimal);
    print_binary_representation_alt(alt);
    print_str_decimal_std(decimal);
}