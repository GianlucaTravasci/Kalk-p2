#include "kalkselectorview.h"
#include "ui_kalkselectorview.h"

KalkSelectorView::KalkSelectorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KalkSelectorView)
{
    // Nothing to do here...
}

KalkSelectorView::~KalkSelectorView()
{
    delete ui;
}

void KalkSelectorView::handle() {
    // Something to do here
    ui->setupUi(this);
    setWindowTitle("Kalk");
    show();
    connect(ui->openComplex, SIGNAL(clicked(bool)), this, SLOT(slotOpenComplex()));
    connect(ui->openQuaternion, SIGNAL(clicked(bool)), this, SLOT(slotOpenQuaternion()));
    connect(ui->openAudio, SIGNAL(clicked(bool)), this, SLOT(slotOpenAudio()));
    connect(ui->openColor,SIGNAL(clicked(bool)), this, SLOT(slotOpenColoredWave()));
}


void KalkSelectorView::slotOpenComplex() {
    emit signalOpenKalk(Application::KalkType::Complessi);
}

void KalkSelectorView::slotOpenQuaternion() {
    emit signalOpenKalk(Application::KalkType::Quaternioni);
}

void KalkSelectorView::slotOpenAudio() {
    emit signalOpenKalk(Application::KalkType::OndeAudio);
}
void KalkSelectorView::slotOpenColoredWave() {
    emit signalOpenKalk(Application::KalkType::OndeColorate);
}
