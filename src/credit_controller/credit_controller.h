#ifndef CREDIT_CONTROLLER_H_

#define CREDIT_CONTROLLER_H_

#include "../credit_model/credit_model.h"

namespace s21 {
class CreditController {
 public:
  CreditController() = delete;
  CreditController(CreditModel* m) : model_(m) {}

  ~CreditController() = default;

  void SetData(int month, double percent, double sum);
  void SetType(bool is_annuity, bool is_differentiated);
  const std::string& GetResultString();
  int GetMonthCount();
  const std::vector<double>& GetTableData();

  void Calculate();
  void ClearData();

 private:
  CreditModel* model_;
};
}  // namespace s21

#endif