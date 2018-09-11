#ifndef AUDIOVIEW_H
#define AUDIOVIEW_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include <QMessageBox>
#include "views/view.h"
#include "logica/audio.h"
#include "views/utils/qcustomplot.h"
#include "exce_kalk.h"

namespace Ui {
class AudioView;
}

class AudioView : public QWidget, public View
{
    Q_OBJECT

public:
    explicit AudioView(QWidget *parent = 0);
    ~AudioView();

    void handle() override;

    /**
     * @name updateAllOp
     * @brief Aggiorna la grafica di tutti i grafici della calcolatrice
     */
    void updateAllOp();
    void updateOperatore(QCustomPlot*, Audio*);

private:
    Ui::AudioView *ui;
    Audio* operatoreUno;
    Audio* operatoreDue;
    Audio* operatoreTre;

signals:
    void signalBack();

private slots:

    void slotOpOndaUno();
    //void slotOpOndaUnoEseguita(Audio);

    void slotOpOndaDue();
    //void slotOpOndaDueEseguita(Audio);

    void slotCalcola();
};

#endif // AUDIOVIEW_H
