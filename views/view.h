#ifndef VIEW_H
#define VIEW_H

#include <QObject>

class View
{
public:
    virtual ~View() = default;
    View() = default;
    View(const View&) = delete;
    View& operator=(const View&) = delete;

    virtual void handle() =0;

signals:
    void signalBack();
};

#endif // VIEW_H
