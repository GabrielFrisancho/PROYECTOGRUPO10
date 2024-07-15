// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

#include <QString>

class Observer {
public:
    virtual void update(const QString& movieTitle) = 0;
    virtual ~Observer() = default;
};

#endif // OBSERVER_H

