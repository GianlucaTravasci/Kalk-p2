#include "coloredwaveview.h"
#include "ui_coloredwaveview.h"
#include "helper.h"


ColoredWaveView::ColoredWaveView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColoredWaveView)
{
    QFile file (":/Resources/Resources/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
    ui->setupUi(this);
    setWindowTitle("Kalk - Colored wave");
    operatoreUno = new ColoredWave();
    operatoreDue = new ColoredWave();
    operatoreTre = new ColoredWave();
}

ColoredWaveView::~ColoredWaveView()
{
    delete ui;
    delete operatoreUno;
    delete operatoreDue;
    delete operatoreTre;
}

void ColoredWaveView::handle() {
    //ui->setupUi(this);
    show();

    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SIGNAL(signalBack()));

    connect(ui->btnInserisciOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataUno()));
    connect(ui->btnSostituisciOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataUno()));
    connect(ui->btnOttieniOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataUno()));
    connect(ui->btnEliminaOndaUno, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataUno()));

    connect(ui->lineEditROndaUno,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndaUno()));
    connect(ui->lineEditGOndaUno,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndaUno()));
    connect(ui->lineEditBOndaUno,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndaUno()));

    connect(ui->horizontalSliderROndaUno,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaUno()));
    connect(ui->horizontalSliderGOndaUno,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaUno()));
    connect(ui->horizontalSliderBOndaUno,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaUno()));


    connect(ui->btnInserisciOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataDue()));
    connect(ui->btnSostituisciOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataDue()));
    connect(ui->btnOttieniOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataDue()));
    connect(ui->btnEliminaOndaDue, SIGNAL(clicked(bool)), this, SLOT(slotOpOndaColorataDue()));

    connect(ui->lineEditROndaDue,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndadue()));
    connect(ui->lineEditGOndaDue,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndaDue()));
    connect(ui->lineEditBOndaDue,SIGNAL(textChanged(QString)),this, SLOT(slotSliderOndaDue()));

    connect(ui->horizontalSliderROndaDue,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaDue()));
    connect(ui->horizontalSliderGOndaDue,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaDue()));
    connect(ui->horizontalSliderBOndaDue,SIGNAL(valueChanged(int)),this, SLOT(slotSliderOndaDue()));


    connect(ui->btnSommaOndeColorate, SIGNAL(clicked(bool)), this, SLOT(slotCalcolaOndaColorata()));
    connect(ui->btnSottrazioneOndeColorate, SIGNAL(clicked(bool)), this, SLOT(slotCalcolaOndaColorata()));
    connect(ui->btnDivisioneOndeColorate, SIGNAL(clicked(bool)), this, SLOT(slotCalcolaOndaColorata()));
    connect(ui->btnMoltiplicazioneOndeColorate, SIGNAL(clicked(bool)), this, SLOT(slotCalcolaOndaColorata()));

    //Assi cartesiani
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

void ColoredWaveView::updateAllOp(){
    updateOperatore(ui->widgetOndaUno, ui->listWidgetColoriOndaUno, operatoreUno);
    updateOperatore(ui->widgetOndaDue, ui->listWidgetColoriOndaDue, operatoreDue);
    updateOperatore(ui->widgetRisultato, ui->listWidgetColoriOndaTre, operatoreTre);
}

void ColoredWaveView::updateOperatore(QCustomPlot* cPlot, QListWidget* listW, ColoredWave* cWave) {
    cPlot->clearGraphs();
    cPlot->addGraph();
    cPlot->graph(0)->setPen(QPen(Qt::black));
    cPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    listW->clear();
    for(int i=0; i<cWave->waveLenght(); ++i){
        cPlot->graph(0)->addData(i, cWave->getAmpVal(i));

        Color colore = cWave->getColor(i);
        QColor coloreSfondo(colore.getRdec(), colore.getGdec(), colore.getBdec());
        QBrush brushSfondo(coloreSfondo);
        QColor coloreText(255-colore.getRdec(), 255-colore.getGdec(), 255-colore.getBdec());
        QBrush brushText(coloreText);
        QListWidgetItem *item = new QListWidgetItem();
        item->setBackground(brushSfondo);
        item->setForeground(brushText);
        item->setText(QString::number(i));
        listW->addItem(item);
    }
    cPlot->graph(0)->rescaleAxes(true);
    cPlot->replot();
}

