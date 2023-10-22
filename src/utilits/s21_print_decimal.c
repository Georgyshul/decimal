#include <stdio.h>
#include <stdlib.h>

#include "s21_utility.h"
#include <gmp.h>

// функции побитовой печати не нужны для сдачи проекта
// чисто для проверки

// распечатка бинарной формы стандартного децимала
// распечатываются склеенные второй, первый и нулевой бит
// и через пробел -- третий бит с пробелом перед младшим словом
void print_binary_representation_std(s21_decimal std) {
  for (int i = 2; i >= 0; i--)
    for (int j = 31; j >= 0; j--) printf("%i", s21_get_bit_int(std.bits[i], j));
  printf(" ");
  for (int j = 31; j >= 16; j--) printf("%i", s21_get_bit_int(std.bits[3], j));
  printf(" ");
  for (int j = 15; j >= 0; j--) printf("%i", s21_get_bit_int(std.bits[3], j));
  printf("\n");
}

// распечатка бинарной формы альтернативного децимала
// распечатываются все биты от старшего к младшему
// и через пробелы - знак (1 - минус, 0 - плюс)
// и положение точки
void print_binary_representation_alt(s21_decimal_alt alt) {
  for (int i = 191; i >= 96; i--) printf("%i", alt.bits[i]);
  printf(" ");
  for (int i = 95; i >= 0; i--) printf("%i", alt.bits[i]);
  printf(" %i %i\n", alt.sign, alt.exp);
}

// КОРОТКИЕ РАСПЕЧАТКИ ЧИСЕЛ
// сделано для простоты дебага
////////////////////////////////////////////////////////////
void print_binary_representation_std_s(s21_decimal std) {
  for (int j = 31; j >= 0; j--) printf("%i", s21_get_bit_int(std.bits[0], j));
  printf(" ");
  for (int j = 31; j >= 16; j--) printf("%i", s21_get_bit_int(std.bits[3], j));
  printf("\n");
}

void print_binary_representation_alt_s(s21_decimal_alt alt) {
  for (int i = 20; i >= 0; i--) printf("%i", alt.bits[i]);
  printf(" %i %i\n", alt.sign, alt.exp);
}
///////////////////////////////////////////////////////////

/*
void print_str_decimal_std(s21_decimal decimal) {
  mpz_t number;
  mpz_init(number);

  s21_decimal_alt alt = s21_convert_std_to_alt(decimal);

  for (int i = 95; i >= 0; i--) {
    mpz_mul_ui(number, number, 2);
    mpz_add_ui(number, number, alt.bits[i]);
  }

  char* decimalString = mpz_get_str(NULL, 10, number);

  printf("%s\n", decimalString);

  mpz_clear(number);
  free(decimalString);
}
*/

void print_str_decimal_std(s21_decimal decimal) {
  char str[97];
  int index = 0;
  mpz_t res;
  mpz_init(res);

  for (int i = 2; i >= 0; --i) {
      for (long int j = 31; j >= 0; --j) {
          if (decimal.bits[i] & (1 << j)) {
              str[index++] = '1';
          } else {
              str[index++] = '0';
          }
      }
  }
  str[index] = 0;

  mpz_set_str(res, str, 2);

  if (get_sign_bit(decimal)) printf("-");
  gmp_printf("%Zd * 10^(-%d)\n", res, get_exponent_rang(decimal));

  mpz_clear(res);
}