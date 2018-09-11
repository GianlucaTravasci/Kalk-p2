#include "tastierinoview.h"
#include "ui_tastierinoview.h"

TastierinoView::TastierinoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TastierinoView)
{
    ui->setupUi(this);

    connect(ui->btn0, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn1, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn2, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn3, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn4, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn5, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn6, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn7, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn8, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btn9, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnPoint, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnComma, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnI, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnJ, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnK, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
    connect(ui->btnMinus, SIGNAL(clicked(bool)), this, SLOT(slotKeyPressed()));
}

TastierinoView::~TastierinoView()
{
    delete ui;
}

void TastierinoView::configureFor(configurabile confFor) {
    switch (confFor) {
    case configurabile::confForComplessi:
        ui->btnI->setEnabled(true);
        ui->btnJ->setEnabled(false);
        ui->btnK->setEnabled(false);
        break;
    case configurabile::confForQuaternioni:
        ui->btnI->setEnabled(true);
        ui->btnJ->setEnabled(true);
        ui->btnK->setEnabled(true);
        break;
    }
    style()->unpolish(ui->btnI);
    style()->polish(ui->btnI);
    style()->unpolish(ui->btnJ);
    style()->polish(ui->btnJ);
    style()->unpolish(ui->btnK);
    style()->polish(ui->btnK);
}

void TastierinoView::slotKeyPressed() {
    if (sender() == ui->btn0) {
        emit signalKeyPressed("0");
    }else if (sender() == ui->btn1) {
        emit signalKeyPressed("1");
    }else if (sender() == ui->btn2) {
        emit signalKeyPressed("2");
    }else if (sender() == ui->btn3) {
        emit signalKeyPressed("3");
    }else if (sender() == ui->btn4) {
        emit signalKeyPressed("4");
    }else if (sender() == ui->btn5) {
        emit signalKeyPressed("5");
    }else if (sender() == ui->btn6) {
        emit signalKeyPressed("6");
    }else if (sender() == ui->btn7) {
        emit signalKeyPressed("7");
    }else if (sender() == ui->btn8) {
        emit signalKeyPressed("8");
    }else if (sender() == ui->btn9) {
        emit signalKeyPressed("9");
    }else if (sender() == ui->btnComma) {
        emit signalKeyPressed(",");
    }else if (sender() == ui->btnPoint) {
        emit signalKeyPressed(".");
    }else if (sender() == ui->btnI) {
        emit signalKeyPressed("i");
    }else if (sender() == ui->btnJ) {
        emit signalKeyPressed("j");
    }else if (sender() == ui->btnK) {
        emit signalKeyPressed("k");
    }else if (sender() == ui->btnMinus) {
        emit signalKeyPressed("-");
    }
}
