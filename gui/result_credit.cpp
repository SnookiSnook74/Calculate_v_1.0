#include "result_credit.h"

#include "ui_result_credit.h"

Result_credit::Result_credit(int period, monthInfo* monthRes, QWidget* parent)
    : QWidget(parent), ui(new Ui::Result_credit) {
  ui->setupUi(this);
  ui->tableWidget->setRowCount(period);

  double total_payment = 0.0;   // Общая выплата
  double total_interest = 0.0;  // Общая переплата

  for (int i = 0; i < period; ++i) {
    ui->tableWidget->setItem(
        i, 0, new QTableWidgetItem(QString::number(monthRes[i].month)));
    ui->tableWidget->setItem(
        i, 1,
        new QTableWidgetItem(QString::number(monthRes[i].payment, 'f', 2)));
    ui->tableWidget->setItem(i, 2,
                             new QTableWidgetItem(QString::number(
                                 monthRes[i].interest_payment, 'f', 2)));
    ui->tableWidget->setItem(i, 3,
                             new QTableWidgetItem(QString::number(
                                 monthRes[i].debt_payment, 'f', 2)));
    ui->tableWidget->setItem(i, 4,
                             new QTableWidgetItem(QString::number(
                                 monthRes[i].remaining_debt, 'f', 2)));

    total_payment += monthRes[i].payment;
    total_interest += monthRes[i].interest_payment;
  }

  ui->label_dolg->setText(QString::number(total_payment, 'f', 2));
  ui->label_proc->setText(QString::number(total_interest, 'f', 2));

  ui->tableWidget->resizeColumnsToContents();
}

Result_credit::~Result_credit() { delete ui; }
