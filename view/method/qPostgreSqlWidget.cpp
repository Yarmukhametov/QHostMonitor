#include "qPostgreSqlWidget.h"
#include "ui_qPostgreSqlWidget.h"
#include "method/tPostgreSql.h"

namespace SDPO {

/*****************************************************************/

PostgreSqlWidget::PostgreSqlWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::PostgreSqlWidget)
{
    ui->setupUi(this);
    connect(ui->cmbServer, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbDatabase, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

PostgreSqlWidget::~PostgreSqlWidget()
{
    delete ui;
}

/*****************************************************************/

void PostgreSqlWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Postgre) ) {
        reset();
        return;
    }
    TPostgreSql* test = qobject_cast<TPostgreSql*>(item);
    ui->cmbServer->setCurrentText(test->getHost());
    ui->spinPort->setValue(test->getPort());
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
}

/*****************************************************************/

TTestMethod *PostgreSqlWidget::save(TTestMethod *item)
{
    TPostgreSql* test;
    if (item && (item->getTMethodID() == TMethodID::Postgre)) {
        test = qobject_cast<TPostgreSql*>(item);
    } else {
        test = new TPostgreSql();
    }
    test->setHost(ui->cmbServer->currentText());
    test->setPort(ui->spinPort->value());
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());

    return test;
}

/*****************************************************************/

void PostgreSqlWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Postgre);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinPort->setValue(POSTGRESQL_DEFAULT_PORT);
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
}

/*****************************************************************/

QStringList PostgreSqlWidget::validate()
{
    QStringList errors;
    if(ui->cmbServer->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Server"));
    }
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Database"));
    }
    return errors;
}

/*****************************************************************/

QString PostgreSqlWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Postgre);
    case Macro::TestMethod : return TMethod::toName(TMethodID::Postgre);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/*****************************************************************/

} // namespace SDPO {
