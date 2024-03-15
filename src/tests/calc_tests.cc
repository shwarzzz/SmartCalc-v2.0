#include <gtest/gtest.h>

#include "../calc_model/calc_model.h"

TEST(TestModelCalculation, Test_1) {
  s21::CalcModel m;
  std::string input = "cos(12)/sqrt(9)-atan(x)*(-sin(-x))+23*ln(5.23)^2";
  s21::Data data[20];
  data[0] = s21::Data(0, 1, s21::kBinaryPlus);
  data[1] = s21::Data(0, 2, s21::kMult);
  data[2] = s21::Data(0, 3, s21::kPow);
  data[3] = s21::Data(2, 0, s21::kNumber);
  data[4] = s21::Data(0, 4, s21::kLn);
  data[5] = s21::Data(5.23, 0, s21::kNumber);
  data[6] = s21::Data(23, 0, s21::kNumber);
  data[7] = s21::Data(0, 1, s21::kBinaryMinus);
  data[8] = s21::Data(0, 2, s21::kMult);
  data[9] = s21::Data(0, 1, s21::kUnaryMinus);
  data[10] = s21::Data(0, 4, s21::kSin);
  data[11] = s21::Data(0, 1, s21::kUnaryMinus);
  data[12] = s21::Data(0, 0, s21::kX);
  data[13] = s21::Data(0, 4, s21::kAtan);
  data[14] = s21::Data(0, 0, s21::kX);
  data[15] = s21::Data(0, 2, s21::kDiv);
  data[16] = s21::Data(0, 4, s21::kSqrt);
  data[17] = s21::Data(9, 0, s21::kNumber);
  data[18] = s21::Data(0, 4, s21::kCos);
  data[19] = s21::Data(12, 0, s21::kNumber);

  m.SetInputString(input);
  m.SetX(3.15);
  m.Calculate();

  std::stack<s21::Data> my_convert = m.GetConvertedString();
  double res = m.GetResultOfCalculation();
  ASSERT_NEAR(res, 63.2446699, 1e-7);
  for (int i = 19; i >= 0; --i) {
    ASSERT_TRUE(data[i] == my_convert.top());
    my_convert.pop();
  }
}

TEST(TestModelCalculation, Test_2) {
  s21::CalcModel m;
  std::string input = "-xmod2*6.35";

  m.SetInputString(input);
  m.SetX(103.9898);
  m.Calculate();

  double res = m.GetResultOfCalculation();
  ASSERT_NEAR(res, -12.63523, 1e-7);
}

TEST(TestModelCalculation, Test_3) {
  s21::CalcModel m;
  std::string input = "1.02355667653";

  m.SetInputString(input);
  m.SetX(103.9898);
  m.Calculate();

  double res = m.GetResultOfCalculation();

  ASSERT_NEAR(res, 1.02355667653, 1e-7);
}

TEST(TestModelCalculation, Test_4) {
  s21::CalcModel m;
  std::string input = "tan(asin(acos(0.98)))+log(2)+ln(0.5)";
  s21::Data data[10];
  data[0] = s21::Data(0.98, 0, s21::kNumber);
  data[1] = s21::Data(0, 4, s21::kAcos);
  data[2] = s21::Data(0, 4, s21::kAsin);
  data[3] = s21::Data(0, 4, s21::kTan);
  data[4] = s21::Data(2, 0, s21::kNumber);
  data[5] = s21::Data(0, 4, s21::kLog);
  data[6] = s21::Data(0, 1, s21::kBinaryPlus);
  data[7] = s21::Data(0.5, 0, s21::kNumber);
  data[8] = s21::Data(0, 4, s21::kLn);
  data[9] = s21::Data(0, 1, s21::kBinaryPlus);

  m.SetInputString(input);
  m.SetX(103.9898);
  m.Calculate();

  std::stack<s21::Data> my_convert = m.GetConvertedString();
  ASSERT_NEAR(m.GetResultOfCalculation(), -0.1876370, 1e-7);
  for (size_t i = 0; i < 10; ++i) {
    ASSERT_TRUE(data[i] == my_convert.top());
    my_convert.pop();
  }
}

