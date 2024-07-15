#ifndef UNTITLED19_USERPREFERENCES_H
#define UNTITLED19_USERPREFERENCES_H

#include <QString>
#include <vector>
#include <set>

class UserPreferences {
public:
    void addLike(const QString &title);
    void addWatchLater(const QString &title);
    std::set<QString> getLikes() const;
    std::set<QString> getWatchLater() const;

private:
    std::set<QString> likes;
    std::set<QString> watchLater;
};

#endif