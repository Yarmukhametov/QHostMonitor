#include "qUncWidget.h"
#include "ui_qUncWidget.h"

namespace SDPO {

UncWidget::UncWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::UncWidget)
{
    ui->setupUi(this);
}

UncWidget::~UncWidget()
{
    delete ui;
}

} //namespace SDPO