void ColoredWaveView::slotSliderOndaUno() {
    int rVal, gVal, bVal;
    rVal = ui->lineEditROndaUno->text().toInt();
    gVal = ui->lineEditGOndaUno->text().toInt();
    bVal = ui->lineEditBOndaUno->text().toInt();
    if(sender() == ui->horizontalSliderROndaUno){
        rVal = ui->horizontalSliderROndaUno->value();
    } else if(sender() == ui->horizontalSliderGOndaUno) {
        gVal = ui->horizontalSliderGOndaUno->value();
    } else if (sender() == ui->horizontalSliderBOndaUno){
        bVal = ui->horizontalSliderBOndaUno->value();
    } else if(sender() == ui->lineEditROndaUno){
        rVal = ui->lineEditROndaUno->text().toInt();
    } else if(sender() == ui->lineEditGOndaUno) {
        gVal = ui->lineEditGOndaUno->text().toInt();
    } else if (sender() == ui->lineEditBOndaUno){
        bVal = ui->lineEditBOndaUno->text().toInt();
    }
    if (rVal < 0)   rVal = 0;
    if (rVal > 255) rVal = 255;
    if (gVal < 0)   gVal = 0;
    if (gVal > 255) gVal = 255;
    if (bVal < 0)   bVal = 0;
    if (bVal > 255) bVal = 255;
    ui->horizontalSliderROndaUno->setValue(rVal);
    ui->horizontalSliderGOndaUno->setValue(gVal);
    ui->horizontalSliderBOndaUno->setValue(bVal);
    ui->lineEditROndaUno->setText(QString::number(rVal));
    ui->lineEditGOndaUno->setText(QString::number(gVal));
    ui->lineEditBOndaUno->setText(QString::number(bVal));

    Color* cTemp = new Color(rVal, gVal, bVal);
    QString stringColor = Color::ConvertRGBtoHex(cTemp);
    delete cTemp;
    ui->lineEditStringOndaUno->setText(stringColor);
}

void ColoredWaveView::slotSliderOndaDue() {
    int rVal, gVal, bVal;
    rVal = ui->lineEditROndaDue->text().toInt();
    gVal = ui->lineEditGOndaDue->text().toInt();
    bVal = ui->lineEditBOndaDue->text().toInt();
    if(sender() == ui->horizontalSliderROndaDue){
        rVal = ui->horizontalSliderROndaDue->value();
    } else if(sender() == ui->horizontalSliderGOndaDue) {
        gVal = ui->horizontalSliderGOndaDue->value();
    } else if (sender() == ui->horizontalSliderBOndaDue){
        bVal = ui->horizontalSliderBOndaDue->value();
    } else if(sender() == ui->lineEditROndaDue){
        rVal = ui->lineEditROndaDue->text().toInt();
    } else if(sender() == ui->lineEditGOndaDue) {
        gVal = ui->lineEditGOndaDue->text().toInt();
    } else if (sender() == ui->lineEditBOndaDue){
        bVal = ui->lineEditBOndaDue->text().toInt();
    }
    if (rVal < 0)   rVal = 0;
    if (rVal > 255) rVal = 255;
    if (gVal < 0)   gVal = 0;
    if (gVal > 255) gVal = 255;
    if (bVal < 0)   bVal = 0;
    if (bVal > 255) bVal = 255;
    ui->horizontalSliderROndaDue->setValue(rVal);
    ui->horizontalSliderGOndaDue->setValue(gVal);
    ui->horizontalSliderBOndaDue->setValue(bVal);
    ui->lineEditROndaDue->setText(QString::number(rVal));
    ui->lineEditGOndaDue->setText(QString::number(gVal));
    ui->lineEditBOndaDue->setText(QString::number(bVal));

    Color* cTemp = new Color(rVal, gVal, bVal);
    QString stringColor = Color::ConvertRGBtoHex(cTemp);
    delete cTemp;
    ui->lineEditStringOndaDue->setText(stringColor);
}

