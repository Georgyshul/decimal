#include "s21_utility.h"

void s21_rescale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal_alt alt_value_1 = s21_convert_std_to_alt(*value_1);
  s21_decimal_alt alt_value_2 = s21_convert_std_to_alt(*value_2);
  s21_rescale_alt(&alt_value_1, &alt_value_2);
  *value_1 = s21_convert_alt_to_std(alt_value_1);
  *value_2 = s21_convert_alt_to_std(alt_value_2);
}

// рескейл на уровне альтернативных децималов
void s21_rescale_alt(s21_decimal_alt *alt_value_1,
                     s21_decimal_alt *alt_value_2) {
  s21_decimal_alt ten;
  s21_null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (!is_null(*alt_value_1) && !is_null(*alt_value_2)) {
    if (alt_value_1->exp > alt_value_2->exp) {
      int exp_dif = alt_value_1->exp - alt_value_2->exp;
      for (int i = 0; i < exp_dif; i++)
        s21_mul_alt(*alt_value_2, ten, alt_value_2);
      if (last_bit(*alt_value_2) > 95) {
        s21_rescale_alt_to_smaller(alt_value_1, alt_value_2);
      }
      alt_value_2->exp = alt_value_1->exp;
    } else if (alt_value_2->exp > alt_value_1->exp) {
      s21_rescale_alt(alt_value_2, alt_value_1);
    }
  } else if (is_null(*alt_value_1)) {
    alt_value_1->exp = alt_value_2->exp;
  } else {
    alt_value_2->exp = alt_value_1->exp;
  }
}

void s21_rescale_alt_to_smaller(s21_decimal_alt *alt_value_1,
                                s21_decimal_alt *alt_value_2) {
  int mod1 = 0, mod2 = 0;
  while (last_bit(*alt_value_2) > 95) {
    mod1 = div_by_ten(alt_value_1);
    mod2 = div_by_ten(alt_value_2);
  }
  s21_bank_rounding(alt_value_1, mod1);
  s21_bank_rounding(alt_value_2, mod2);
  if (last_bit(*alt_value_2) > 95) {
    mod1 = div_by_ten(alt_value_1);
    mod2 = div_by_ten(alt_value_2);
    s21_bank_rounding(alt_value_1, mod1);
    s21_bank_rounding(alt_value_2, mod2);
  }
}

// приводит exp к нулю, нужно для деления
void s21_rescale_alt_to_zero(s21_decimal_alt *alt_value_1,
                             s21_decimal_alt *alt_value_2) {
  s21_decimal_alt ten;
  s21_null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (alt_value_1->exp > alt_value_2->exp) {
    alt_value_1->exp -= alt_value_2->exp;
    alt_value_2->exp = 0;
    while (alt_value_1->exp != 0) {
      alt_value_1->exp--;
      s21_mul_alt(*alt_value_2, ten, alt_value_2);
    }
  } else {
    alt_value_2->exp -= alt_value_1->exp;
    alt_value_1->exp = 0;
    while (alt_value_2->exp != 0) {
      alt_value_2->exp--;
      s21_mul_alt(*alt_value_1, ten, alt_value_1);
    }
  }
}
