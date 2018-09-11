#include "audioview.h"
#include "ui_audioview.h"



AudioView::AudioView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioView)
{
    QFile file (":/Resources/Resources/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
    operatoreUno = new Audio();
    operatoreDue = new Audio();
    operatoreTre = new Audio();
}

AudioView::~AudioView()
{
    delete ui;
    delete operatoreUno;
    delete operatoreDue;
    delete operatoreTre;
}

void AudioView::handle() {
    // Something to do here
    ui->setupUi(this);
    setWindowTitle("Kalk - Audio wave");
    show();

    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SIGNAL(signalBack()));

    connect(ui->btnInserisciOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaUno()));
    connect(ui->btnSostituisciOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaUno()));
    connect(ui->btnOttieniOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaUno()));
    connect(ui->btnEliminaOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaUno()));

    connect(ui->btnInserisciOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaDue()));
    connect(ui->btnSostituisciOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaDue()));
    connect(ui->btnOttieniOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaDue()));
    connect(ui->btnEliminaOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaDue()));

    connect(ui->btnSommaOndeAudio, SIGNAL(clicked(bool)), this, SLOT(slotCalcola()));
    connect(ui->btnSottrazioneOndeAudio, SIGNAL(clicked(bool)), this, SLOT(slotCalcola()));
    connect(ui->btnDivisioneOndeAudio, SIGNAL(clicked(bool)), this, SLOT(slotCalcola()));
    connect(ui->btnMoltiplicazioneOndeAudio, SIGNAL(clicked(bool)), this, SLOT(slotCalcola()));

    // Sistemiamo gli assi
    ui->widgetOndaUno->xAxis2->setVisible(true);
    ui->widgetOndaUno->xAxis2->setTickLabels(false);
    ui->widgetOndaUno->yAxis2->setVisible(true);
    ui->widgetOndaUno->yAxis2->setTickLabels(false);
    ui->widgetOndaDue->xAxis2->setVisible(true);
    ui->widgetOndaDue->xAxis2->setTickLabels(false);
    ui->widgetOndaDue->yAxis2->setVisible(true);
    ui->widgetOndaDue->yAxis2->setTickLabels(false);
    ui->widgetRisultato->xAxis2->setVisible(true);
    ui->widgetRisultato->xAxis2->setTickLabels(false);
    ui->widgetRisultato->yAxis2->setVisible(true);
    ui->widgetRisultato->yAxis2->setTickLabels(false);
}

void AudioView::updateAllOp() {
    updateOperatore(ui->widgetOndaUno, operatoreUno);
    updateOperatore(ui->widgetOndaDue, operatoreDue);
    updateOperatore(ui->widgetRisultato, operatoreTre);
}

void AudioView::updateOperatore(QCustomPlot* cPlot, Audio* audio) {
    cPlot->clearGraphs();
    cPlot->addGraph();
    cPlot->addGraph();
    cPlot->graph(0)->setPen(QPen(Qt::blue));
    cPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    cPlot->graph(1)->setPen(QPen(Qt::red));
    cPlot->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20)));

    for (int i=0; i < audio->waveLenght() ; ++i) {
        cPlot->graph(0)->addData(i, audio->getAmpVal(i));
        cPlot->graph(1)->addData(i, audio->getAmpVal(i, Audio::ondeDisponibili::ondaDx));
    }

    cPlot->graph(0)->rescaleAxes(true);
    cPlot->graph(1)->rescaleAxes(true);
    cPlot->replot();
}

