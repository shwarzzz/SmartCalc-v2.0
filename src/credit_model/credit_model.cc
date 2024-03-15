#include "credit_model.h"

s21::CreditModel::CreditModel() { ResetData(); }

void s21::CreditModel::ResetData() {
  month_ = 0;
  percent_ = 0;
  sum_ = 0;
  is_data_correct_ = false;
  is_calculated_ = false;
  type_ = kNotSelected;
  result_ = "";
}

void s21::CreditModel::CheckEnteredValues() {
  if (percent_ == 0 || month_ == 0 || sum_ == 0) {
    is_data_correct_ = false;
  } else {
    is_data_correct_ = true;
  }
}

void s21::CreditModel::SetMonthCount(int count) {
  if (month_ != count) {
    month_ = count;
    is_calculated_ = false;
  }
}

void s21::CreditModel::SetPercent(double percent) {
  if (percent_ != percent) {
    percent_ = percent;
    is_calculated_ = false;
  }
}

void s21::CreditModel::SetSum(double sum) {
  if (sum_ != sum) {
    sum_ = sum;
    is_calculated_ = false;
  }
}

int s21::CreditModel::GetMonthCount() { return month_; }

const std::string& s21::CreditModel::GetResultString() { return result_; }

const std::vector<double>& s21::CreditModel::GetTableData() {
  return table_data_;
}

void s21::CreditModel::CheckPaymentType(bool is_annuity,
                                        bool is_differentiated) {
  if (is_annuity) {
    if (type_ != kAnnuity) {
      type_ = kAnnuity;
      is_calculated_ = false;
    }
  } else if (is_differentiated) {
    if (type_ != kDifferentiated) {
      type_ = kDifferentiated;
      is_calculated_ = false;
    }
  } else {
    type_ = kNotSelected;
  }
}

void s21::CreditModel::Calculate() {
  if (type_ != kNotSelected) {
    if (is_data_correct_) {
      if (!is_calculated_) {
        table_data_.reserve(COLUMNS_COUNT * month_);
        table_data_.clear();
        if (type_ == kAnnuity) {
          CalculateAnnuityPay();
        } else {
          CalculateDifferentiatedPay();
        }
        is_calculated_ = true;
      }
    } else {
      result_ = "Ошибка: Значения всех полей должно быть > 0!";
    }
  } else {
    result_ = "Ошибка: Выберите тип платежа!";
  }
}

void s21::CreditModel::CalculateAnnuityPay() {
  double month_percent = (percent_ / 100.0) / 12.0;
  double sum = sum_;
  double month_payment =
      sum *
      (month_percent + month_percent / (pow(1 + month_percent, month_) - 1));
  month_payment = round(month_payment * 100) / 100;
  for (int i = 1; i <= month_; ++i) {
    double percent_rest = round(sum * month_percent * 100) / 100;
    double debt = round((month_payment - percent_rest) * 100) / 100;
    double sum_rest = sum - debt;
    table_data_.push_back(sum);
    table_data_.push_back(month_payment);
    table_data_.push_back(percent_rest);
    table_data_.push_back(debt);
    table_data_.push_back(sum_rest);
    sum = sum_rest;
  }
  double total_sum = floor(month_payment * month_ * 100) / 100;
  char total_str[5000] = "";
  std::sprintf(
      total_str,
      "Итог:\nЕжемесячный платеж: %.2lf руб.\nОбщая сумма выплат: %.2lf "
      "руб.\nНачисленные проценты: %.2lf руб.",
      month_payment, total_sum, total_sum - sum_);
  result_ = total_str;
}

void s21::CreditModel::CalculateDifferentiatedPay() {
  double sum = sum_;
  double month_percent = (percent_ / 100.0) / 12.0;
  double month_payment = 0;
  double max_payment = 0;
  double min_payment = 0;
  double total_sum = 0;
  double month_pay_debt = sum / month_;
  for (int i = 1; i <= month_; ++i) {
    double percent_rest = round(sum * month_percent * 100) / 100;
    month_payment = month_pay_debt + percent_rest;
    month_payment = round(month_payment * 100) / 100;
    if (i == 1) {
      max_payment = month_payment;
    } else if (i == month_) {
      min_payment = month_payment;
    }
    double sum_rest = sum - month_pay_debt;
    total_sum += month_payment;
    table_data_.push_back(sum);
    table_data_.push_back(month_payment);
    table_data_.push_back(percent_rest);
    table_data_.push_back(month_pay_debt);
    table_data_.push_back(sum_rest);
    sum = sum_rest;
  }
  char total_str[5000] = "";
  std::sprintf(total_str,
               "Итог:\nЕжемесячный платеж: %.2lf руб., .., %.2lf руб.\nОбщая "
               "сумма выплат: %.2lf руб.\nНачисленные проценты: %.2lf руб.",
               max_payment, min_payment, total_sum, total_sum - sum_);
  result_ = total_str;
}
