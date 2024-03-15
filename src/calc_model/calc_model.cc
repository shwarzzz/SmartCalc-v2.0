#include "calc_model.h"

s21::CalcModel::CalcModel() {
  is_calculated_ = false;
  is_converted_ = false;
  is_parsed_ = false;

  is_plot_error_ = false;

  x_dots_.reserve(DOTS_COUNT);
  y_dots_.reserve(DOTS_COUNT);
}

void s21::CalcModel::ParseString() {
  converted_input_ = parser_.ParseString(input_);
  is_parsed_ = true;
}

void s21::CalcModel::ConvertStringToPolish() {
  if (!is_parsed_) {
    ParseString();
  }
  converted_input_ = converter_.ConvertToPolish(converted_input_);
  is_converted_ = true;
}

void s21::CalcModel::Calculate() {
  try {
    if (!is_converted_) {
      ConvertStringToPolish();
    }
    if (!is_calculated_) {
      result_ = calculator_.PerformCalculation(converted_input_, x_);
      is_calculated_ = true;
      setlocale(LC_NUMERIC, "C");
      char buffer[100] = "";
      std::sprintf(buffer, "%.7f", result_);
      result_string_ = buffer;
    }
  } catch (std::exception& e) {
    result_string_ = e.what();
    is_calculated_ = false;
  }
}

void s21::CalcModel::Reset() {
  is_parsed_ = false;
  is_converted_ = false;
  is_calculated_ = false;
  is_plot_error_ = false;

  input_.clear();
  result_string_.clear();
  plot_status_.clear();

  x_dots_.clear();
  y_dots_.clear();

  while (!converted_input_.empty()) {
    converted_input_.pop();
  }
  result_ = 0;
}

void s21::CalcModel::FindDotsToPlot(double x_begin, double x_end,
                                    double y_begin, double y_end) {
  if (x_begin >= x_end || y_begin >= y_end) {
    plot_status_ = "Error: Incorrect x or y values!";
  } else {
    if (!is_converted_) {
      try {
        ConvertStringToPolish();
      } catch (s21::InputError& e) {
        plot_status_ = e.what();
        return;
      }
    }
    x_dots_.clear();
    y_dots_.clear();
    is_plot_error_ = false;
    double step = (x_end - x_begin) / DOTS_COUNT;
    double x_value = x_begin;
    for (size_t i = 0; i < DOTS_COUNT; ++i, x_value += step) {
      try {
        y_dots_.push_back(
            calculator_.PerformCalculation(converted_input_, x_value));
        x_dots_.push_back(x_value);
      } catch (std::exception& e) {
        is_plot_error_ = true;
        plot_status_ = e.what();
        x_dots_.clear();
        y_dots_.clear();
        return;
      }
    }
    plot_status_ = "Success!";
  }
}

bool s21::CalcModel::IsGraphDataCorrect() { return is_plot_error_ == false; }

void s21::CalcModel::SetInputString(const std::string& str) {
  if (str != input_) {
    input_ = str;
    is_parsed_ = false;
    is_converted_ = false;
    is_calculated_ = false;
  }
}

void s21::CalcModel::SetX(double value) { x_ = value; }

const std::string& s21::CalcModel::GetResultString() { return result_string_; }

const std::string& s21::CalcModel::GetPlotStatusString() {
  return plot_status_;
}

const std::vector<double>& s21::CalcModel::GetXDotsVector() { return x_dots_; }
const std::vector<double>& s21::CalcModel::GetYDotsVector() { return y_dots_; }

std::stack<s21::Data> s21::CalcModel::GetConvertedString() {
  return converted_input_;
}

double s21::CalcModel::GetResultOfCalculation() { return result_; }
