#include "../s21_decimal.h"
#include "../utilits/s21_utility.h"

int s21_truncate(s21_decimal value, s21_decimal *res) {
  int return_code = 0;
  if (res) {
    s21_decimal_alt alt_value = s21_convert_std_to_alt(value);
    s21_truncate_alt(&alt_value);
    *res = s21_convert_alt_to_std(alt_value);
  } else {
    return_code = 1;
  }
  return return_code;
}
