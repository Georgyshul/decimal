#ifndef SRC_UTILITS_S21_UTILITY_H_
#define SRC_UTILITS_S21_UTILITY_H_
#include <stdio.h>

#include "../s21_decimal.h"

int s21_sub_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result);
int s21_add_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result);
int s21_mul_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result);
int s21_div_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result);
int s21_mod_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result);

bool s21_get_bit_int(unsigned int num, int pos);
int8_t get_sign_bit(s21_decimal value);
int8_t get_bit(s21_decimal value, int8_t position);
int find_main_bit(s21_decimal value);
int8_t get_position(int8_t piece, int8_t bit);
int is_zero(s21_decimal value);
void set_sign_bit(s21_decimal *value, uint8_t sign_bit);
void s21_right_shift(s21_decimal_alt *alt);
int8_t get_exponent_rang(s21_decimal value);
void delete_bit(s21_decimal *value, int8_t position);
void s21_left_shift(s21_decimal_alt *alt);
void s21_copy_decimal(s21_decimal src, s21_decimal *dst);
void set_exponent_rang(s21_decimal *value, uint8_t exponent_rang);
void int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *difference);
int multiply_by_two(s21_decimal *value, int times);
int8_t divide_by_two(s21_decimal *value);
void copy_only_number(s21_decimal src, s21_decimal *dst);
int add_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void sub_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
void put_bit(s21_decimal *value, int8_t position);
void set_bit(s21_decimal *value, int8_t position, int8_t bit);
bool s21_get_sign_std(s21_decimal dec);
int s21_get_exp_std(s21_decimal dec);
int increase_order_of_magnitude(s21_decimal *value, int times, int *possible);
int8_t decrease_order_of_magnitude(s21_decimal *value);
void s21_null_decimal_alt(s21_decimal_alt *alt);
s21_decimal_alt s21_convert_std_to_alt(s21_decimal std);
s21_decimal s21_convert_alt_to_std(s21_decimal_alt alt);
void s21_rescale(s21_decimal *value_1, s21_decimal *value_2);
void s21_rescale_alt(s21_decimal_alt *alt_value_1,
                     s21_decimal_alt *alt_value_2);
void s21_rescale_alt_to_smaller(s21_decimal_alt *alt_value_1,
                                s21_decimal_alt *alt_value_2);
void init_decimal(s21_decimal *decimal);
int div_by_ten(s21_decimal_alt *alt);
bool compare_bits(s21_decimal_alt alt1, s21_decimal_alt alt2);
bool is_null(s21_decimal_alt alt);
int last_bit(s21_decimal_alt alt);
void s21_bank_rounding(s21_decimal_alt *alt, int mod);
void align(s21_decimal_alt *alt1, s21_decimal_alt *alt2);
void s21_rescale_alt_to_zero(s21_decimal_alt *alt_value_1,
                             s21_decimal_alt *alt_value_2);
s21_decimal_alt div_with_modulo(s21_decimal_alt alt_value_1,
                                s21_decimal_alt alt_value_2,
                                s21_decimal_alt *alt_result);
void s21_truncate_alt(s21_decimal_alt *alt_value);

void decrease_non_significant(s21_decimal *value);
int8_t align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                            int *possible);

void print_binary_representation_std(s21_decimal std);
void print_binary_representation_alt(s21_decimal_alt alt);
void print_binary_representation_std_s(s21_decimal std);
void print_binary_representation_alt_s(s21_decimal_alt alt);

void print_str_decimal_std(s21_decimal decimal);

s21_decimal_alt s21_convert_int_to_alt(unsigned long int number);
s21_decimal_alt s21_revert_alt_decimal(s21_decimal_alt alt, int i);
s21_decimal s21_convert_int_to_std(unsigned long int number);
long int s21_convert_std_to_int(s21_decimal decimal);
long int s21_convert_alt_to_int(s21_decimal_alt alt);

#endif  // SRC_UTILITS_S21_UTILITY_H_
