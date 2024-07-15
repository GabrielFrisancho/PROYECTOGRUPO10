#ifndef UNTITLED19_USERPREFERENCES_H // MODIFICAR DEPENDE DE TU TITULO DE PROYECTO
#define UNTITLED19_USERPREFERENCES_H 

#include <QString>
#include <vector>
#include <set>

class UserPreferences {
public:
    static UserPreferences* getInstance();
    void addLike(const QString &title);
    void addWatchLater(const QString &title);
    std::set<QString> getLikes() const;
    std::set<QString> getWatchLater() const;

private:
    UserPreferences() = default; // Constructor privado
    static UserPreferences* instance;
    std::set<QString> likes;
    std::set<QString> watchLater;
};

#endif //UNTITLED19_USERPREFERENCES_H //MODIFICAR DEPENDE DE TU TITULO DE PROYECTO
