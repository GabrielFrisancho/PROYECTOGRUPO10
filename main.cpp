#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "MovieSearcher.h"
#include "UserPreferences.h"

void printMenu();
void printMovies(const std::vector<QStringList> &movies, int startIndex);
void printMovieDetails(const QStringList &movie);
void handleSearchByLetters(MovieSearcher &searcher, UserPreferences* userPreferences);
void handleSearchByTags(MovieSearcher &searcher, UserPreferences* userPreferences);
void handleViewLikes(UserPreferences* userPreferences, MovieSearcher &searcher);
void handleViewWatchLater(UserPreferences* userPreferences);

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString filePath = "mpst_fulldatadr_clean.csv";
    MovieSearcher searcher(filePath);
    UserPreferences* userPreferences = UserPreferences::getInstance();

    int opcion;
    do {
        printMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                handleSearchByLetters(searcher, userPreferences);
                break;
            case 2:
                handleSearchByTags(searcher, userPreferences);
                break;
            case 3:
                handleViewLikes(userPreferences, searcher);
                break;
            case 4:
                handleViewWatchLater(userPreferences);
                break;
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);

    return a.exec();
}

void printMenu() {
    std::cout << "\n--- MENU ---\n";
    std::cout << "1. Buscar pelicula por letras\n";
    std::cout << "2. Buscar pelicula por tags (generos)\n";
    std::cout << "3. Ver peliculas 'Like'\n";
    std::cout << "4. Ver peliculas 'Ver mas tarde'\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

void printMovies(const std::vector<QStringList> &movies, int startIndex) {
    std::cout << "\n--- Peliculas encontradas ---\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << (startIndex + i + 1) << ". " << movies[i][1].toStdString() << std::endl;
    }
}

void printMovieDetails(const QStringList &movie) {
    std::cout << "\nSelecciono la pelicula:\n";
    std::cout << "IMDB ID: " << movie[0].toStdString() << std::endl;
    std::cout << "Title: " << movie[1].toStdString() << std::endl;
    std::cout << "Plot Synopsis: " << movie[2].toStdString() << std::endl;
    std::cout << "Tags: " << movie[3].toStdString() << std::endl;
    std::cout << "Split: " << movie[4].toStdString() << std::endl;
    std::cout << "Synopsis Source: " << movie[5].toStdString() << std::endl;
}

void handleSearchByLetters(MovieSearcher &searcher, UserPreferences* userPreferences) {
    std::string keyword;
    std::cout << "Introduzca letras para buscar peliculas: ";
    std::cin >> keyword;
    auto foundMovies = searcher.searchMovieByLetters(QString::fromStdString(keyword), 0);

    while (!foundMovies.empty()) {
        printMovies(foundMovies, 0);
        std::cout << "\nSeleccione una pelicula por su numero, ingrese 0 para ver mas resultados, o -1 para volver al menu: ";
        int selectedIndex;
        std::cin >> selectedIndex;
        if (selectedIndex == -1) {
            break;
        } else if (selectedIndex == 0) {
            static int startIndex = 5;
            foundMovies = searcher.searchMovieByLetters(QString::fromStdString(keyword), startIndex);
            startIndex += 5;
        } else if (selectedIndex > 0 && selectedIndex <= static_cast<int>(foundMovies.size())) {
            printMovieDetails(foundMovies[selectedIndex - 1]);
            std::cout << "1. Agregar a 'Like'\n";
            std::cout << "2. Agregar a 'Ver mas tarde'\n";
            std::cout << "3. Volver al menu principal\n";
            int action;
            std::cin >> action;
            if (action == 1) {
                userPreferences->addLike(foundMovies[selectedIndex - 1][1]);
            } else if (action == 2) {
                userPreferences->addWatchLater(foundMovies[selectedIndex - 1][1]);
            }
        }
    }
}