void ColoredWaveView::slotOpOndaColorataUno(){
    double ampOndaUno = ui->lineEditValoriOndaUno->text().simplified().toLower().replace(" ", "").toDouble();
    int indOndaUno = ui->lineEditIndiceOndaUno->text().simplified().toLower().replace( " ", "" ).toInt();

    int valROndaUno = ui->lineEditROndaUno->text().simplified().toLower().replace( " ", "").toInt();
    int valGOndaUno = ui->lineEditGOndaUno->text().simplified().toLower().replace( " ", "").toInt();
    int valBOndaUno = ui->lineEditBOndaUno->text().simplified().toLower().replace( " ", "").toInt();
    Color colore(valROndaUno, valGOndaUno, valBOndaUno);
    try {

        if (ui->lineEditIndiceOndaUno->text().simplified().toLower().replace( " ", "" ) == ""){
            throw exce_kalk("Inserire indice -1 per cominciare ad inserire.");
        }
        if (sender() == ui->btnInserisciOndaUno){
            if (ui->lineEditValoriOndaUno->text().simplified().toLower().replace(" ", "") == ""){
                throw exce_kalk("Non sono stati inseriti valori");
            } else {
                int indTarget = (indOndaUno<0 ? -1 : indOndaUno);
                operatoreUno->pushPoint(ampOndaUno, colore, indTarget, true);
                updateAllOp();
            }
        } else if(sender() == ui->btnSostituisciOndaUno) {
            if (indOndaUno < 0) indOndaUno = 0;
            int indTarget = (indOndaUno<0 ? 0 : indOndaUno);
            operatoreUno->pushPoint(ampOndaUno, colore, indTarget, false);
            updateAllOp();
        } else if (sender() == ui->btnOttieniOndaUno) {
            if (indOndaUno < 0 || indOndaUno >= operatoreUno->waveLenght()) {
                throw exce_kalk("Indice Fuori dal range consentito. Controllare che sia positivo o che esista.");
            } else {
                ui->lineEditValoriOndaUno->setText(QString::number(operatoreUno->getAmpVal(indOndaUno)));
                ui->lineEditROndaUno->setText(QString::number(operatoreUno->getColor(indOndaUno).getRdec()));
                ui->lineEditGOndaUno->setText(QString::number(operatoreUno->getColor(indOndaUno).getGdec()));
                ui->lineEditBOndaUno->setText(QString::number(operatoreUno->getColor(indOndaUno).getBdec()));
            }
        } else if (sender() == ui->btnEliminaOndaUno) {
            if (indOndaUno < 0 || indOndaUno >= operatoreUno->waveLenght()) {
                throw exce_kalk("Indice Fuori dal range consentito. Controllare che sia positivo o che esista.");
            } else {
                operatoreUno->removePoint(indOndaUno);
                updateAllOp();
            }
        }
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void ColoredWaveView::slotOpOndaColorataDue() {
    double ampOndaDue = ui->lineEditValoriOndaDue->text().simplified().toLower().replace( " ", "").toDouble();
    int indOndaDue = ui->lineEditIndiceOndaDue->text().simplified().toLower().replace( " ", "" ). toInt();

    int valROndaDue = ui->lineEditROndaDue->text().simplified().toLower().replace( " ", "").toInt();
    int valGOndaDue = ui->lineEditGOndaDue->text().simplified().toLower().replace( " ", "").toInt();
    int valBOndaDue = ui->lineEditBOndaDue->text().simplified().toLower().replace( " ", "").toInt();
    Color colore(valROndaDue, valGOndaDue, valBOndaDue);
    try {

        if (ui->lineEditIndiceOndaDue->text().simplified().toLower().replace( " ", "" ) == ""){
            throw exce_kalk("Inserire indice -1 per cominciare ad inserire.");
        }
        if (sender() == ui->btnInserisciOndaDue){
            if (ui->lineEditValoriOndaDue->text().simplified().toLower().replace(" ", "") == ""){
                throw exce_kalk("Non sono stati inseriti valori");
            } else {
                int indTarget = (indOndaDue<0 ? -1 : indOndaDue);
                operatoreDue->pushPoint(ampOndaDue, colore, indTarget, true);
                updateAllOp();
            }
        } else if(sender() == ui->btnSostituisciOndaDue) {
            if (indOndaDue < 0) indOndaDue = 0;
            int indTarget = (indOndaDue<0 ? 0 : indOndaDue);
            operatoreDue->pushPoint(ampOndaDue, colore, indTarget, false);
            updateAllOp();
        } else if (sender() == ui->btnOttieniOndaDue) {
            if (indOndaDue < 0 || indOndaDue >= operatoreDue->waveLenght()) {
                throw exce_kalk("Indice Fuori dal range consentito. Controllare che sia positivo o che esista.");
            } else {
                ui->lineEditValoriOndaDue->setText((QString::number(operatoreDue->getAmpVal(indOndaDue))));
                ui->lineEditROndaDue->setText(QString::number(operatoreDue->getColor(indOndaDue).getRdec()));
                ui->lineEditGOndaDue->setText(QString::number(operatoreDue->getColor(indOndaDue).getGdec()));
                ui->lineEditBOndaDue->setText(QString::number(operatoreDue->getColor(indOndaDue).getBdec()));
            }
        } else if (sender() == ui->btnEliminaOndaDue) {
            if (indOndaDue < 0 || indOndaDue >= operatoreDue->waveLenght()) {
                throw exce_kalk("Indice Fuori dal range consentito. Controllare che sia positivo o che esista.");
            } else {
                operatoreDue->removePoint(indOndaDue);
                updateAllOp();
            }
        }
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void ColoredWaveView::slotCalcolaOndaColorata(){
    try {
        if (sender() == ui->btnSommaOndeColorate) {
            *operatoreTre = *operatoreUno + *operatoreDue;
        } else if (sender() == ui->btnSottrazioneOndeColorate){
            *operatoreTre = *operatoreUno - *operatoreDue;
        } else if (sender() == ui->btnDivisioneOndeColorate) {
            *operatoreTre = *operatoreUno / *operatoreDue;
        } else if (sender() == ui->btnMoltiplicazioneOndeColorate) {
            *operatoreTre = *operatoreUno * *operatoreDue;
        }
        updateOperatore(ui->widgetRisultato, ui->listWidgetColoriOndaTre, operatoreTre);
    } catch(exce_kalk e) {
        // Errore
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}
