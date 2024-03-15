#ifndef CALC_CONTROLLER_H_

#define CALC_CONTROLLER_H_

#include "../calc_model/calc_model.h"

namespace s21 {
class CalcController {
 public:
  CalcController() = delete;
  CalcController(CalcModel* model) : model_(model) {}

  void CalculateGraphDots(double x_begin, double x_end, double y_begin,
                          double y_end);
  void Calculate();
  void Reset();

  void SetInputString(const std::string& str);
  void SetXValue(double x);

  const std::vector<double>& GetXDots();
  const std::vector<double>& GetYDots();
  const std::string& GetPlotStatusString();
  const std::string& GetResultString();

  bool IsGraphDataCorrect();

 private:
  CalcModel* model_;
};
}  // namespace s21

#endif
