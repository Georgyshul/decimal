#include "../s21_decimal.h"
#include "s21_utility.h"

bool s21_get_bit_int(unsigned int num, int pos) { return (num >> pos) & 1; }

int8_t get_bit(s21_decimal value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  return (value.bits[piece] & (1 << bit)) ? 1 : 0;
}

int8_t get_sign_bit(s21_decimal value) {
  int8_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  int8_t sign = get_bit(value, position);
  return sign;
}

int8_t get_position(int8_t piece, int8_t bit) {
  int8_t position = piece * PIECE_AMOUNT + bit;
  return position;
}

// Function increases order of magnitude for a number in decimal(10) notation
// Return number of possible increase + 1 without overflow or 0
int increase_order_of_magnitude(s21_decimal *value, int times, int *possible) {
  int error = 0;
  s21_decimal result;
  s21_copy_decimal(*value, &result);

  int i;
  for (i = 0; i < times && !error; ++i) {
    s21_decimal buffer_1, buffer_2;
    s21_copy_decimal(result, &buffer_1);
    s21_copy_decimal(result, &buffer_2);

    error += multiply_by_two(&buffer_1, 3);
    multiply_by_two(&buffer_2, 1);

    error += add_bit_by_bit(buffer_1, buffer_2, &result);
  }

  if (!error) {
    copy_only_number(result, value);
    set_exponent_rang(value, get_exponent_rang(*value) + times);
  } else if (possible != NULL) {
    *possible = i - 1;
  }

  return error;
}

void s21_copy_decimal(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 4; ++i) dst->bits[i] = src.bits[i];
}

void set_exponent_rang(s21_decimal *value, uint8_t exponent_rang) {
  for (int i = 16; i <= 23; ++i) {
    int8_t position = get_position(INFORMATION_BIT, i);
    set_bit(value, position, exponent_rang % 2);
    exponent_rang /= 2;
  }
}

void init(s21_decimal *value) {
  for (int i = 0; i < 4; ++i) value->bits[i] = 0;
}

void int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *difference) {
  int main_bit_dif = find_main_bit(value_1) - find_main_bit(value_2);
  init(difference);
  init(result);

  if (main_bit_dif >= 0) {
    multiply_by_two(&value_2, main_bit_dif);

    while (main_bit_dif >= 0) {
      sub_bit_by_bit(value_1, value_2, difference);
      if (!get_sign_bit(*difference)) {
        copy_only_number(*difference, &value_1);
        put_bit(result, 0);
      }
      if (main_bit_dif) {
        multiply_by_two(result, 1);
        divide_by_two(&value_2);
      }
      --main_bit_dif;
    }
  }

  copy_only_number(value_1, difference);
  set_sign_bit(difference, 0);
}

int multiply_by_two(s21_decimal *value, int times) {
  int error = 0;
  s21_decimal buffer;
  s21_copy_decimal(*value, &buffer);

  for (int i = 0; i < times && !error; ++i) {
    if (!get_bit(*value, 3 * PIECE_AMOUNT - 1)) {
      value->bits[2] = value->bits[2] << 1;
      set_bit(value, 2 * PIECE_AMOUNT, get_bit(*value, 2 * PIECE_AMOUNT - 1));
      value->bits[1] = value->bits[1] << 1;
      set_bit(value, PIECE_AMOUNT, get_bit(*value, PIECE_AMOUNT - 1));
      value->bits[0] = value->bits[0] << 1;
    } else {
      s21_copy_decimal(buffer, value);
      error = 1;
    }
  }

  return error;
}

void set_bit(s21_decimal *value, int8_t position, int8_t bit) {
  if (bit)
    put_bit(value, position);
  else
    delete_bit(value, position);
}

void put_bit(s21_decimal *value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  value->bits[piece] |= (1 << bit);
}

int find_main_bit(s21_decimal value) {
  int pos;
  int stop = 0;

  for (pos = (NUMBER_PICES - 1) * PIECE_AMOUNT - 1; pos >= 0 && !stop; --pos) {
    if (get_bit(value, pos)) stop = 1;
  }

  int main_bit = pos + 1;
  return main_bit;
}

void set_sign_bit(s21_decimal *value, uint8_t sign_bit) {
  int8_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  set_bit(value, position, sign_bit);
}

void delete_bit(s21_decimal *value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  value->bits[piece] &= ~(1 << bit);
}

void sub_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  init(result);

  if (number_less(value_1, value_2)) {
    s21_decimal buffer;
    s21_copy_decimal(value_1, &buffer);
    s21_copy_decimal(value_2, &value_1);
    s21_copy_decimal(buffer, &value_2);
    set_sign_bit(result, 1);
  }

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT; ++pos) {
    if (get_bit(value_2, pos)) {
      if (!get_bit(value_1, pos)) {
        put_bit(result, pos);

        int k = 1;
        while (!get_bit(value_1, pos + k)) {
          put_bit(&value_1, pos + k);
          ++k;
        }

        delete_bit(&value_1, pos + k);
      }
    } else {
      set_bit(result, pos, get_bit(value_1, pos));
    }
  }
}

void copy_only_number(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < NUMBER_PICES; ++i) dst->bits[i] = src.bits[i];
}

int add_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int next_bite = 0;
  int error = 0;
  init(result);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT; ++pos) {
    int8_t k = get_bit(value_1, pos) + get_bit(value_2, pos) + next_bite;

    if (k % 2) put_bit(result, pos);
    if (k >= 2)
      next_bite = 1;
    else
      next_bite = 0;
  }

  if (next_bite) error = 1;
  return error;
}

