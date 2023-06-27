#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <stdbool.h>
#include <stdint.h>

#define INFORMATION_BIT 3
#define MINUS_SIGN 2147483648
#define PIECE_AMOUNT 32
#define NUMBER_PICES 3
#define ALL_PICES 4

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[192];
  bool sign;
  int exp;
} s21_decimal_alt;

typedef enum {
  OPERATION_OK = 0,
  NUMBER_TOO_BIG,
  NUMBER_TOO_SMALL,
  DIVISION_BY_ZERO
} operation_result;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

#define CHECK_EXPONENT(condition, first, second)   \
  do {                                             \
    if (condition) {                               \
      align_exponent_rangs(&first, &second, NULL); \
    }                                              \
  } while (0)

enum S21_DECIMAL_COMPARE {
  S21_FALSE = 0,
  S21_TRUE = 1,
  S21_VARIANT = 2,  // for not binary functions results
};

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int8_t s21_is_equal(s21_decimal first, s21_decimal second);
int8_t s21_is_not_equal(s21_decimal first, s21_decimal second);
int8_t s21_is_greater(s21_decimal first, s21_decimal second);
int8_t s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int8_t s21_is_less(s21_decimal first, s21_decimal second);
int8_t s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int8_t s21_is_less(s21_decimal first, s21_decimal second);
int8_t s21_compare_less(s21_decimal first, s21_decimal second);
int8_t s21_sign_comparison(s21_decimal first, s21_decimal second);
int8_t number_less(s21_decimal value_1, s21_decimal value_2);
int8_t s21_is_zero_decimal(s21_decimal source);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_round(s21_decimal value, s21_decimal *res);
int s21_floor(s21_decimal value, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *res);
int s21_truncate(s21_decimal value, s21_decimal *res);

#endif  // SRC_S21_DECIMAL_H_