TEST(TestModelCalculation, Test_5) {
  s21::CalcModel m;
  std::string input = "+2+6";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), 8, 1e-7);
}

TEST(TestModelCalculation, Test_6) {
  s21::CalcModel m;
  std::string input = "0.0003e+6";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), 300, 1e-7);
}

TEST(TestModelCalculation, Test_7) {
  s21::CalcModel m;
  std::string input = "300e-2+50*2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), 103, 1e-7);
}

TEST(TestModelCalculation, Test_8) {
  s21::CalcModel m;
  std::string input = "30e+0/2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), 15, 1e-7);
}

TEST(TestModelCalculation, Test_9) {
  s21::CalcModel m;
  std::string input = "-sqrt(0.16e+2)/2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), -2, 1e-7);
}

TEST(TestModelCalculation, Test_10) {
  s21::CalcModel m;
  std::string input = "-0e+2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_NEAR(m.GetResultOfCalculation(), 0, 1e-7);
}

TEST(TestModelCalculationError, Test_1) {
  s21::CalcModel m;
  std::string input = "x/0";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Div by zero!");
}

TEST(TestModelCalculationError, Test_2) {
  s21::CalcModel m;
  std::string input = "log(0)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Calculation error!");
}

TEST(TestModelCalculationError, Test_3) {
  s21::CalcModel m;
  std::string input = "2+asin(1.01)*2.53";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Calculation error!");
}

TEST(TestModelCalculationError, Test_4) {
  s21::CalcModel m;
  std::string input = "-acos(1.0001)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Calculation error!");
}

TEST(TestModelCalculationError, Test_5) {
  s21::CalcModel m;
  std::string input = "+1modsqrt(-0.5)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Calculation error!");
}

TEST(TestModelCalculationError, Test_6) {
  s21::CalcModel m;
  std::string input = "ln(0)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Calculation error!");
}

TEST(TestModelCalculationError, Test_7) {
  s21::CalcModel m;
  std::string input = "1mod0";
  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Div by zero!");
}

TEST(TestModelInputError, Test_1) {
  s21::CalcModel m;
  std::string input = "1.023.55667653";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_2) {
  s21::CalcModel m;
  std::string input = "00102355667653";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_3) {
  s21::CalcModel m;
  std::string input = "sin(2)xx";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_4) {
  s21::CalcModel m;
  std::string input = "sik(2)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_5) {
  s21::CalcModel m;
  std::string input = "1mob2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_6) {
  s21::CalcModel m;
  std::string input = "sin(";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_7) {
  s21::CalcModel m;
  std::string input = "sin()";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_8) {
  s21::CalcModel m;
  std::string input = "p";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_9) {
  s21::CalcModel m;
  std::string input = "123.55+x1";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_10) {
  s21::CalcModel m;
  std::string input = "123.55*(x+3)+abin(4)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_11) {
  s21::CalcModel m;
  std::string input = "123.55*(x+3)+li(4)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_12) {
  s21::CalcModel m;
  std::string input = "1(2+3)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_13) {
  s21::CalcModel m;
  std::string input = ")";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_14) {
  s21::CalcModel m;
  std::string input = "1+2)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_15) {
  s21::CalcModel m;
  std::string input = "mod2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_16) {
  s21::CalcModel m;
  std::string input = "3mod^(2x)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_17) {
  s21::CalcModel m;
  std::string input = "+^(2x)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_18) {
  s21::CalcModel m;
  std::string input = "3+^(2x)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_19) {
  s21::CalcModel m;
  std::string input = "55.23/^(2x)";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_20) {
  s21::CalcModel m;
  std::string input = "e+2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_21) {
  s21::CalcModel m;
  std::string input = "1521e2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_22) {
  s21::CalcModel m;
  std::string input = "1e+02";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_23) {
  s21::CalcModel m;
  std::string input = "1e+0.2";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

TEST(TestModelInputError, Test_24) {
  s21::CalcModel m;
  std::string input = "1e+x";

  m.SetInputString(input);
  m.SetX(0);
  m.Calculate();

  ASSERT_EQ(m.GetResultString(), "Error: Wrong input!");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}