int8_t divide_by_two(s21_decimal *value) {
  int8_t remainder = get_bit(*value, 0);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT - 1; ++pos) {
    set_bit(value, pos, get_bit(*value, pos + 1));
  }

  return remainder;
}

int8_t decrease_order_of_magnitude(s21_decimal *value) {
  s21_decimal remainder_dec, result, divider;
  s21_from_int_to_decimal(10, &divider);

  init(&result);
  int_div(*value, divider, &result, &remainder_dec);

  set_sign_bit(&result, get_sign_bit(*value));
  int exp_rang = get_exponent_rang(*value);
  if (exp_rang >= 1) set_exponent_rang(&result, exp_rang - 1);

  int remainder;
  s21_from_decimal_to_int(remainder_dec, &remainder);

  s21_copy_decimal(result, value);
  return remainder;
}

int is_zero(s21_decimal value) {
  int is_zero = 1;
  for (int i = 0; i < NUMBER_PICES - 1; ++i)
    if (value.bits[i] != 0) is_zero = 0;

  return is_zero;
}

// сдвиг вправо для альтернативного децимала
void s21_right_shift(s21_decimal_alt *alt) {
  for (int i = 0; i < 191; i++) alt->bits[i] = alt->bits[i + 1];
  alt->bits[191] = 0;
}

int8_t get_exponent_rang(s21_decimal value) {
  int8_t exponent_rang = 0;
  int power = 1;

  for (int i = 16; i <= 23; ++i) {
    int8_t position = get_position(INFORMATION_BIT, i);
    exponent_rang += get_bit(value, position) * power;
    power *= 2;
  }

  return exponent_rang;
}

int8_t align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                            int *possible) {
  int8_t error = 0;
  decrease_non_significant(value_1);
  decrease_non_significant(value_2);

  int8_t exp_diff = get_exponent_rang(*value_1) - get_exponent_rang(*value_2);
  s21_decimal *ptr = value_2;

  if (exp_diff) {
    if (exp_diff < 0) {
      ptr = value_1;
      exp_diff *= -1;
    }

    s21_decimal buffer;
    s21_copy_decimal(*ptr, &buffer);

    error = increase_order_of_magnitude(&buffer, exp_diff, possible);
    if (!error)
      increase_order_of_magnitude(ptr, exp_diff, NULL);
    else if (ptr == value_1)
      *possible *= -1;
  }

  return error;
}

void decrease_non_significant(s21_decimal *value) {
  s21_decimal buffer;
  s21_copy_decimal(*value, &buffer);
  int remainder = 0;

  while (remainder != 0 && (get_exponent_rang(*value) != 0)) {
    remainder = decrease_order_of_magnitude(&buffer);
    if (!remainder) s21_copy_decimal(buffer, value);
  }

  s21_copy_decimal(buffer, value);
}

// сдвиг влево для альтернативного децимала
// нужно при умножении
void s21_left_shift(s21_decimal_alt *alt) {
  for (int i = 191; i > 0; i--) alt->bits[i] = alt->bits[i - 1];
  alt->bits[0] = 0;
}

bool s21_get_sign_std(s21_decimal dec) {
  return s21_get_bit_int(dec.bits[3], 31);
}

int s21_get_exp_std(s21_decimal dec) {
  return (dec.bits[3] % 2147483648) >> 16;
}

void s21_null_decimal_alt(s21_decimal_alt *alt) {
  alt->sign = 0;
  alt->exp = 0;
  for (int i = 0; i < 192; i++) alt->bits[i] = 0;
}

void init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

// сравнение битов первого и второго альтернативного децимала
// не учитывает экспоненту
// возвращает 1, если первое число больше или равно второму
// 0 если второе число больше первого
bool compare_bits(s21_decimal_alt alt1, s21_decimal_alt alt2) {
  int i = 191;
  while (i >= 0 && alt1.bits[i] == alt2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : alt1.bits[i];
}

// равен ли альтернативный децимал 0
bool is_null(s21_decimal_alt alt) {
  bool result = 0;
  for (int i = 0; i < 192; i++) result += alt.bits[i];
  return !result;
}

// где находится самый левый единичный бит?
int last_bit(s21_decimal_alt alt) {
  int i = -1;
  if (!is_null(alt)) {
    for (i = 191; i >= 0; i--)
      if (alt.bits[i] == 1) break;
  }
  return i;
}

// "выравнивание" чисел
// нужно в делении
// превращает, например, 1001 и 10 в 1001 и 1000
// но 1001 и 11 в 1001 и 110
// по совершенно непонятным мне причинам не работает с div_by_ten
void align(s21_decimal_alt *alt_value_1, s21_decimal_alt *alt_value_2) {
  if (!is_null(*alt_value_1) && !is_null(*alt_value_2)) {
    int l1 = last_bit(*alt_value_1);
    int l2 = last_bit(*alt_value_2);
    while (last_bit(*alt_value_1) != last_bit(*alt_value_2))
      if (compare_bits(*alt_value_1, *alt_value_2))
        s21_left_shift(alt_value_2);
      else
        s21_left_shift(alt_value_1);
    if (!compare_bits(*alt_value_1, *alt_value_2)) s21_left_shift(alt_value_1);
    if (alt_value_1->bits[0] == 0 && alt_value_2->bits[0] == 0 &&
        last_bit(*alt_value_1) > l1 && last_bit(*alt_value_2) > l2) {
      s21_right_shift(alt_value_1);
      s21_right_shift(alt_value_2);
    }
  }
}
