#include "UserPreferences.h"
#include <algorithm>

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
    watchLater.emplace_back(movieTitle);
}

void UserPreferences::setPriority(const QString &movieTitle, int priority) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& movie : watchLater) {
        if (movie.title == movieTitle) {
            movie.priority = priority;
            break;
        }
    }
}

void UserPreferences::addNote(const QString &movieTitle, const QString &note) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& movie : watchLater) {
        if (movie.title == movieTitle) {
            movie.notes = note;
            break;
        }
    }
}

void UserPreferences::setPlannedDate(const QString &movieTitle, const QDate &date) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& movie : watchLater) {
        if (movie.title == movieTitle) {
            movie.plannedDate = date;
            break;
        }
    }
}

void UserPreferences::markAsViewed(const QString &movieTitle) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& movie : watchLater) {
        if (movie.title == movieTitle) {
            movie.viewed = true;
            addLike(movieTitle);  // Automáticamente añade a "Like"
            break;
        }
    }
    // Elimina la película de "Ver mas tarde"
    watchLater.erase(std::remove_if(watchLater.begin(), watchLater.end(),
                                    [&movieTitle](const WatchLaterMovie& m) { return m.title == movieTitle; }),
                     watchLater.end());
}

std::vector<QString> UserPreferences::getLikes() const {
    std::lock_guard<std::mutex> lock(mutex);
    return likes;
}

std::vector<WatchLaterMovie> UserPreferences::getWatchLater() const {
    std::lock_guard<std::mutex> lock(mutex);
    return watchLater;
}

void UserPreferences::sortWatchLater(const QString &criterion) {
    std::lock_guard<std::mutex> lock(mutex);
    if (criterion == "title") {
        std::sort(watchLater.begin(), watchLater.end(),
                  [](const WatchLaterMovie& a, const WatchLaterMovie& b) { return a.title < b.title; });
    } else if (criterion == "priority") {
        std::sort(watchLater.begin(), watchLater.end(),
                  [](const WatchLaterMovie& a, const WatchLaterMovie& b) { return a.priority > b.priority; });
    } else if (criterion == "date") {
        std::sort(watchLater.begin(), watchLater.end(),
                  [](const WatchLaterMovie& a, const WatchLaterMovie& b) { return a.plannedDate < b.plannedDate; });
    }
}


