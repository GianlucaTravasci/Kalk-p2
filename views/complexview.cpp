#include "complexview.h"
#include "ui_complexview.h"
#include <QFile>
#include <QMessageBox>
#include <QPixmap>
#include <QMovie>

ComplexView::ComplexView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComplexView)
{
    // Nothing to do here
    QFile file (":/Resources/Resources/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
}

ComplexView::~ComplexView()
{
    delete ui;
    delete op1;
    delete op2;
    delete op3;
}

void ComplexView::initialize() {
    op1 = new Complex();
    op2 = new Complex();
    op3 = new Complex();

    // Configurazione tasti disponibili
    confFor = TastierinoView::configurabile::confForComplessi;

    // Validator setup for complex
    QRegExp regx(Complex::regExp);
    validator.setRegExp(regx);

    // Set placeholder
    placeholder = "Formato: 0 , 0i";

    setWindowTitle("Kalk - Complessi");
}

void ComplexView::handle() {
    // Setup iniziali
    ui->setupUi(this);
    initialize();
    operationStep = 0;

    // Sistemiamo un po' la grafica
    ui->labelLog->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    ui->lineEditCurrent->setAlignment(Qt::AlignRight);
    ui->lineEditCurrent->setPlaceholderText(placeholder);
    manageKeys();

    show(); // Mostriamo il tutto altrimenti abbiamo fatto questo per niente

    // Connect all buttons
    connect(ui->btnBack, SIGNAL(clicked()),             this, SIGNAL(signalBack()));

    connect(ui->btnSomma, SIGNAL(clicked()),            this, SLOT(slotCalculate()));
    connect(ui->btnSottrazione, SIGNAL(clicked()),      this, SLOT(slotCalculate()));
    connect(ui->btnMoltiplicazione, SIGNAL(clicked()),  this, SLOT(slotCalculate()));
    connect(ui->btnDivisione, SIGNAL(clicked()),        this, SLOT(slotCalculate()));
    connect(ui->btnInverso, SIGNAL(clicked()),          this, SLOT(slotCalculate()));
    connect(ui->btnConiugato, SIGNAL(clicked()),        this, SLOT(slotCalculate()));
    connect(ui->btnNorma, SIGNAL(clicked()),            this, SLOT(slotCalculate()));

    connect(ui->btnCalcola, SIGNAL(clicked()),          this, SLOT(slotCalculate()));

    connect(ui->btnClearE, SIGNAL(clicked()),           this, SLOT(slotEditCurrent()));
    connect(ui->btnClear, SIGNAL(clicked()),            this, SLOT(slotEditCurrent()));
    connect(ui->btnBackspace, SIGNAL(clicked()),        this, SLOT(slotEditCurrent()));

    // Connetto il tastierino
    connect(ui->widgetTastierino, SIGNAL(signalKeyPressed(QString)), this, SLOT(slotKeyPressed(QString)));
    ui->widgetTastierino->configureFor(confFor);
}

void ComplexView::errorManager(QString err) {
    // Something to do here
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setStyleSheet("QPushButton{padding:5px 10px;}");
    if (ui->lineEditCurrent->text() == "pulpfiction") {
        QLabel* label = new QLabel(msgBox);
        label-> setWindowFlags(Qt::FramelessWindowHint);
        label->setObjectName("imgGif");
        QPixmap p(":/Resources/Resources/whatIcon.gif");

        msgBox->setStyleSheet("QLabel{min-height:70px;padding-left:70px} #imgGif{padding-left:0;} QPushButton{padding:5px 10px;}");

        label->setPixmap(p);
        label->setFixedHeight(100);
        label->setFixedWidth(100);

        QMovie *movie = new QMovie(":/Resources/Resources/whatIcon.gif");
        label->setMovie(movie);
        movie->start();

        label->show();
    }else{
        msgBox->setText(err);
    }
    msgBox->exec();
}

void ComplexView::logAppend(QString str) {
    ui->labelLog->setText(
        ui->labelLog->text().append("<p>").append(str).append("</p>"));
}

void ComplexView::logReset() {
    ui->labelLog->setText("");
}

void ComplexView::manageKeys() {
    bool isZero = (operationStep == 0 ? true : false );
    setEnabledKey(ui->btnSomma, isZero);
    setEnabledKey(ui->btnSottrazione, isZero);
    setEnabledKey(ui->btnMoltiplicazione, isZero);
    setEnabledKey(ui->btnDivisione, isZero);
    setEnabledKey(ui->btnCalcola, !isZero);   // Sarà attivo solo in fase 1 a differenza degli altri
    setEnabledKey(ui->btnInverso, isZero);
    setEnabledKey(ui->btnNorma, isZero);
    setEnabledKey(ui->btnConiugato, isZero);
}

void ComplexView::setEnabledKey(QWidget* widget, bool enabled) {
    widget->setEnabled(enabled);
    style()->unpolish(widget);
    style()->polish(widget);
}

void ComplexView::calcola() {
    try {
        switch (operation) {
        case tipiCalcolo::sum:
            op3 = &(*op1 + *op2);
            break;
        case tipiCalcolo::sub:
            op3 = &(*op1 - *op2);
            break;
        case tipiCalcolo::mult:
            op3 = &(*op1 * *op2);
            break;
        case tipiCalcolo::div:
            op3 = &(*op1 / *op2);
            break;
        }
        logAppend(op3->getString());
        ui->lineEditCurrent->setText(op3->getString());
        ui->lineEditCurrent->setFocus();
        operationStep = 0;
    }catch (exce_kalk e) {
        // Errore
        logReset();
        operationStep = 0;
        errorManager(e.what());
    }
}

void ComplexView::slotCalculate() {
    // TODO: controlli dei valori ??
    try {
        QString str = ui->lineEditCurrent->text();
        str = str.simplified().toLower();
        str.replace( " ", "" );
        int pos = 0;
        if (validator.validate(str, pos) != QRegExpValidator::State::Acceptable) {
            errorManager("Input non valido, controlla che il formato sia corretto");
            return;
        }
        if (operationStep == 0) {
            logReset();
            if(sender() == ui->btnSomma) {
                ++operationStep;
                op1->string(str);
                operation = tipiCalcolo::sum;
                logAppend(op1->getString());
                logAppend("+");
                ui->lineEditCurrent->setText("");
            }else if(sender() == ui->btnSottrazione) {
                ++operationStep;
                op1->string(str);
                operation = tipiCalcolo::sub;
                logAppend(op1->getString());
                logAppend("-");
                ui->lineEditCurrent->setText("");
            }else if(sender() == ui->btnMoltiplicazione) {
                ++operationStep;
                op1->string(str);
                operation = tipiCalcolo::mult;
                logAppend(op1->getString());
                logAppend("*");
                ui->lineEditCurrent->setText("");
            }else if(sender() == ui->btnDivisione) {
                ++operationStep;
                op1->string(str);
                operation = tipiCalcolo::div;
                logAppend(op1->getString());
                logAppend("/");
                ui->lineEditCurrent->setText("");
            }else if(sender() == ui->btnInverso) {
                op3->string(str);
                logAppend(op3->getString());
                op3 = &(op3->inverse());
                logAppend("Inverso:");
                logAppend(op3->getString());
                ui->lineEditCurrent->setText(op3->getString());
            }else if(sender() == ui->btnNorma) {
                op3->string(str);
                logAppend(op3->getString());
                double res = op3->norm();
                logAppend("Norma:");
                logAppend(QString::number(res));
                ui->lineEditCurrent->setText(op3->getString());
            }else if(sender() == ui->btnConiugato) {
                op3->string(str);
                logAppend(op3->getString());
                *op3 = op3->conjugate();
                logAppend("Coniugato:");
                logAppend(op3->getString());
                ui->lineEditCurrent->setText(op3->getString());
            }
        }else if(operationStep == 1) {
            if(sender() == ui->btnCalcola) {
                op2->string(str);
                logAppend(op2->getString());
                logAppend("=");
                calcola();
            }
        }
    }catch (exce_kalk e) {
        // Errore
        logReset();
        operationStep = 0;
        errorManager(e.what());
    }
    manageKeys();
    ui->lineEditCurrent->setFocus();
}

void ComplexView::slotEditCurrent() {
    if(sender() == ui->btnClearE) {
        ui->lineEditCurrent->setText("");
    }else if(sender() == ui->btnClear) {
        logReset();
        ui->lineEditCurrent->setText("");
        operationStep = 0;
    }else if(sender() == ui->btnBackspace) {
        QString current = ui->lineEditCurrent->text();
        if (current.size() > 0) {
            current.resize(current.size() - 1);
        }
        ui->lineEditCurrent->setText( current );
    }
    manageKeys();
    ui->lineEditCurrent->setFocus();
}

void ComplexView::slotKeyPressed(QString premuto) {
    premuto.prepend(ui->lineEditCurrent->text());
    ui->lineEditCurrent->setText(premuto);
    ui->lineEditCurrent->setFocus();
}
