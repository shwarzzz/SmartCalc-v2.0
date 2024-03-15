#include "calculator.h"

double s21::Calculator::PerformCalculation(
    const std::stack<s21::Data>& converted_input, double x) {
  std::stack<s21::Data> input = converted_input;
  array numb{};
  int index = -1;
  while (!input.empty()) {
    s21::Data elem = input.top();
    if (elem.GetType() == kX || elem.GetType() == kNumber) {
      ++index;
      numb[index] = elem.GetType() != kX ? elem.GetValue() : x;
    } else if (!DoSimpleArithmetic(elem, numb, index)) {
      DoHardArithmetic(elem, numb, index);
    }
    input.pop();
  }
  if (!std::isfinite(numb[index])) {
    throw s21::CalculationError("Error: Calculation error!");
  }
  return numb[index];
}

bool s21::Calculator::DoSimpleArithmetic(s21::Data& elem, array& numb,
                                         int& index) {
  bool is_completed = true;
  if (elem.GetType() == kUnaryPlus) {
    numb[index] *= 1;
  } else if (elem.GetType() == kUnaryMinus) {
    numb[index] *= -1;
  } else {
    if (elem.GetType() == kBinaryPlus) {
      numb[index - 1] += numb[index];
    } else if (elem.GetType() == kBinaryMinus) {
      numb[index - 1] -= numb[index];
    } else if (elem.GetType() == kMult) {
      numb[index - 1] *= numb[index];
    } else if (elem.GetType() == kDiv) {
      if (numb[index] == 0) {
        throw s21::CalculationError("Error: Div by zero!");
      }
      numb[index - 1] /= numb[index];
    } else if (elem.GetType() == kMod) {
      if (numb[index] == 0) {
        throw s21::CalculationError("Error: Div by zero!");
      }
      numb[index - 1] = fmod(numb[index - 1], numb[index]);
    } else if (elem.GetType() == kPow) {
      numb[index - 1] = pow(numb[index - 1], numb[index]);
    } else {
      is_completed = false;
      ++index;
    }
    --index;
  }
  return is_completed;
}

void s21::Calculator::DoHardArithmetic(s21::Data& elem, array& numb,
                                       int& index) {
  if (elem.GetType() == kSin) {
    numb[index] = sin(numb[index]);
  } else if (elem.GetType() == kCos) {
    numb[index] = cos(numb[index]);
  } else if (elem.GetType() == kTan) {
    numb[index] = tan(numb[index]);
  } else if (elem.GetType() == kAsin) {
    if (fabs(numb[index]) <= 1) {
      numb[index] = asin(numb[index]);
    } else {
      throw s21::CalculationError("Error: Calculation error!");
    }
  } else if (elem.GetType() == kAcos) {
    if (fabs(numb[index]) <= 1) {
      numb[index] = acos(numb[index]);
    } else {
      throw s21::CalculationError("Error: Calculation error!");
    }
  } else if (elem.GetType() == kAtan) {
    numb[index] = atan(numb[index]);
  } else if (elem.GetType() == kLog) {
    if (numb[index] > 0) {
      numb[index] = log10(numb[index]);
    } else {
      throw s21::CalculationError("Error: Calculation error!");
    }
  } else if (elem.GetType() == kLn) {
    if (numb[index] > 0) {
      numb[index] = log(numb[index]);
    } else {
      throw s21::CalculationError("Error: Calculation error!");
    }
  } else if (elem.GetType() == kSqrt) {
    if (numb[index] < 0) {
      throw s21::CalculationError("Error: Calculation error!");
    } else {
      numb[index] = sqrt(numb[index]);
    }
  }
}