#include "calc_controller.h"

namespace s21 {

void s21::CalcController::SetInputString(const std::string& str) {
  model_->SetInputString(str);
}

void s21::CalcController::SetXValue(double x) { model_->SetX(x); }

void s21::CalcController::Calculate() { model_->Calculate(); }

const std::string& s21::CalcController::GetResultString() {
  return model_->GetResultString();
}

void s21::CalcController::Reset() { model_->Reset(); }

void s21::CalcController::CalculateGraphDots(double x_begin, double x_end,
                                             double y_begin, double y_end) {
  model_->FindDotsToPlot(x_begin, x_end, y_begin, y_end);
}

const std::vector<double>& s21::CalcController::GetXDots() {
  return model_->GetXDotsVector();
}

const std::vector<double>& s21::CalcController::GetYDots() {
  return model_->GetYDotsVector();
}

const std::string& s21::CalcController::GetPlotStatusString() {
  return model_->GetPlotStatusString();
}

bool s21::CalcController::IsGraphDataCorrect() {
  return model_->IsGraphDataCorrect();
}

}  // namespace s21