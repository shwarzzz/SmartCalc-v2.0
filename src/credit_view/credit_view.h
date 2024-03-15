#ifndef CREDIT_VIEW_H_
#define CREDIT_VIEW_H_

#include <QWidget>

#include "../credit_controller/credit_controller.h"
namespace Ui {
class CreditView;
}

class CreditView : public QWidget {
  Q_OBJECT

 public:
  CreditView(s21::CreditController* c, QWidget* parent = nullptr);
  ~CreditView();

 private slots:
  void ProcessCalcButtonClick();
  void ProcessShowTableButtonClick();
  void ProcessClearButtonClick();

 private:
  void SetEventHandler();
  Ui::CreditView* ui_;
  s21::CreditController* controller_;
};
#endif  // CreditView_H
