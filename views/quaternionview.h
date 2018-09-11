#ifndef QUATERNIONVIEW_H
#define QUATERNIONVIEW_H

#include <QWidget>
#include <QString>
#include "views/complexview.h"
#include "logica/quaternion.h"


class QuaternionView : public ComplexView
{
    Q_OBJECT

public:
    void initialize() override;
};

#endif // QUATERNIONVIEW_H
