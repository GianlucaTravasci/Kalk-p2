#include "quaternionview.h"

void QuaternionView::initialize() {
    op1 = new Quaternion();
    op2 = new Quaternion();
    op3 = new Quaternion();

    // Configurazione tasti disponibili
    confFor = TastierinoView::configurabile::confForQuaternioni;

    // Validator setup for quaternion
    QRegExp regx(Quaternion::regExp);
    validator.setRegExp(regx);

    // Set placeholder
    placeholder = "Formato: 0 , 0i, 0j, 0k";

    setWindowTitle("Kalk - Quaternioni");
}
