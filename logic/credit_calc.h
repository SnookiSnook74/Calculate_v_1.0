#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_INTEREST_RATE 7.50

typedef struct {
  int month;  // Номер месяца в течении срока кредитования
  double payment;  // Общая сумма платежа за этот месяц
  double interest_payment;  // Сумма платежа по процентам за этот месяц
  double debt_payment;  // Сумма платежа по основному долгу за этот месяц
  double remaining_debt;  // Оставшаяся сумма долга после платежа в этом месяце
} monthInfo;
typedef struct {
  double accrued_interest;   // Начисленные проценты
  double tax;                // Сумма налога
  double remaining_balance;  // Остаток на вкладе
} depositInfo;

monthInfo* calculate_annuity_payments(double sum_credit, double procent,
                                      int time);
monthInfo* calculate_diff_payments(double sum_credit, double procent, int time);
// Определение высокосного кода
int is_leap_year(int year);

depositInfo* calculate_deposit_yield(double initial_sum, int term,
                                     double interest_rate, double tax_rate,
                                     int is_capitalization);
#ifdef __cplusplus
}
#endif

#endif  // CREDIT_CALC_H
