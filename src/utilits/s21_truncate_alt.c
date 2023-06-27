#include "s21_utility.h"

void s21_truncate_alt(s21_decimal_alt *alt_value) {
  while (alt_value->exp > 0) div_by_ten(alt_value);
}
