#include "UserPreferences.h"

UserPreferences* UserPreferences::instance = nullptr;

UserPreferences* UserPreferences::getInstance() {
    if (instance == nullptr) {
        instance = new UserPreferences();
    }
    return instance;
}

void UserPreferences::addLike(const QString &movieTitle) {
    std::lock_guard<std::mutex> lock(mutex);
    likes.push_back(movieTitle);
}

void UserPreferences::addWatchLater(const QString &movieTitle) {
    std::lock_guard<std::mutex> lock(mutex);
    watchLater.push_back(movieTitle);
}

std::vector<QString> UserPreferences::getLikes() const {
    std::lock_guard<std::mutex> lock(mutex);
    return likes;
}

std::vector<QString> UserPreferences::getWatchLater() const {
    std::lock_guard<std::mutex> lock(mutex);
    return watchLater;
}

