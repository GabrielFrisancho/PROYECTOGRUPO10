#ifndef MOVIENOTIFIER_H
#define MOVIENOTIFIER_H

#include <vector>
#include <algorithm>
#include "Observer.h"

class MovieNotifier {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const QString& movieTitle) {
        for (auto observer : observers) {
            observer->update(movieTitle);
        }
    }
};

#endif // MOVIENOTIFIER_H
