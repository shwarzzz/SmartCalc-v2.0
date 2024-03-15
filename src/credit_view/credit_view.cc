#include "credit_view.h"

#include "ui_credit_view.h"

CreditView::CreditView(s21::CreditController *c, QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreditView), controller_(c) {
  ui_->setupUi(this);
  SetEventHandler();
  ui_->table_PaymentSchedule->setColumnCount(5);
  ui_->table_PaymentSchedule->setVisible(false);
}

CreditView::~CreditView() {
  ui_->table_PaymentSchedule->clearContents();
  ui_->table_PaymentSchedule->clear();
  delete ui_;
};

void CreditView::ProcessCalcButtonClick() {
  controller_->SetData(ui_->spinBox_month->value(),
                       ui_->doubleSpinBox_percent->value(),
                       ui_->doubleSpinBox_sum->value());
  controller_->SetType(ui_->radioButton_an->isChecked(),
                       ui_->radioButton_dif->isChecked());
  controller_->Calculate();
  ui_->plainTextEdit_result->setPlainText(
      QString::fromStdString(controller_->GetResultString()));
}

void CreditView::ProcessShowTableButtonClick() {
  ui_->table_PaymentSchedule->clearContents();
  ui_->table_PaymentSchedule->clear();
  ui_->table_PaymentSchedule->setHorizontalHeaderLabels(QStringList()
                                                        << "Остаток долга:"
                                                        << "Платёж:"
                                                        << "Проценты:"
                                                        << "Долг:"
                                                        << "Конец периода:");
  ui_->table_PaymentSchedule->setRowCount(controller_->GetMonthCount());
  std::vector<double> data = controller_->GetTableData();
  for (size_t i = 0; i < data.size(); ++i) {
    QTableWidgetItem *item =
        new QTableWidgetItem(QString::number(data[i], 'f', 2));
    ui_->table_PaymentSchedule->setItem(i / COLUMNS_COUNT, i % COLUMNS_COUNT,
                                        item);
  }
  ui_->table_PaymentSchedule->setVisible(true);
}

void CreditView::ProcessClearButtonClick() {
  ui_->table_PaymentSchedule->clearContents();
  ui_->table_PaymentSchedule->clear();
  ui_->table_PaymentSchedule->setVisible(false);
  ui_->spinBox_month->setValue(0);
  ui_->doubleSpinBox_percent->setValue(0);
  ui_->doubleSpinBox_sum->setValue(0);
  ui_->plainTextEdit_result->clear();
  controller_->ClearData();
}

void CreditView::SetEventHandler() {
  connect(ui_->pushButton_calc, SIGNAL(clicked()), this,
          SLOT(ProcessCalcButtonClick()));
  connect(ui_->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(ProcessClearButtonClick()));
  connect(ui_->pushButton_show_graph, SIGNAL(clicked()), this,
          SLOT(ProcessShowTableButtonClick()));
}
