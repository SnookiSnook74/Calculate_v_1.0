#ifndef RESULT_CREDIT_H
#define RESULT_CREDIT_H

#include <QWidget>

#include "credit_calc.h"

namespace Ui {
class Result_credit;
}

class Result_credit : public QWidget {
  Q_OBJECT

 public:
  explicit Result_credit(int period, monthInfo* monthRes,
                         QWidget* parent = nullptr);
  ~Result_credit();

 private:
  Ui::Result_credit* ui;
  monthInfo* monthData;
};

#endif  // RESULT_CREDIT_H
