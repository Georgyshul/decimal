#include "../s21_decimal.h"
#include "../utilits/s21_utility.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    return_code = 3;
  } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[2] == 0) {
    init_decimal(result);
  } else {
    s21_decimal_alt alt_value_1 = s21_convert_std_to_alt(value_1);
    s21_decimal_alt alt_value_2 = s21_convert_std_to_alt(value_2);
    s21_decimal_alt alt_result;
    s21_null_decimal_alt(&alt_result);
    while (alt_value_1.bits[0] == 0 && alt_value_2.bits[0] == 0) {
      s21_right_shift(&alt_value_1);
      s21_right_shift(&alt_value_2);
    }
    return_code = s21_div_alt(alt_value_1, alt_value_2, &alt_result);
    *result = s21_convert_alt_to_std(alt_result);
  }
  return return_code;
}
