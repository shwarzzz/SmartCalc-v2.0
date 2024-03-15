#include "converter.h"

std::stack<s21::Data> s21::Converter::ConvertToPolish(stack& input) {
  stack result;
  stack support;
  ReverseStack(input);
  while (!input.empty()) {
    s21::Data elem = input.top();
    if (elem.GetType() == kNumber || elem.GetType() == kX) {
      result.push(elem);
    } else {
      CheckPriority(elem, support, result);
    }
    input.pop();
  }
  MergeStack(result, support);
  ReverseStack(result);
  return result;
}

void s21::Converter::CheckPriority(s21::Data& elem, stack& support,
                                   stack& result) {
  if (support.empty()) {
    support.push(elem);
  } else {
    s21::Data tmp = support.top();
    if (elem.GetType() != kRightBracket) {
      if (elem.GetPriority() <= tmp.GetPriority() &&
          elem.GetType() != kLeftBracket) {
        while (!support.empty() && elem.GetPriority() <= tmp.GetPriority()) {
          result.push(tmp);
          support.pop();
          if (!support.empty()) {
            tmp = support.top();
          }
        }
      }
      support.push(elem);
    } else {
      while (tmp.GetType() != kLeftBracket) {
        result.push(tmp);
        support.pop();
        tmp = support.top();
      }
      support.pop();
    }
  }
}

void s21::Converter::MergeStack(stack& dst, stack& src) {
  while (!src.empty()) {
    Data tmp = src.top();
    dst.push(tmp);
    src.pop();
  }
}

void s21::Converter::ReverseStack(std::stack<s21::Data>& src) {
  std::stack<s21::Data> tmp;
  while (!src.empty()) {
    tmp.push(src.top());
    src.pop();
  }
  src = std::move(tmp);
}