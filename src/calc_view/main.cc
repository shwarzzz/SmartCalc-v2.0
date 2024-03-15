#include <QApplication>

#include "calc_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalcModel model;
  s21::CalcController controller(&model);
  CalcView calculator(&controller);
  calculator.show();
  return a.exec();
}
