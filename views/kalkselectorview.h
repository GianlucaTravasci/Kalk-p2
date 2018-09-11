#ifndef KALKSELECTORVIEW_H
#define KALKSELECTORVIEW_H

#include <QMainWindow>
#include "views/view.h"
#include "application.h"

namespace Ui {
class KalkSelectorView;
}

class KalkSelectorView : public QMainWindow, public View
{
    Q_OBJECT

public:
    explicit KalkSelectorView(QWidget *parent = 0);
    ~KalkSelectorView();

    void handle() override;

private:
    Ui::KalkSelectorView *ui;

private slots:
    void slotOpenComplex();
    void slotOpenQuaternion();
    void slotOpenAudio();
    void slotOpenColoredWave();

signals:
    void signalBack();
    void signalOpenKalk(int);
};

#endif // KALKSELECTORVIEW_H
