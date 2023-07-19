#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

#include "result_deposit.h"

namespace Ui {
class Deposit;
}

class Deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_pushButton_calc_deposit_clicked();

 private:
  Ui::Deposit *ui;
  Result_deposit *deposit_calc;
};

#endif  // DEPOSIT_H
