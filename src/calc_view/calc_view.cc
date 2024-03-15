#include "calc_view.h"

#include <QVector>

#include "ui_calc_view.h"

CalcView::CalcView(s21::CalcController* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::CalcView), controller_(controller) {
  ui_->setupUi(this);
  credit_model_ = new s21::CreditModel();
  credit_controller_ = new s21::CreditController(credit_model_);
  credit_calc_view_ = new CreditView(credit_controller_);
  SetEventHandler();
}

CalcView::~CalcView() {
  delete ui_;
  delete credit_model_;
  delete credit_controller_;
  delete credit_calc_view_;
}

void CalcView::SetEventHandler() {
  connect(ui_->pushButton_n_0, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_1, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_2, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_3, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_4, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_5, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_6, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_7, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_8, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_n_9, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_e, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));

  connect(ui_->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));

  connect(ui_->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(AddSymbolToLineEdit()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this,
          SLOT(ProcessDivButtonClick()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(ProcessModButtonClick()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(ProcessMultButtonClick()));

  connect(ui_->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(AddFunctionToLineEdit()));

  connect(ui_->pushButton_clean, SIGNAL(clicked()), this,
          SLOT(ProcessCleanButtonClick()));
  connect(ui_->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(ProcessCalculateButtonClick()));
  connect(ui_->pushButton_plot, SIGNAL(clicked()), this,
          SLOT(ProcessPlotButtonClick()));
  connect(ui_->pushButton_openCreditCalc, SIGNAL(clicked()), this,
          SLOT(ProcessOpenCreditCalcButtonClick()));
}

void CalcView::ProcessCalculateButtonClick() {
  controller_->SetInputString(ui_->lineEdit->text().toStdString());
  controller_->SetXValue(ui_->doubleSpinBox_xvalue->value());
  controller_->Calculate();
  ui_->lineEdit->setText(
      QString::fromStdString(controller_->GetResultString()));
}

void CalcView::AddSymbolToLineEdit() {
  QPushButton* current_button = (QPushButton*)sender();
  ui_->lineEdit->setText(ui_->lineEdit->text() + current_button->text());
}

void CalcView::AddFunctionToLineEdit() {
  QPushButton* current_button = (QPushButton*)sender();
  ui_->lineEdit->setText(ui_->lineEdit->text() + current_button->text() + "(");
}

void ::CalcView::ProcessCleanButtonClick() {
  ui_->lineEdit->clear();
  controller_->Reset();
}

void ::CalcView::ProcessDivButtonClick() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "/");
}

void ::CalcView::ProcessMultButtonClick() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "*");
}

void CalcView::ProcessModButtonClick() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "mod");
}

void CalcView::ProcessPlotButtonClick() {
  double x_begin = ui_->doubleSpinBox_xbegin->value();
  double x_end = ui_->doubleSpinBox_xend->value();

  double y_begin = ui_->doubleSpinBox_ybegin->value();
  double y_end = ui_->doubleSpinBox_yend->value();

  controller_->SetInputString(ui_->lineEdit->text().toStdString());
  controller_->CalculateGraphDots(x_begin, x_end, y_begin, y_end);
  QString plot_status =
      QString::fromStdString(controller_->GetPlotStatusString());

  QVector<double> x = QVector<double>(controller_->GetXDots().begin(),
                                      controller_->GetXDots().end());
  QVector<double> y = QVector<double>(controller_->GetYDots().begin(),
                                      controller_->GetYDots().end());

  ui_->s21_graph->clearGraphs();
  if (controller_->IsGraphDataCorrect()) {
    ui_->s21_graph->xAxis->setRange(x_begin, x_end);
    ui_->s21_graph->yAxis->setRange(y_begin, y_end);
    ui_->s21_graph->addGraph();
    ui_->s21_graph->graph(0)->addData(x, y);
  }
  ui_->s21_graph->replot();
  ui_->labelPlotStatus->setText(plot_status);
}

void CalcView::ProcessOpenCreditCalcButtonClick() { credit_calc_view_->show(); }
