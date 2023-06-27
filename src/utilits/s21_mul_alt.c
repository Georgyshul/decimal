#include "s21_utility.h"

int s21_mul_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
                s21_decimal_alt *alt_result) {
  int return_code = 0;
  s21_null_decimal_alt(alt_result);
  if (!is_null(alt_value_1) && !(is_null(alt_value_2))) {
    for (int i = 0; i < 192; i++) {
      if (alt_value_2.bits[i] == 1)
        s21_add_alt(*alt_result, alt_value_1, alt_result);
      s21_left_shift(&alt_value_1);
    }
    alt_result->exp = alt_value_1.exp + alt_value_2.exp;
    alt_result->sign = alt_value_1.sign ^ alt_value_2.sign;
    if (last_bit(*alt_result) > 95 || alt_result->exp > 28) {
      int mod = 0;
      while (alt_result->exp > 0 &&
             (last_bit(*alt_result) > 95 || alt_result->exp > 28)) {
        if (alt_result->exp == 0) break;
        mod = div_by_ten(alt_result);
      }
      if (alt_result->exp > 0)
        s21_bank_rounding(alt_result, mod);
      else
        return_code = 1;
    }
    if (is_null(*alt_result)) return_code = 2;
  }
  return return_code;
}