void AudioView::slotOpOndaUno() {
    QString valOndaUnoSx = ui->lineEditValoriOndaUnoOndaSx->text();
    QString valOndaUnoDx = ui->lineEditValoriOndaUnoOndaDx->text();
    int indOndaUno = ui->lineEditIndiceOndaUno->text().simplified().toLower().replace( " ", "" ).toInt();
    int lungOndaUno = ui->lineEditLunghezzaOndaUno->text().simplified().toLower().replace( " ", "" ).toInt();

    // controlli vari sul formato degli input
    valOndaUnoSx = valOndaUnoSx.simplified().toLower();
    valOndaUnoSx.replace( " ", "" );
    valOndaUnoDx = valOndaUnoDx.simplified().toLower();
    valOndaUnoDx.replace( " ", "" );
    QStringList listUnoSx = valOndaUnoSx.split(',');
    QStringList listUnoDx = valOndaUnoDx.split(',');

    try {

        if (ui->lineEditIndiceOndaUno->text().simplified().toLower().replace( " ", "" ) == ""){
            throw exce_kalk("Inserire indice -1 per cominciare ad inserire.");
        }
        if (sender() == ui->btnInserisciOndaUno) {
            if (listUnoSx.length() != listUnoDx.length() || indOndaUno > operatoreUno->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            } else if (ui->lineEditValoriOndaUnoOndaSx->text()  == "" || ui->lineEditValoriOndaUnoOndaDx->text() ==""){
                throw exce_kalk("Non sono stati inseriti valori");
            } else {
                for (int i = 0; i < listUnoSx.length() ; ++i) {
                    int indTarget = (indOndaUno<0 ? -1 : indOndaUno+i);
                    operatoreUno->pushPoint(listUnoSx[i].toDouble() , listUnoDx[i].toDouble(), indTarget, true);
                }
                updateAllOp();
            }
        } else if (sender() == ui->btnSostituisciOndaUno){
            if (indOndaUno < 0) indOndaUno = 0;
            if (listUnoSx.length() != listUnoDx.length() || indOndaUno <0 || indOndaUno+listUnoSx.length() > operatoreUno->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else{
                for (int i = 0; i < listUnoSx.length() ; ++i) {
                    int indTarget = (indOndaUno<0 ? 0 : indOndaUno+i);
                    operatoreUno->pushPoint(listUnoSx[i].toDouble() , listUnoDx[i].toDouble(), indTarget, false);
                }
                updateAllOp();
            }
        } else if (sender() == ui->btnOttieniOndaUno) {
            if (indOndaUno+lungOndaUno > operatoreUno->waveLenght()) {
                throw exce_kalk("Indici fuori dal range. Ricontrollare che esistano.");
            }else if(indOndaUno <0) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            } else {
                // ottengo i dati
                QString ondaSx, ondaDx, comma;
                for (int i = indOndaUno; i < indOndaUno+lungOndaUno ; ++i) {
                    ondaSx.append(comma);
                    ondaDx.append(comma);
                    ondaSx.append( QString::number(operatoreUno->getAmpVal(i)) );
                    ondaDx.append( QString::number(operatoreUno->getAmpVal(i, Audio::ondeDisponibili::ondaDx)) );
                    comma = ", ";
                }
                ui->lineEditValoriOndaUnoOndaSx->setText(ondaSx);
                ui->lineEditValoriOndaUnoOndaDx->setText(ondaDx);
            }
        } else if (sender() == ui->btnEliminaOndaUno) {
            if (indOndaUno <0 || indOndaUno+lungOndaUno > operatoreUno->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else{
                // rimuovo i dati
                for (int i = indOndaUno; i < indOndaUno+lungOndaUno ; ++i) {
                    operatoreUno->removePoint(indOndaUno);
                }
            }
            updateAllOp();
        }
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void AudioView::slotOpOndaDue() {
    QString valOndaDueSx = ui->lineEditValoriOndaDueOndaSx->text();
    QString valOndaDueDx = ui->lineEditValoriOndaDueOndaDx->text();
    int indOndaDue = ui->lineEditIndiceOndaDue->text().simplified().toLower().replace( " ", "" ).toInt();
    int lungOndaDue = ui->lineEditLunghezzaOndaDue->text().simplified().toLower().replace( " ", "" ).toInt();

    // controlli vari sul formato degli input
    valOndaDueSx = valOndaDueSx.simplified().toLower();
    valOndaDueSx.replace( " ", "" );
    valOndaDueDx = valOndaDueDx.simplified().toLower();
    valOndaDueDx.replace( " ", "" );
    QStringList listDueSx = valOndaDueSx.split(',');
    QStringList listDueDx = valOndaDueDx.split(',');
    try {

        if (ui->lineEditIndiceOndaDue->text().simplified().toLower().replace( " ", "" ) == ""){
            throw exce_kalk("Inserire indice -1 per cominciare ad inserire.");
        }
        if (sender() == ui->btnInserisciOndaDue) {
            if (ui->lineEditValoriOndaDueOndaSx->text()  == "" || ui->lineEditValoriOndaDueOndaDx->text() ==""){
                throw exce_kalk("Non sono stati inseriti valori");
            } else if (listDueSx.length() != listDueDx.length() || indOndaDue > operatoreDue->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else{
                for (int i = 0; i < listDueSx.length() ; ++i) {
                    int indTarget = (indOndaDue<0 ? -1 : indOndaDue+i);
                    operatoreDue->pushPoint(listDueSx[i].toDouble() , listDueDx[i].toDouble(), indTarget, true);
                }
                updateAllOp();
            }
        } else if (sender() == ui->btnSostituisciOndaDue){
            if (indOndaDue < 0) indOndaDue = 0;
            if (listDueSx.length() != listDueDx.length() || indOndaDue <0 || indOndaDue+listDueSx.length() > operatoreDue->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else{
                for (int i = 0; i < listDueSx.length() ; ++i) {
                    int indTarget = (indOndaDue<0 ? 0 : indOndaDue+i);
                    operatoreDue->pushPoint(listDueSx[i].toDouble() , listDueDx[i].toDouble(), indTarget, false);
                }
                updateAllOp();
            }
        } else if (sender() == ui->btnOttieniOndaDue) {
            if (indOndaDue <0) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else if(indOndaDue+lungOndaDue > operatoreDue->waveLenght()){
                throw exce_kalk("Indici fuori dal range. Ricontrollare che esistano.");
            }else {
                // ottengo i dati
                QString ondaSx, ondaDx, comma;
                for (int i = indOndaDue; i < indOndaDue+lungOndaDue ; ++i) {
                    ondaSx.append(comma);
                    ondaDx.append(comma);
                    ondaSx.append( QString::number(operatoreDue->getAmpVal(i)) );
                    ondaDx.append( QString::number(operatoreDue->getAmpVal(i, Audio::ondeDisponibili::ondaDx)) );
                    comma = ", ";
                }
                ui->lineEditValoriOndaDueOndaSx->setText(ondaSx);
                ui->lineEditValoriOndaDueOndaDx->setText(ondaDx);
            }
        } else if (sender() == ui->btnEliminaOndaDue) {
            if (indOndaDue <0 || indOndaDue+lungOndaDue > operatoreDue->waveLenght()) {
                throw exce_kalk("Le onde audio sono caratterizzate da due onde, onda sinistra e onda destra di lunghezza uguale. ");
            }else{
                // rimuovo i dati
                for (int i = indOndaDue; i < indOndaDue+lungOndaDue ; ++i) {
                    operatoreDue->removePoint(indOndaDue);
                }
            }
            updateAllOp();
        }
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void AudioView::slotCalcola() {
    try {
        if (sender() == ui->btnSommaOndeAudio) {
            *operatoreTre = *operatoreUno + *operatoreDue;
        } else if (sender() == ui->btnSottrazioneOndeAudio){
            *operatoreTre = *operatoreUno - *operatoreDue;
        } else if (sender() == ui->btnDivisioneOndeAudio) {
            *operatoreTre = *operatoreUno / *operatoreDue;
        } else if (sender() == ui->btnMoltiplicazioneOndeAudio) {
            *operatoreTre = *operatoreUno * *operatoreDue;
        }
        updateOperatore(ui->widgetRisultato, operatoreTre);
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}
