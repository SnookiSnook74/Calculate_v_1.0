#include <check.h>
#include <limits.h>

#include "../logic/credit_calc.h"
#include "../logic/parser.h"

START_TEST(s21_calc_0) {
  char *str = "1+2+3";
  double cal = calculate(str);
  double result = 6;
  ck_assert_double_eq_tol(cal, result, 1e-7);
}
END_TEST

START_TEST(s21_calc_1) {
  char *str = "1+2+3+sin(2)+cos(5)*2";
  double cal = calculate(str);
  double result = 7.4766217;
  ck_assert_double_eq_tol(cal, result, 1e-7);
}
END_TEST

START_TEST(s21_calc_2) {
  char *str = "1+2+3+sin(2)+cos(5)*2-2/3*2^3";
  double cal = calculate(str);
  double result = 2.1432884;
  ck_assert_double_eq_tol(cal, result, 1e-7);
}
END_TEST

START_TEST(s21_calc_3) {
  char *str = "5/0";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_4) {
  char *str = "-cos(5)+1";
  double cal = calculate(str);
  double result = 0.7163378;
  ck_assert_double_eq_tol(cal, result, 1e-7);
}
END_TEST

START_TEST(s21_calc_5) {
  char *str = "acos(0.5)";
  double cal = calculate(str);
  double result = 1.0472;
  ck_assert_double_eq_tol(cal, result, 1e-4);
}
END_TEST

START_TEST(s21_calc_6) {
  char *str = "acos(0.5)+asin(0.5)+atan(0.5)";
  double cal = calculate(str);
  double result = 2.03444;
  ck_assert_double_eq_tol(cal, result, 1e-5);
}
END_TEST

START_TEST(s21_calc_7) {
  char *str = "acos(0.5)+asin(0.5)+atan(0.5)+sqrt(3)+tan(2)";
  double cal = calculate(str);
  double result = 1.58145;
  ck_assert_double_eq_tol(cal, result, 1e-5);
}
END_TEST

START_TEST(s21_calc_8) {
  char *str = "log(-5)";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_9) {
  char *str = "log(5)+log(20)";
  double cal = calculate(str);
  double result = 2;
  ck_assert_double_eq_tol(cal, result, 1e-5);
}
END_TEST

START_TEST(s21_calc_10) {
  char *str = "ln(5)+ln(20)";
  double cal = calculate(str);
  double result = 4.60517;
  ck_assert_double_eq_tol(cal, result, 1e-5);
}
END_TEST

START_TEST(s21_calc_11) {
  char *str = "1+sqrt(-4)";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_12) {
  char *str = "1+ln(-3)";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_13) {
  char *str = "1+ln(-3)))";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_14) {
  char *str = "1+lffffn(-3)))";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_15) {
  char *str = "1+()+2";
  double cal = calculate(str);
  ck_assert_msg(isnan(cal), "Expected NaN");
}
END_TEST

START_TEST(s21_calc_16) {
  char *str = "5%2/2";
  double cal = calculate(str);
  double result = 0.5;
  ck_assert_double_eq_tol(cal, result, 1e-5);
}
END_TEST

START_TEST(test_calculate_annuity_payments) {
  double sum_credit = 10000.0;
  double procent = 5.0;
  int time = 12;
  monthInfo *result = calculate_annuity_payments(sum_credit, procent, time);

  ck_assert(result != NULL);
  for (int i = 0; i < time; ++i) {
    ck_assert(result[i].month == i + 1);
    ck_assert(result[i].payment > 0.0);
    ck_assert(result[i].interest_payment > 0.0);
    ck_assert(result[i].debt_payment > 0.0);
    ck_assert(result[i].remaining_debt >= 0.0);
  }

  free(result);
}
END_TEST

START_TEST(test_calculate_diff_payments) {
  double sum_credit = 10000.0;
  double procent = 5.0;
  int time = 12;
  monthInfo *result = calculate_diff_payments(sum_credit, procent, time);

  ck_assert(result != NULL);
  for (int i = 0; i < time; ++i) {
    ck_assert(result[i].month == i + 1);
    ck_assert(result[i].payment > 0.0);
    ck_assert(result[i].interest_payment > 0.0);
    ck_assert(result[i].debt_payment > 0.0);
    ck_assert(result[i].remaining_debt >= 0.0);
  }

  free(result);
}
END_TEST

START_TEST(test_calculate_deposit_yield) {
  double initial_sum = 10000.0;
  double interest_rate = 5.0;
  double tax_rate = 2.0;
  int term = 12;
  int is_capitalization = 1;
  depositInfo *result = calculate_deposit_yield(
      initial_sum, term, interest_rate, tax_rate, is_capitalization);

  ck_assert(result != NULL);
  for (int i = 0; i < term; ++i) {
    ck_assert(result[i].accrued_interest > 0.0);
    ck_assert(result[i].remaining_balance >= initial_sum);
    ck_assert(result[i].tax >= 0.0);
  }

  free(result);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Core");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_calc_0);
  tcase_add_test(tc_core, s21_calc_1);
  tcase_add_test(tc_core, s21_calc_2);
  tcase_add_test(tc_core, s21_calc_3);
  tcase_add_test(tc_core, s21_calc_4);
  tcase_add_test(tc_core, s21_calc_5);
  tcase_add_test(tc_core, s21_calc_6);
  tcase_add_test(tc_core, s21_calc_7);
  tcase_add_test(tc_core, s21_calc_8);
  tcase_add_test(tc_core, s21_calc_9);
  tcase_add_test(tc_core, s21_calc_10);
  tcase_add_test(tc_core, s21_calc_11);
  tcase_add_test(tc_core, s21_calc_12);
  tcase_add_test(tc_core, s21_calc_13);
  tcase_add_test(tc_core, s21_calc_14);
  tcase_add_test(tc_core, s21_calc_15);
  tcase_add_test(tc_core, s21_calc_16);
  tcase_add_test(tc_core, test_calculate_annuity_payments);
  tcase_add_test(tc_core, test_calculate_diff_payments);
  tcase_add_test(tc_core, test_calculate_deposit_yield);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_calc_suite();
  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}