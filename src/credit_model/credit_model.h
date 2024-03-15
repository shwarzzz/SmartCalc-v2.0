#ifndef CREDIT_MODEL_H_
#define CREDIT_MODEL_H_

#include <cmath>
#include <string>
#include <vector>

#define COLUMNS_COUNT 5

namespace s21 {

enum PaymentType { kNotSelected = 0, kAnnuity = 1, kDifferentiated = 2 };

class CreditModel {
 public:
  CreditModel();
  ~CreditModel() = default;

  void CheckEnteredValues();
  void CheckPaymentType(bool is_annuity, bool is_differentiated);

  void Calculate();
  void ResetData();

  void SetMonthCount(int count);
  void SetPercent(double percent);
  void SetSum(double sum);

  int GetMonthCount();
  const std::string& GetResultString();
  const std::vector<double>& GetTableData();

 private:
  void CalculateAnnuityPay();
  void CalculateDifferentiatedPay();

  int month_;
  double percent_;
  double sum_;
  bool is_data_correct_;
  bool is_calculated_;
  PaymentType type_;
  std::string result_;
  std::vector<double> table_data_;
};
}  // namespace s21

#endif