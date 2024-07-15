#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "MovieSearcher.h"
#include "UserPreferences.h"
#include "MovieNotifier.h"
#include "UserNotifier.h"

void printMenu();
void printMovies(const std::vector<QStringList> &movies, int startIndex);
void printMovieDetails(const QStringList &movie);
void handleSearchByLetters(MovieSearcher &searcher, UserPreferences* userPreferences, MovieNotifier &notifier);
void handleSearchByTags(MovieSearcher &searcher, UserPreferences* userPreferences, MovieNotifier &notifier);
void handleViewLikes(UserPreferences* userPreferences, MovieSearcher &searcher,MovieNotifier &notifier);
void handleViewWatchLater(UserPreferences* userPreferences, MovieSearcher &searcher);

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString filePath = "mpst_fulldatadr_clean.csv";
    MovieSearcher searcher(filePath);
    UserPreferences* userPreferences = UserPreferences::getInstance();

    // Solicitar el nombre del usuario
    std::cout << "Por favor, ingrese su nombre: ";
    std::string username;
    std::getline(std::cin, username);

    MovieNotifier movieNotifier;
    UserNotifier userNotifier(QString::fromStdString(username));

    movieNotifier.addObserver(&userNotifier);


    int opcion;
    do {
        printMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                handleSearchByLetters(searcher, userPreferences, movieNotifier);
                break;
            case 2:
                handleSearchByTags(searcher, userPreferences, movieNotifier);
                break;
            case 3:
                handleViewLikes(userPreferences, searcher, movieNotifier);
                break;
            case 4:
                handleViewWatchLater(userPreferences,searcher);
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

void handleSearchByLetters(MovieSearcher &searcher, UserPreferences* userPreferences, MovieNotifier &notifier) {
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
                notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
            } else if (action == 2) {
                userPreferences->addWatchLater(foundMovies[selectedIndex - 1][1]);
                notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
            }
        }
    }
}

void handleSearchByTags(MovieSearcher &searcher, UserPreferences* userPreferences, MovieNotifier &notifier) {
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
                notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
            } else if (action == 2) {
                userPreferences->addWatchLater(foundMovies[selectedIndex - 1][1]);
                notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
            }
        }
    }
}

void handleViewLikes(UserPreferences* userPreferences, MovieSearcher &searcher, MovieNotifier &notifier) {
    auto likedMovies = userPreferences->getLikes();
    if (likedMovies.empty()) {
        std::cout << "No hay peliculas en 'Like'.\n";
    } else {
        while (true) {
            std::cout << "\nPeliculas en 'Like':\n";
            for (size_t i = 0; i < likedMovies.size(); ++i) {
                std::cout << (i + 1) << ". " << likedMovies[i].toStdString() << std::endl;
            }
            std::cout << "Seleccione una pelicula para ver mas detalles o buscar similares por tags (0 para volver al menu principal): ";
            int selectedLike;
            std::cin >> selectedLike;

            if (selectedLike == 0) {
                break;
            }

            if (selectedLike > 0 && selectedLike <= static_cast<int>(likedMovies.size())) {
                QString selectedMovie = likedMovies[selectedLike - 1];
                while (true) {
                    std::cout << "\nSelecciono: " << selectedMovie.toStdString() << std::endl;
                    std::cout << "1. Ver informacion de la película\n";
                    std::cout << "2. Ver peliculas similares por tag\n";
                    std::cout << "3. Volver a la lista de 'Like'\n";
                    std::cout << "4. Volver al Menu principal\n";
                    int likeAction;
                    std::cin >> likeAction;
                    if (likeAction == 1) {
                        printMovieDetails(searcher.getMovieDetails(selectedMovie));
                    } else if (likeAction == 2) {
                        QString tag = searcher.getFirstTag(selectedMovie);
                        auto foundMovies = searcher.searchMovieByTags(tag, 0);
                        while (!foundMovies.empty()) {
                            printMovies(foundMovies, 0);
                            std::cout << "\nSeleccione una pelicula por su numero, ingrese 0 para ver mas resultados, o -1 para volver: ";
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
                                while (true) {
                                    std::cout << "\n1. Agregar pelicula a Like\n";
                                    std::cout << "2. Agregar pelicula a ver mas tarde\n";
                                    std::cout << "3. Volver a la opcion anterior\n";
                                    std::cout << "4. Volver al MENU\n";
                                    int choice;
                                    std::cin >> choice;
                                    if (choice == 1) {
                                        userPreferences->addLike(foundMovies[selectedIndex - 1][1]);
                                        notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
                                        std::cout << "Pelicula agregada a Like.\n";
                                    } else if (choice == 2) {
                                        userPreferences->addWatchLater(foundMovies[selectedIndex - 1][1]);
                                        notifier.notifyObservers(foundMovies[selectedIndex - 1][1]);
                                        std::cout << "Pelicula agregada a Ver mas tarde.\n";
                                    } else if (choice == 3) {
                                        break;
                                    } else if (choice == 4) {
                                        return;
                                    }
                                }
                            }
                        }
                    } else if (likeAction == 3) {
                        break;
                    } else if (likeAction == 4) {
                        return;
                    }
                }
            }
        }
    }
}

