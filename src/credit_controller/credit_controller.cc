#include "credit_controller.h"

void s21::CreditController::SetData(int month, double percent, double sum) {
  model_->SetMonthCount(month);
  model_->SetPercent(percent);
  model_->SetSum(sum);
}

void s21::CreditController::SetType(bool is_annuity, bool is_differentiated) {
  model_->CheckPaymentType(is_annuity, is_differentiated);
}

void s21::CreditController::Calculate() {
  model_->CheckEnteredValues();
  model_->Calculate();
}

void s21::CreditController::ClearData() { model_->ResetData(); }

int s21::CreditController::GetMonthCount() { return model_->GetMonthCount(); }

const std::vector<double>& s21::CreditController::GetTableData() {
  return model_->GetTableData();
}

const std::string& s21::CreditController::GetResultString() {
  return model_->GetResultString();
}
