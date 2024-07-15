#ifndef USERPREFERENCES_H
#define USERPREFERENCES_H

#include <vector>
#include <QString>
#include <QDate>
#include <mutex>

struct WatchLaterMovie {
    QString title;
    int priority;
    QString notes;
    QDate plannedDate;
    bool viewed;

    WatchLaterMovie(const QString& t) : title(t), priority(0), notes(""), plannedDate(QDate::currentDate()), viewed(false) {}
};

class UserPreferences {
public:
    static UserPreferences* getInstance();
    void addLike(const QString &movieTitle);
    void addWatchLater(const QString &movieTitle);
    void setPriority(const QString &movieTitle, int priority);
    void addNote(const QString &movieTitle, const QString &note);
    void setPlannedDate(const QString &movieTitle, const QDate &date);
    void markAsViewed(const QString &movieTitle);
    std::vector<QString> getLikes() const;
    std::vector<WatchLaterMovie> getWatchLater() const;
    void sortWatchLater(const QString &criterion);

private:
    UserPreferences() = default;
    static UserPreferences* instance;
    std::vector<QString> likes;
    std::vector<WatchLaterMovie> watchLater;
    mutable std::mutex mutex;
};

#endif // USERPREFERENCES_H
