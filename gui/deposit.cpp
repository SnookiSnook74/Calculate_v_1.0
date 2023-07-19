#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  ui->radioButton_no->click();
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_pushButton_calc_deposit_clicked() {
  double sum = ui->sum_deposit->text().toDouble();
  int time_dep = ui->time_deposit->text().toInt();
  double proc = ui->percent_deposit->text().toDouble();
  double proc_nalog = ui->percent_deposit_nalog->text().toDouble();
  int capital = 0;
  if (ui->radioButton_yes->isChecked()) {
    capital = 1;
  }

  depositInfo *info =
      calculate_deposit_yield(sum, time_dep, proc, proc_nalog, capital);

  deposit_calc = new Result_deposit(time_dep, sum, info);

  deposit_calc->show();
}
