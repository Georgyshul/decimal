#include "../s21_decimal.h"
#include "s21_utility.h"

// деление числа на 10
// возращает остаток от деления числа на 10
int div_by_ten(s21_decimal_alt *alt) {
  s21_decimal_alt result;
  s21_null_decimal_alt(&result);
  // возможно, эта конструкция не нужна и есть решение получше
  int exp = alt->exp;
  int sign = alt->sign;
  result.sign = 0;
  result.exp = 0;
  s21_decimal_alt ten;
  s21_null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_decimal_alt modulo = div_with_modulo(*alt, ten, alt);
  int res = s21_convert_alt_to_std(modulo).bits[0];
  // возможно, эта конструкция не нужна и есть решение получше
  alt->exp = exp - 1;
  alt->sign = sign;
  return res;
}

void s21_bank_rounding(s21_decimal_alt *alt, int mod) {
  if ((mod == 5 && alt->bits[0]) || mod > 5) {
    s21_decimal_alt one;
    s21_null_decimal_alt(&one);
    one.bits[0] = 1;
    one.exp = alt->exp;
    one.sign = alt->sign;
    s21_add_alt(*alt, one, alt);
    if (last_bit(*alt) > 95) {
      s21_sub_alt(*alt, one, alt);
      mod = div_by_ten(alt);
      s21_bank_rounding(alt, mod);
    }
  }
}
