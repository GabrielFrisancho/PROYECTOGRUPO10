#ifndef UNTITLED19_MOVIESEARCHER_H
#define UNTITLED19_MOVIESEARCHER_H


#include <QString>
#include <QStringList>
#include <vector>
#include <map>
#include <mutex>

class MovieSearcher {
public:
    MovieSearcher(const QString &filePath);
    std::vector<QStringList> searchMovieByLetters(const QString &letters);
    std::vector<QStringList> searchMovieByTags(const QString &tags);

private:
    QString filePath;
    std::map<QString, QStringList> movieData;
    std::mutex mutex;

    QStringList parseCSVLine(const QString &line);
    void readCSVFile();
};

#endif //UNTITLED19_MOVIESEARCHER_H