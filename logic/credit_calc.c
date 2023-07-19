#include "credit_calc.h"

#include <time.h>

monthInfo* calculate_annuity_payments(double sum_credit, double procent,
                                      int time) {
  procent /= 100.0;  // Преобразуем процентную ставку в десятичное число
  double K = procent / 12;  // Ежемесячная процентная ставка
  double A = round(sum_credit * (K * pow(1 + K, time)) /
                   (pow(1 + K, time) - 1) * 100) /
             100.0;  // Аннуитетный платеж с округлением
  monthInfo* payments = malloc(sizeof(monthInfo) * time);
  if (!payments) {
    printf("Failed to allocate memory.\n");
    return NULL;
  }
  for (int i = 0; i < time; ++i) {
    double interest_payment = round(sum_credit * K * 100) /
                              100.0;  // Платеж по процентам с округлением
    double debt_payment = round((A - interest_payment) * 100) /
                          100.0;  // Платеж по основному долгу с округлением
    sum_credit = round((sum_credit - debt_payment) * 100) /
                 100.0;  // Остаток долга с округлением

    payments[i].month = i + 1;
    payments[i].payment = A;
    payments[i].interest_payment = interest_payment;
    payments[i].debt_payment = debt_payment;
    payments[i].remaining_debt = sum_credit;
  }

  return payments;
}

monthInfo* calculate_diff_payments(double sum_credit, double procent,
                                   int time) {
  procent /= 100.0;
  double P = sum_credit / time;
  monthInfo* payments = malloc(sizeof(monthInfo) * time);
  if (!payments) {
    return NULL;
  }
  for (int i = 0; i < time; ++i) {
    double interest_payment = sum_credit * procent / 12;
    sum_credit = sum_credit - P;
    double A = P + interest_payment;
    payments[i].month = i + 1;
    payments[i].payment = round(A * 100) / 100;
    payments[i].interest_payment = round(interest_payment * 100) / 100;
    payments[i].debt_payment = round(P * 100) / 100;
    payments[i].remaining_debt = round(sum_credit * 100) / 100;
  }
  return payments;
}

int is_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

depositInfo* calculate_deposit_yield(double initial_sum, int term,
                                     double interest_rate, double tax_rate,
                                     int is_capitalization) {
  interest_rate /= 100.0;  // Преобразуем процентную ставку в десятичное число
  tax_rate /= 100.0;  // Преобразуем налоговую ставку в десятичное число
  double tax_free_income =
      1000000 * KEY_INTEREST_RATE / 100.0;  // Необлагаемый доход
  depositInfo* info = (depositInfo*)malloc(sizeof(depositInfo) * term);
  if (!info) {
    printf("Failed to allocate memory.\n");
    return NULL;
  }
  double balance = initial_sum;
  // Получаем текущую дату
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  double total_interest = 0;  // Общая сумма начисленных процентов
  int days_in_month_normal[12] = {31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
  int days_in_month_leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  for (int i = 0; i < term; ++i) {
    int month = (tm.tm_mon + i) % 12;  // Номер месяца
    int year = tm.tm_year + 1900 + (tm.tm_mon + i) / 12;  // Год
    int* days_in_month =
        is_leap_year(year) ? days_in_month_leap : days_in_month_normal;
    int days_in_year = 365 + is_leap_year(year);  // Количество дней в году

    double interest = round(balance * interest_rate * days_in_month[month] /
                            days_in_year * 100) /
                      100;  // Вычисляем начисленные проценты и округляем
    // Если это январь, вычитаем 0.159%
    if (month == 0) {
      interest *= (1 - 0.00159);
    }
    total_interest += interest;
    if (is_capitalization) {
      balance += interest;  // Если есть капитализация, увеличиваем баланс
    }

    info[i].accrued_interest = interest;
    info[i].remaining_balance = balance;
  }

  double taxable_income =
      total_interest - tax_free_income;  // Налогооблагаемый доход
  if (taxable_income < 0) {
    taxable_income = 0;  // Если налогооблагаемый доход отрицательный,
                         // устанавливаем его равным 0
  }
  double total_tax = round(taxable_income * tax_rate * 100) /
                     100;  // Вычисляем сумму налога и округляем
  balance -= total_tax;  // Вычитаем налог из баланса

  for (int i = 0; i < term; ++i) {
    info[i].tax = total_tax;
    info[i].remaining_balance = balance;
  }

  return info;
}
