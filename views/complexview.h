#ifndef COMPLEXVIEW_H
#define COMPLEXVIEW_H

#include <QWidget>
#include <QString>
#include "views/view.h"
#include "logica/complex.h"
#include "views/utils/tastierinoview.h"
#include <QRegExpValidator>

namespace Ui {
class ComplexView;
}

class ComplexView : public QWidget, public View
{
    Q_OBJECT

public:
    explicit ComplexView(QWidget *parent = 0);
    ~ComplexView();

    virtual void initialize();
    void handle();

protected:
    void errorManager(QString);
    Complex* op1;
    Complex* op2;
    Complex* op3;
    TastierinoView::configurabile confFor;
    QRegExpValidator validator;
    QString placeholder;

private:
    Ui::ComplexView *ui;

    enum tipiCalcolo {
        sum, sub, mult, div
    };
    int operationStep;
    tipiCalcolo operation;

    void logAppend(QString);
    void logReset();

    void manageKeys();
    void setEnabledKey(QWidget*, bool);

    void calcola();

public slots:
    void slotCalculate();
    void slotEditCurrent();
    void slotKeyPressed(QString);

signals:
    void signalBack();
};

#endif // COMPLEXVIEW_H
