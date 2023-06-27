#include "s21_utility.h"

int s21_mod_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result) {
  int return_code = 0;
  bool sign = alt_value_1.sign;
  alt_value_1.sign = 0;
  alt_value_2.sign = 0;
  s21_decimal_alt factor;
  s21_div_alt(alt_value_1, alt_value_2, &factor);
  s21_truncate_alt(&factor);
  s21_mul_alt(alt_value_2, factor, &factor);
  s21_rescale_alt(&alt_value_1, &factor);
  s21_sub_alt(alt_value_1, factor, alt_result);
  alt_result->exp = factor.exp;
  if (last_bit(*alt_result) > 95) s21_truncate_alt(alt_result);
  if (last_bit(*alt_result) > 95) return_code = 1;
  alt_result->sign = sign;
  return return_code;
}
