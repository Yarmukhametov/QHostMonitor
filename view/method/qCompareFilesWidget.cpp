#include "qCompareFilesWidget.h"
#include "ui_qCompareFilesWidget.h"
#include "mSettings.h"
#include "global/tMethod.h"
#include "method/tCompareFiles.h"
#include <QFileDialog>

namespace SDPO {

/*****************************************************************/

CompareFilesWidget::CompareFilesWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::CompareFilesWidget)
{
    ui->setupUi(this);
    connect(ui->editFirstFile, SIGNAL(textEdited(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->editSecondFile, SIGNAL(textEdited(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbAlert, SIGNAL(currentIndexChanged(int)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

CompareFilesWidget::~CompareFilesWidget()
{
    delete ui;
}

/*****************************************************************/

void CompareFilesWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::FileCompare) ) {
        reset();
        return;
    }
    TCompareFiles* test = qobject_cast<TCompareFiles*>(item);
    ui->cmbAlert->setCurrentIndex(test->getAlertWhen());
    ui->editFirstFile->setText(test->getFirstFile());
    ui->chkFirstFile->setChecked(test->isTranslateFirstMacros());
    ui->editSecondFile->setText(test->getSecondFile());
    ui->chkSecondFile->setChecked(test->isTranslateSecondMacros());
    ui->cmbString->setCurrentText(test->getString());
    ui->cmbStringCoding->setCurrentText(test->getStringCoding());
    ui->chkCompareTime->setChecked(test->isTime());
    ui->chkCompareSize->setChecked(test->isSize());
    ui->chkCompareContents->setChecked(test->isContents());
    ui->chkCaseSensitive->setChecked(test->isCaseSensitive());
    ui->chkWholeWords->setChecked(test->isWholeWordsOnly());
}

/*****************************************************************/

TTestMethod *CompareFilesWidget::save(TTestMethod *item)
{
    TCompareFiles* test;
    if (item && (item->getTMethodID() == TMethodID::FileCompare)) {
        test = qobject_cast<TCompareFiles*>(item);
    } else {
        test = new TCompareFiles();
    }
    test->setAlertWhen(ui->cmbAlert->currentIndex());
    test->setFirstFile(ui->editFirstFile->text());
    test->setTranslateFirstMacros(ui->chkFirstFile->isChecked());
    test->setSecondFile(ui->editSecondFile->text());
    test->setTranslateSecondMacros(ui->chkSecondFile->isChecked());
    test->setString(ui->cmbString->currentText());
    test->setStringCoding(ui->cmbStringCoding->currentText());
    test->setTime(ui->chkCompareTime->isChecked());
    test->setSize(ui->chkCompareSize->isChecked());
    test->setContents(ui->chkCompareContents->isChecked());
    test->setCaseSensitive(ui->chkCaseSensitive->isChecked());
    test->setWholeWordsOnly(ui->chkWholeWords->isChecked());
    return test;
}

/******************************************************************/

void CompareFilesWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::FileCompare);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbAlert->setCurrentIndex(0);
    on_selectAlert();
    connect(ui->cmbAlert, SIGNAL(currentIndexChanged(int)), this, SLOT(on_selectAlert()));
    ui->editFirstFile->clear();
    ui->chkFirstFile->setChecked(false);
    ui->editSecondFile->clear();
    ui->chkSecondFile->setChecked(false);
    ui->chkCompareTime->setChecked(false);
    ui->chkCompareSize->setChecked(false);
    ui->chkCompareContents->setChecked(false);
}

/******************************************************************/

QStringList CompareFilesWidget::validate()
{
    QStringList errors;
    int CurrentAlertIndex = ui->cmbAlert->currentIndex();
    if(ui->editFirstFile->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a name for the 1st file"));
    }
    if(ui->editSecondFile->text().trimmed().isEmpty() && CurrentAlertIndex <= 3) {
        errors.append(tr("Please, specify a name for the 2nd file"));
    }
    if(ui->cmbString->currentText().trimmed().isEmpty() && CurrentAlertIndex > 3) {
        errors.append(tr("Please, provide a string to look up"));
    }
    if(ui->chkCompareTime->isChecked()?0:1 && ui->chkCompareSize->isChecked()?0:1 && ui->chkCompareContents->isChecked()?0:1 && CurrentAlertIndex < 2)
    {
        errors.append(tr("Please, select one or more comparsion methods"));
    }
    return errors;
}

/******************************************************************/

QString CompareFilesWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Script);
    case Macro::TestMethod : return TMethod::toName(TMethodID::Script);
    case Macro::Object : return ui->editFirstFile->text();
    case Macro::Object2 : return ui->editSecondFile->text();
    case Macro::TestMode : return ui->cmbAlert->currentText();
    default: return QString();
    }
}

/*****************************************************************/

void CompareFilesWidget::on_selectAlert()
{
    int AlertIndex = ui->cmbAlert->currentIndex();
    if (AlertIndex == 0 || AlertIndex == 1)
    {
        ui->stackFileStringSelect->setCurrentIndex(0);
        ui->stackFileStringCompare->setCurrentIndex(0);
        ui->stackStringCodingSelect->setCurrentIndex(0);
        ui->stackFileStringCompare->setEnabled(true);
        ui->lblFirstFile->setText(QString("1st file"));
        ui->lblSecondFile->setText(QString("2nd file"));
    }
    else if (AlertIndex == 2 || AlertIndex == 3)
    {
        ui->stackFileStringSelect->setCurrentIndex(0);
        ui->stackFileStringCompare->setCurrentIndex(0);
        ui->stackStringCodingSelect->setCurrentIndex(0);
        ui->stackFileStringCompare->setDisabled(true);
        ui->lblFirstFile->setText(QString("1st file"));
        ui->lblSecondFile->setText(QString("2nd file"));
    }
    else if (AlertIndex == 4 || AlertIndex == 5)
    {
        ui->stackFileStringSelect->setCurrentIndex(1);
        ui->stackFileStringCompare->setCurrentIndex(1);
        ui->stackStringCodingSelect->setCurrentIndex(1);
        ui->stackFileStringCompare->setEnabled(true);
        ui->lblFirstFile->setText(QString("file"));
        ui->lblSecondFile->setText(QString("string"));
    }
}

/******************************************************************/

void CompareFilesWidget::on_btnFirstFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editFirstFile->text());
    if (!fileName.isEmpty()) {
        ui->editFirstFile->setText(fileName);
    }
}

/******************************************************************/

void CompareFilesWidget::on_btnSecondFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editSecondFile->text());
    if (!fileName.isEmpty()) {
        ui->editSecondFile->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO
