#include "s21_utility.h"

int s21_div_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result) {
  s21_decimal_alt ten;
  s21_null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_null_decimal_alt(alt_result);
  int return_code = 0;
  bool sign = alt_value_1.sign ^ alt_value_2.sign;
  alt_value_1.sign = 0;
  alt_value_2.sign = 0;

  s21_rescale_alt_to_zero(&alt_value_1, &alt_value_2);
  s21_decimal_alt modulo;
  s21_null_decimal_alt(&modulo);
  modulo = div_with_modulo(alt_value_1, alt_value_2, &alt_value_1);
  int exp = 0;
  int status = 0;
  while (!is_null(alt_value_1) || !is_null(modulo)) {
    exp++;
    s21_mul_alt(modulo, ten, &modulo);
    s21_mul_alt(*alt_result, ten, alt_result);
    status = s21_add_alt(*alt_result, alt_value_1, alt_result);
    modulo = div_with_modulo(modulo, alt_value_2, &alt_value_1);
    if (status == 1) break;
  }
  int mod;
  if (status == 1) {
    mod = div_by_ten(alt_result);
    while (last_bit(*alt_result) > 95 && exp > 0) {
      mod = div_by_ten(alt_result);
      exp--;
    }
    s21_bank_rounding(alt_result, mod);
    exp--;
  }
  alt_result->exp = exp - 1;
  mod = 10;
  while (alt_result->exp > 28) mod = div_by_ten(alt_result);
  if (is_null(*alt_result))
    return_code = 2;
  else if (mod != 10)
    s21_bank_rounding(alt_result, mod);
  if (last_bit(*alt_result) > 95) return_code = 1;
  alt_result->sign = sign;
  return return_code;
}

s21_decimal_alt div_with_modulo(s21_decimal_alt alt_value_1,
                                s21_decimal_alt alt_value_2,
                                s21_decimal_alt *alt_result) {
  int denominator_left_bit = last_bit(alt_value_2);
  s21_decimal_alt modulo;
  s21_null_decimal_alt(&modulo);
  s21_null_decimal_alt(alt_result);
  if (compare_bits(alt_value_1, alt_value_2)) {
    align(&alt_value_1, &alt_value_2);
  }
  for (int i = 0; i < 191; i++) {
    if (compare_bits(alt_value_1, alt_value_2)) {
      s21_sub_alt(alt_value_1, alt_value_2, &alt_value_1);
      alt_result->bits[0] = 1;
    }
    if (last_bit(alt_value_2) <= denominator_left_bit) break;
    if (last_bit(alt_value_2) > denominator_left_bit)
      s21_right_shift(&alt_value_2);
    s21_left_shift(alt_result);
  }
  return alt_value_1;
}
