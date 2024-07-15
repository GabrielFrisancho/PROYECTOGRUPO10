#include "UserPreferences.h"

UserPreferences* UserPreferences::instance = nullptr;

UserPreferences* UserPreferences::getInstance() {
    if (instance == nullptr) {
        instance = new UserPreferences();
    }
    return instance;
}

void UserPreferences::addLike(const QString &title) {
    likes.insert(title);
}

void UserPreferences::addWatchLater(const QString &title) {
    watchLater.insert(title);
}

std::set<QString> UserPreferences::getLikes() const {
    return likes;
}

std::set<QString> UserPreferences::getWatchLater() const {
    return watchLater;
}
