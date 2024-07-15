#ifndef USERNOTIFIER_H
#define USERNOTIFIER_H

#include "Observer.h"
#include <iostream>
#include <QString>

class UserNotifier : public Observer {
private:
    QString username;

public:
    UserNotifier(const QString& name) : username(name) {}

    void update(const QString& movieTitle) override {
        std::cout << "Hey " << username.toStdString() << "! A new movie matching your preferences has been added: "
                  << movieTitle.toStdString() << std::endl;
    }

    void setUsername(const QString& name) {
        username = name;
    }
};

#endif // USERNOTIFIER_H
