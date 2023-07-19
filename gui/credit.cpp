#include "credit.h"

#include <QTableWidget>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->radioButton_aut->click();
}
Credit::~Credit() { delete ui; }

void Credit::on_pushButton_calc_clicked() {
  int period = ui->time_credit->text().toInt();
  double sum = ui->sum_credit->text().toDouble();
  double proc = ui->percent_credit->text().toInt();
  if (ui->year_and_month->currentIndex() == 1) {
    period *= 12;
  }
  if (ui->radioButton_aut->isChecked()) {
    monthInfo *monthRes = calculate_annuity_payments(sum, proc, period);
    credit = new Result_credit(period, monthRes);
  } else if (ui->radioButton_dif->isChecked()) {
    monthInfo *monthRes = calculate_diff_payments(sum, proc, period);
    credit = new Result_credit(period, monthRes);
  }
  credit->show();
}
