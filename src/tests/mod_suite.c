#include "../s21_decimal.h"
#include "../utilits/s21_utility.h"
#include "s21_decimal_test.h"

START_TEST(basic_mod) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  dec1.bits[0] = 10;
  dec2.bits[0] = 4;
  // 10 % 4 = 2

  s21_decimal true_ans;
  init_decimal(&true_ans);
  true_ans.bits[0] = 2;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mod_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  // 164471392.8219 % -2829034.112383 = 387414.303686

  // 164471392.8219
  // 00000000 00000000 00000001 01111110
  // 11110000 10010110 11100110 00011011
  // 00000000 00000100 00000000 00000000
  dec1.bits[0] = 4036421147;
  dec1.bits[1] = 382;
  dec1.bits[3] = 262144;

  // -2829034.112383
  // 00000000 00000000 00000010 10010010
  // 10101111 10010010 11000101 01111111
  // 10000000 00000110 00000000 00000000
  dec2.bits[0] = 2945631615;
  dec2.bits[1] = 658;
  dec2.bits[3] = 2147876864;

  // 387414.303686
  // 00000000 00000000 00000000 01011010
  // 00110011 10110001 00100011 11000110
  // 00000000 00000110 00000000 00000000
  s21_decimal true_ans;
  init_decimal(&true_ans);
  true_ans.bits[0] = 867247046;
  true_ans.bits[1] = 90;
  true_ans.bits[3] = 393216;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mod_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  init_decimal(&ans);
  // -1624980713402947.82193 % 85460968.29048340298 = -53115272.67168058004

  // -1624980713402947.82193
  // 00000000 00000000 00000000 00001000
  // 11001111 00011101 00011110 11101110
  // 10101100 01011010 10111100 11110001
  // 10000000 00000101 00000000 00000000
  dec1.bits[0] = 2891627761;
  dec1.bits[1] = 3474792174;
  dec1.bits[2] = 8;
  dec1.bits[3] = 2147811328;

  // 85460968.29048340298
  // 01110110 10011001 11010101 11001001
  // 01101111 10000100 10111111 01001010
  // 00000000 00001011 00000000 00000000
  dec2.bits[0] = 1870970698;
  dec2.bits[1] = 1989793225;
  dec2.bits[3] = 720896;

  // -53115272.67168058004
  // 01001001 10110110 01010101 11101000
  // 01100110 01011010 01111010 10010100
  // 10000000 00001011 00000000 00000000
  s21_decimal true_ans;
  init_decimal(&true_ans);
  true_ans.bits[0] = 1717205652;
  true_ans.bits[1] = 1236686312;
  true_ans.bits[3] = 720896 + MINUS_SIGN;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(readme_mod) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  init_decimal(&ans);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 1;
  dec2.bits[3] = 196608;

  s21_decimal true_ans;
  init_decimal(&true_ans);

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(division_on_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  init_decimal(&ans);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 0;
  dec2.bits[3] = 196608;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 3;  // операция прошла успешно

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(division_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init_decimal(&dec1);
  init_decimal(&dec2);
  init_decimal(&ans);
  dec1.bits[0] = 0;
  dec1.bits[3] = 196608;

  dec2.bits[0] = 217948;
  dec2.bits[3] = 196608;

  s21_decimal true_ans;
  init_decimal(&true_ans);
  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* mod_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("s21_mod");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_mod);
  tcase_add_test(tc_core, basic_mod_2);
  tcase_add_test(tc_core, basic_mod_3);
  tcase_add_test(tc_core, readme_mod);
  tcase_add_test(tc_core, division_on_zero);
  tcase_add_test(tc_core, division_zero);
  suite_add_tcase(s, tc_core);

  return s;
}
