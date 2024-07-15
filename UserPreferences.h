#ifndef USERPREFERENCES_H
#define USERPREFERENCES_H

#include <vector>
#include <QString>
#include <mutex>

class UserPreferences {
public:
    static UserPreferences* getInstance();
    void addLike(const QString &movieTitle);
    void addWatchLater(const QString &movieTitle);
    std::vector<QString> getLikes() const;
    std::vector<QString> getWatchLater() const;

private:
    UserPreferences() = default;
    static UserPreferences* instance;
    std::vector<QString> likes;
    std::vector<QString> watchLater;
    mutable std::mutex mutex;
};

#endif // USERPREFERENCES_H
