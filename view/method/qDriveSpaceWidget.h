#ifndef QDRIVESPACEWIDGET_H
#define QDRIVESPACEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DriveSpaceWidget;
}

namespace SDPO {

class TTestMethod;

class DriveSpaceWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit DriveSpaceWidget(QWidget *parent = 0);
    ~DriveSpaceWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DriveSpaceWidget *ui;
};

} // namespace SDPO

#endif // QDRIVESPACEWIDGET_H
