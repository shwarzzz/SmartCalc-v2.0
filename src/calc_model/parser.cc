#include "parser.h"

std::stack<s21::Data> s21::Parser::ParseString(const std::string& str) {
  std::stack<s21::Data> result;
  for (size_t i = 0; i < str.size(); ++i) {
    if (IsDigit(str[i])) {
      result.push(ConvertNumberToString(str, i));
    } else if (str[i] == 'x') {
      if (i == 0 || (i > 0 && (!IsDigit(str[i - 1]) && str[i - 1] != ')' &&
                               str[i - 1] != 'x'))) {
        s21::Data tmp(0, 0, kX);
        result.push(tmp);
      } else {
        throw s21::InputError("Error: Wrong input!");
      }
    } else {
      s21::Data tmp = CheckAlgebraicSigns(str, i);
      if (tmp.GetType() == kUnknown) {
        if (str[i] == '(' || str[i] == ')') {
          result.push(CheckMatchingBracket(str, i));
        } else {
          tmp = CheckMathLexeme(str, i);
          if (tmp.GetType() == kUnknown) {
            tmp = CheckTrigonometricLexeme(str, i);
            if (tmp.GetType() == kUnknown) {
              if (str[i] != '\0') {
                throw s21::InputError("Error: Wrong input!");
              }
            }
          }
          result.push(tmp);
        }
      } else {
        result.push(tmp);
      }
    }
  }
  return result;
}

s21::Data s21::Parser::ConvertNumberToString(const std::string& str,
                                             size_t& index) {
  if (index > 0 && (str[index - 1] == 'x' || str[index - 1] == ')')) {
    throw s21::InputError("Error: Wrong input!");
  }
  std::string num = CheckNumber(str, index, 1);
  double exp = 0;
  if (str[index] == 'e') {
    ++index;
    int sign = 1;
    if (str[index] == '-') {
      sign = -1;
    } else if (str[index] != '+') {
      throw s21::InputError("Error: Wrong input!");
    }
    ++index;
    if (!IsDigit(str[index])) {
      throw s21::InputError("Error: Wrong input!");
    }
    exp = ConvertStringToDouble(CheckNumber(str, index, 0)) * sign;
  }
  --index;
  double res = ConvertStringToDouble(num);
  res = res * pow(10, exp);
  s21::Data tmp(res, 0, kNumber);
  return tmp;
}

std::string s21::Parser::CheckNumber(const std::string& str, size_t& index,
                                     size_t max_dot_count) {
  std::string num = "";
  size_t dot_count = 0;
  for (;; ++index) {
    if ((IsDigit(str[index]) || str[index] == '.') && str[index] != '\0') {
      num.push_back(str[index]);
      if (str[index] == '.') {
        ++dot_count;
      }
    } else {
      if (!num.empty() &&
          (num[num.size() - 1] == '.' || dot_count > max_dot_count ||
           (num.size() > 1 && num[0] == '0' && num[1] != '.'))) {
        throw s21::InputError("Error: Wrong input!");
      } else {
        break;
      }
    }
  }
  return num;
}

s21::Data s21::Parser::CheckAlgebraicSigns(const std::string& str,
                                           size_t index) {
  s21::Data res;
  if (str[index] == '+' || str[index] == '-') {
    if (index == 0 || (index > 0 && str[index - 1] == '(')) {
      if (IsSymbolCorrect(str[index + 1])) {
        if (str[index] == '+') {
          res.SetPriority(1);
          res.SetType(kUnaryPlus);
        } else {
          res.SetPriority(1);
          res.SetType(kUnaryMinus);
        }
      } else {
        throw s21::InputError("Error: Wrong input!");
      }
    } else if (IsBinaryOperatorsConditions(str, index)) {
      res.SetPriority(1);
      res.SetType(one_char_lexeme.at(str[index]));
    } else {
      throw s21::InputError("Error: Wrong input!");
    }
  } else if (str[index] == '*' || str[index] == '/' || str[index] == '^') {
    if (IsBinaryOperatorsConditions(str, index)) {
      int priority = str[index] == '^' ? 3 : 2;
      res.SetPriority(priority);
      res.SetType(one_char_lexeme.at(str[index]));
    } else {
      throw s21::InputError("Error: Wrong input!");
    }
  }
  return res;
}

