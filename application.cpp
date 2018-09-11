#include "application.h"
#include "views/kalkselectorview.h"
#include "views/audioview.h"
#include "views/coloredwaveview.h"
#include "views/complexview.h"
#include "views/quaternionview.h"

Application::Application(int* argc, char** argv[]) :
    qAppl(*argc, *argv)
{
}

Application::~Application() {
}

void Application::initialize() {
    // do something   0_0
    currentView = new KalkSelectorView();

    currentView->handle();

    KalkSelectorView* aux = dynamic_cast<KalkSelectorView*>(currentView);
    connect(aux, SIGNAL(signalOpenKalk(int)), this, SLOT(slotOpenKalkType(int)));
}

void Application::initializeKalk(View* subC) {
    destroyView();
    currentView = subC;
    subC->handle();
}

void Application::destroyView() {
    if (currentView)
        delete currentView;
}

void Application::exitKalk() {
    destroyView();
    initialize();
}

int Application::exec() {
    return qAppl.exec();
}

void Application::slotOpenKalkType(int tipo) {
    switch (tipo) {
    case Application::KalkType::Complessi:
        {ComplexView* aux = new ComplexView();
        connect(aux, SIGNAL(signalBack()), this, SLOT(slotBack()));
        initializeKalk(aux);}
        break;
    case Application::KalkType::Quaternioni:
        {ComplexView* aux = new QuaternionView();
        connect(aux, SIGNAL(signalBack()), this, SLOT(slotBack()));
        initializeKalk(aux);}
        break;
    case Application::KalkType::OndeAudio:{
        AudioView* aux = new AudioView();
        connect(aux, SIGNAL(signalBack()), this, SLOT(slotBack()));
        initializeKalk(aux);}
        break;
    case Application::KalkType::OndeColorate:{
        ColoredWaveView* aux = new ColoredWaveView();
        connect(aux, SIGNAL(signalBack()), this, SLOT(slotBack()));
        initializeKalk(aux);}
    }

}

void Application::slotBack() {
    exitKalk();
}