void handleViewWatchLater(UserPreferences* userPreferences, MovieSearcher &searcher) {
    auto watchLaterMovies = userPreferences->getWatchLater();
    if (watchLaterMovies.empty()) {
        std::cout << "No hay peliculas en 'Ver mas tarde'.\n";
    } else {
        while (true) {
            std::cout << "\nPeliculas en 'Ver mas tarde':\n";
            for (size_t i = 0; i < watchLaterMovies.size(); ++i) {
                std::cout << (i + 1) << ". " << watchLaterMovies[i].title.toStdString()
                          << " (Prioridad: " << watchLaterMovies[i].priority
                          << ", Fecha planeada: " << watchLaterMovies[i].plannedDate.toString("dd/MM/yyyy").toStdString() << ")\n";
            }
            std::cout << "\n1. Seleccionar pelicula\n";
            std::cout << "2. Ordenar lista\n";
            std::cout << "3. Volver al menu principal\n";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Seleccione el numero de la pelicula: ";
                int movieChoice;
                std::cin >> movieChoice;
                if (movieChoice > 0 && movieChoice <= static_cast<int>(watchLaterMovies.size())) {
                    WatchLaterMovie& selectedMovie = watchLaterMovies[movieChoice - 1];
                    while (true) {
                        std::cout << "\nPelicula: " << selectedMovie.title.toStdString() << "\n";
                        std::cout << "1. Ver detalles\n";
                        std::cout << "2. Establecer prioridad\n";
                        std::cout << "3. Agregar nota\n";
                        std::cout << "4. Establecer fecha para ver\n";
                        std::cout << "5. Marcar como vista\n";
                        std::cout << "6. Volver a la lista\n";
                        int action;
                        std::cin >> action;
                        if (action == 1) {
                            printMovieDetails(searcher.getMovieDetails(selectedMovie.title));
                        } else if (action == 2) {
                            std::cout << "Ingrese la prioridad (1-5): ";
                            int priority;
                            std::cin >> priority;
                            userPreferences->setPriority(selectedMovie.title, priority);
                        } else if (action == 3) {
                            std::cout << "Ingrese la nota: ";
                            std::string note;
                            std::cin.ignore();
                            std::getline(std::cin, note);
                            userPreferences->addNote(selectedMovie.title, QString::fromStdString(note));
                        } else if (action == 4) {
                            std::cout << "Ingrese la fecha (DD/MM/YYYY): ";
                            std::string dateStr;
                            std::cin >> dateStr;
                            QDate date = QDate::fromString(QString::fromStdString(dateStr), "dd/MM/yyyy");
                            userPreferences->setPlannedDate(selectedMovie.title, date);
                        } else if (action == 5) {
                            userPreferences->markAsViewed(selectedMovie.title);
                            std::cout << "Pelicula marcada como vista y movida a 'Like'.\n";
                            break;
                        } else if (action == 6) {
                            break;
                        }
                    }
                }
            } else if (choice == 2) {
                std::cout << "Ordenar por:\n";
                std::cout << "1. Titulo\n";
                std::cout << "2. Prioridad\n";
                std::cout << "3. Fecha planeada\n";
                int sortChoice;
                std::cin >> sortChoice;
                if (sortChoice == 1) {
                    userPreferences->sortWatchLater("title");
                } else if (sortChoice == 2) {
                    userPreferences->sortWatchLater("priority");
                } else if (sortChoice == 3) {
                    userPreferences->sortWatchLater("date");
                }
            } else if (choice == 3) {
                break;
            }
            watchLaterMovies = userPreferences->getWatchLater();  // Actualizar la lista después de posibles cambios
        }
    }
}