s21::Data s21::Parser::CheckMatchingBracket(const std::string& str,
                                            size_t index) {
  int brackets_count = 0;
  s21::Data result(0, -1, one_char_lexeme.at(str[index]));
  if (str[index] == '(') {
    if (index >= 1 && (str[index - 1] == 'x' || IsDigit(str[index - 1]))) {
      throw s21::InputError("Error: Wrong input!");
    }
    ++index;
    for (; str[index] != '\0' && brackets_count != 1; ++index) {
      if (str[index] == '(') {
        --brackets_count;
      } else if (str[index] == ')') {
        ++brackets_count;
        if (str[index - 1] == '(') {
          throw s21::InputError("Error: Wrong input!");
        }
      }
    }
  } else if (str[index] == ')') {
    if (index == 0) {
      throw s21::InputError("Error: Wrong input!");
    }
    --index;
    for (; brackets_count != 1; --index) {
      if (str[index] == ')') {
        --brackets_count;
      } else if (str[index] == '(') {
        ++brackets_count;
        if (str[index + 1] == ')') {
          throw s21::InputError("Error: Wrong input!");
        }
      }
      if (index == 0) {
        break;
      }
    }
  }
  if (brackets_count != 1) {
    throw s21::InputError("Error: Wrong input!");
  }
  return result;
}

s21::Data s21::Parser::CheckMathLexeme(const std::string& str, size_t& index) {
  s21::Data result;
  if (str[index] == 'm') {
    result = CheckModLexeme(str, index);
  } else if (str[index] == 'l') {
    if (str[index + 1] == 'n') {
      result = CheckLexemeEquality(str, index, kLn);
    } else if (str[index + 1] == 'o') {
      result = CheckLexemeEquality(str, index, kLog);
    } else {
      throw s21::InputError("Error: Wrong input!");
    }
  } else if (str[index] == 's' && str[index + 1] != 'i') {
    result = CheckLexemeEquality(str, index, kSqrt);
  }
  return result;
}

s21::Data s21::Parser::CheckTrigonometricLexeme(const std::string& str,
                                                size_t& index) {
  s21::Data result;
  if (str[index] == 'a') {
    if (str[index + 1] == 's') {
      result = CheckLexemeEquality(str, index, kAsin);
    } else if (str[index + 1] == 'c') {
      result = CheckLexemeEquality(str, index, kAcos);
    } else if (str[index + 1] == 't') {
      result = CheckLexemeEquality(str, index, kAtan);
    } else {
      throw s21::InputError("Error: Wrong input!");
    }
  } else if (str[index] == 's' && str[index + 1] != 'q') {
    result = CheckLexemeEquality(str, index, kSin);
  } else if (str[index] == 'c') {
    result = CheckLexemeEquality(str, index, kCos);
  } else if (str[index] == 't') {
    result = CheckLexemeEquality(str, index, kTan);
  }
  return result;
}

s21::Data s21::Parser::CheckLexemeEquality(const std::string& str,
                                           size_t& index, OperationType type) {
  std::string check = function_lexeme.at(type);
  for (size_t i = 0; i < check.size(); ++i, ++index) {
    if (str[index] == '\0' || str[index] != check[i]) {
      throw s21::InputError("Error: Wrong input!");
    }
  }
  s21::Data result(0, 4, type);
  index -= 2;
  return result;
}

s21::Data s21::Parser::CheckModLexeme(const std::string& str, size_t& index) {
  s21::Data result;
  std::string check = function_lexeme.at(kMod);
  if (index > 0 && (str[index - 1] == ')' || str[index - 1] == 'x' ||
                    IsDigit(str[index - 1]))) {
    for (size_t i = 0; i < check.size(); ++i, ++index) {
      if (str[index] != check[i]) {
        throw s21::InputError("Error: Wrong input!");
      }
    }
    if (IsSymbolCorrect(str[index])) {
      result.SetPriority(2);
      result.SetType(kMod);
      --index;
    } else {
      throw s21::InputError("Error: Wrong input!");
    }
  } else {
    throw s21::InputError("Error: Wrong input!");
  }
  return result;
}

double s21::Parser::ConvertStringToDouble(const std::string& str) {
  bool isDot = false;
  double count = 0;
  double res = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '.') {
      isDot = true;
      count = 0;
    } else {
      res = res * 10 + (str[i] - '0');
      ++count;
    }
  }
  if (isDot) {
    res /= pow(10, count);
  }
  return res;
}

bool s21::Parser::IsDigit(char c) { return c >= 48 && c <= 57; }

bool s21::Parser::IsBinaryOperatorsConditions(const std::string& str,
                                              size_t index) {
  return index > 0 &&
         (str[index - 1] == ')' || str[index - 1] == 'x' ||
          IsDigit(str[index - 1])) &&
         IsSymbolCorrect(str[index + 1]);
}

bool s21::Parser::IsSymbolCorrect(char c) {
  bool res = false;
  if (c == '(' || c == 'a' || c == 's' || c == 'c' || c == 't' || c == 'l' ||
      c == 'x' || IsDigit(c)) {
    res = true;
  }
  return res;
}