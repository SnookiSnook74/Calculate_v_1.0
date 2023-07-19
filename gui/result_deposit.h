#ifndef RESULT_DEPOSIT_H
#define RESULT_DEPOSIT_H

#include <QWidget>

#include "credit_calc.h"

namespace Ui {
class Result_deposit;
}

class Result_deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Result_deposit(int term, double sum, depositInfo *info,
                          QWidget *parent = nullptr);
  ~Result_deposit();

 private:
  Ui::Result_deposit *ui;
};

#endif  // RESULT_DEPOSIT_H
