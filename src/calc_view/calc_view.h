#ifndef CALC_VIEW_H_
#define CALC_VIEW_H_

#include <QMainWindow>

#include "../calc_controller/calc_controller.h"
#include "../credit_view/credit_view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(s21::CalcController* controller, QWidget* parent = nullptr);
  ~CalcView();

 private:
  void SetEventHandler();

  Ui::CalcView* ui_;
  s21::CalcController* controller_;

  s21::CreditModel* credit_model_;
  s21::CreditController* credit_controller_;
  CreditView* credit_calc_view_;

 private slots:
  void AddSymbolToLineEdit();
  void AddFunctionToLineEdit();

  void ProcessCalculateButtonClick();
  void ProcessCleanButtonClick();
  void ProcessDivButtonClick();
  void ProcessMultButtonClick();
  void ProcessModButtonClick();
  void ProcessPlotButtonClick();
  void ProcessOpenCreditCalcButtonClick();
};

#endif  // CALC_VIEW_H_
