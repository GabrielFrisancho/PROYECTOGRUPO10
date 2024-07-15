// UserNotifier.h
#ifndef USERNOTIFIER_H
#define USERNOTIFIER_H

#include "Observer.h"
#include <iostream>

class UserNotifier : public Observer {
private:
    QString username;

public:
    UserNotifier(const QString& name) : username(name) {}

    void update(const QString& movieTitle) override {
        std::cout << "Hey " << username.toStdString() << "! A new movie matching your preferences has been added: "
                  << movieTitle.toStdString() << std::endl;
    }
};

#endif // USERNOTIFIER_H
