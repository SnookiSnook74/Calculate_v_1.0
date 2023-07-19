#include "result_deposit.h"

#include "ui_result_deposit.h"

Result_deposit::Result_deposit(int term, double sum, depositInfo* info,
                               QWidget* parent)
    : QWidget(parent), ui(new Ui::Result_deposit) {
  ui->setupUi(this);
  ui->tableWidget->setRowCount(term);

  double total_accrued_interest = 0;

  for (int i = 0; i < term; ++i) {
    ui->tableWidget->setItem(i, 0,
                             new QTableWidgetItem(QString::number(i + 1)));
    ui->tableWidget->setItem(i, 1,
                             new QTableWidgetItem(QString::number(
                                 info[i].accrued_interest, 'f', 2)));
    total_accrued_interest += info[i].accrued_interest;
  }

  ui->label_sum_proc->setText(QString::number(total_accrued_interest, 'f', 2));
  ui->label_sum_dep->setText(
      QString::number(total_accrued_interest + sum, 'f', 2));
  ui->label_sum_nalog->setText(QString::number(info->tax, 'f', 2));

  ui->tableWidget->resizeColumnsToContents();
}

Result_deposit::~Result_deposit() { delete ui; }
