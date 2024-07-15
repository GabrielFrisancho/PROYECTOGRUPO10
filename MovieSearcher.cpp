#include "MovieSearcher.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MovieSearcher::MovieSearcher(const QString &filePath) : filePath(filePath) {
    readCSVFile();
}

std::vector<QStringList> MovieSearcher::searchMovieByLetters(const QString &letters, int startIndex) {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<QStringList> foundMovies;

    int count = 0;
    for (auto it = movieData.begin(); it != movieData.end(); ++it) {
        if (it->first.contains(letters, Qt::CaseInsensitive)) {
            if (count >= startIndex && count < startIndex + 5) {
                foundMovies.push_back(it->second);
            }
            ++count;
        }
    }

    return foundMovies;
}

std::vector<QStringList> MovieSearcher::searchMovieByTags(const QString &tags, int startIndex) {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<QStringList> foundMovies;

    int count = 0;
    int foundCount = 0;
    for (auto it = movieData.begin(); it != movieData.end(); ++it) {
        QStringList movieTags = it->second[3].split(';');
        for (const QString &tag : movieTags) {
            if (tag.trimmed().compare(tags, Qt::CaseInsensitive) == 0) {
                if (count >= startIndex && foundCount < 5) {
                    foundMovies.push_back(it->second);
                    ++foundCount;
                }
                ++count;
                break;
            }
        }
    }

    return foundMovies;
}

QStringList MovieSearcher::parseCSVLine(const QString &line) {
    QStringList result;
    bool inQuotes = false;
    QString currentField;

    for (QChar c : line) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            result.append(currentField);
            currentField.clear();
        } else {
            currentField.append(c);
        }
    }
    result.append(currentField);
    return result;
}

void MovieSearcher::readCSVFile() {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "No se pudo abrir el archivo CSV.";
        return;
    }

    QTextStream in(&file);
    QStringList headers;

    if (!in.atEnd()) {
        QString headerLine = in.readLine();
        headers = parseCSVLine(headerLine);
        qDebug() << "Headers:" << headers;
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList items = parseCSVLine(line);

        if (!items.isEmpty()) {
            QString title = items[1].toLower();
            movieData[title] = items;
        }
    }

    file.close();
}

QStringList MovieSearcher::getMovieDetails(const QString &title) const {
    auto it = movieData.find(title.toLower());
    if (it != movieData.end()) {
        return it->second;
    }
    return QStringList();
}

QString MovieSearcher::getFirstTag(const QString &title) const {
    auto it = movieData.find(title.toLower());
    if (it != movieData.end()) {
        QStringList tags = it->second[3].split(';');
        if (!tags.isEmpty()) {
            return tags[0].trimmed();
        }
    }
    return QString();
}