void handleSearchByTags(MovieSearcher &searcher, UserPreferences* userPreferences) {
    std::string keyword;
    std::cout << "Introduzca tags para buscar: ";
    std::cin >> keyword;
    auto foundMovies = searcher.searchMovieByTags(QString::fromStdString(keyword), 0);

    while (!foundMovies.empty()) {
        printMovies(foundMovies, 0);
        std::cout << "\nSeleccione una pelicula por su numero, ingrese 0 para ver mas resultados, o -1 para volver al menu: ";
        int selectedIndex;
        std::cin >> selectedIndex;
        if (selectedIndex == -1) {
            break;
        } else if (selectedIndex == 0) {
            static int startIndex = 5;
            foundMovies = searcher.searchMovieByTags(QString::fromStdString(keyword), startIndex);
            startIndex += 5;
        } else if (selectedIndex > 0 && selectedIndex <= static_cast<int>(foundMovies.size())) {
            printMovieDetails(foundMovies[selectedIndex - 1]);
            std::cout << "1. Agregar a 'Like'\n";
            std::cout << "2. Agregar a 'Ver más tarde'\n";
            std::cout << "3. Volver al menu principal\n";
            int action;
            std::cin >> action;
            if (action == 1) {
                userPreferences->addLike(foundMovies[selectedIndex - 1][1]);
            } else if (action == 2) {
                userPreferences->addWatchLater(foundMovies[selectedIndex - 1][1]);
            }
        }
    }
}

void handleViewLikes(UserPreferences* userPreferences, MovieSearcher &searcher) {
    auto likedMovies = userPreferences->getLikes();
    if (likedMovies.empty()) {
        std::cout << "No hay peliculas en 'Like'.\n";
    } else {
        std::cout << "\nPeliculas en 'Like':\n";
        for (size_t i = 0; i < likedMovies.size(); ++i) {
            std::cout << (i + 1) << ". " << likedMovies[i].toStdString() << std::endl;
        }
        std::cout << "Seleccione una pelicula para ver mas detalles o buscar similares por tags: ";
        int selectedLike;
        std::cin >> selectedLike;
        if (selectedLike > 0 && selectedLike <= static_cast<int>(likedMovies.size())) {
            QString selectedMovie = likedMovies[selectedLike - 1];
            std::cout << "\nSelecciono: " << selectedMovie.toStdString() << std::endl;
            std::cout << "1. Ver informacion de la película\n";
            std::cout << "2. Ver peliculas similares por tag\n";
            int likeAction;
            std::cin >> likeAction;
            if (likeAction == 1) {
                printMovieDetails(searcher.getMovieDetails(selectedMovie));
            } else if (likeAction == 2) {
                QString tag = searcher.getFirstTag(selectedMovie);
                auto foundMovies = searcher.searchMovieByTags(tag, 0);
                while (!foundMovies.empty()) {
                    printMovies(foundMovies, 0);
                    std::cout << "\nSeleccione una pelicula por su numero, ingrese 0 para ver mas resultados, o -1 para volver al menu: ";
                    int selectedIndex;
                    std::cin >> selectedIndex;
                    if (selectedIndex == -1) {
                        break;
                    } else if (selectedIndex == 0) {
                        static int startIndex = 5;
                        foundMovies = searcher.searchMovieByTags(tag, startIndex);
                        startIndex += 5;
                    } else if (selectedIndex > 0 && selectedIndex <= static_cast<int>(foundMovies.size())) {
                        printMovieDetails(foundMovies[selectedIndex - 1]);
                    }
                }
            }
        }
    }
}

void handleViewWatchLater(UserPreferences* userPreferences) {
    auto watchLaterMovies = userPreferences->getWatchLater();
    if (watchLaterMovies.empty()) {
        std::cout << "No hay peliculas en 'Ver mas tarde'.\n";
    } else {
        std::cout << "\nPeliculas en 'Ver mas tarde':\n";
        for (size_t i = 0; i < watchLaterMovies.size(); ++i) {
            std::cout << (i + 1) << ". " << watchLaterMovies[i].toStdString() << std::endl;
        }
    }
}
