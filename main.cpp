#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "MovieSearcher.h"
#include "UserPreferences.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString filePath = "mpst_fulldatadr_clean.csv";
    MovieSearcher searcher(filePath);
    UserPreferences* userPreferences = UserPreferences::getInstance();

    int opcion;
    std::string keyword;
    std::vector<QStringList> foundMovies;

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Buscar película por letras\n";
        std::cout << "2. Buscar película por tags (géneros)\n";
        std::cout << "3. Ver películas 'Like'\n";
        std::cout << "4. Ver películas 'Ver más tarde'\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Introduzca letras para buscar películas: ";
                std::cin >> keyword;
                foundMovies = searcher.searchMovieByLetters(QString::fromStdString(keyword));
                break;
            case 2:
                std::cout << "Introduzca un tag para buscar películas: ";
                std::cin >> keyword;
                foundMovies = searcher.searchMovieByTags(QString::fromStdString(keyword));
                break;
            case 3: {
                std::set<QString> likes = userPreferences->getLikes();
                std::cout << "\n--- Películas 'Like' ---\n";
                if (likes.empty()) {
                    std::cout << "No hay películas en 'Like'.\n";
                } else {
                    for (const QString &title : likes) {
                        std::cout << title.toStdString() << std::endl;
                    }
                }
                continue;
            }
            case 4: {
                std::set<QString> watchLater = userPreferences->getWatchLater();
                std::cout << "\n--- Películas 'Ver más tarde' ---\n";
                if (watchLater.empty()) {
                    std::cout << "No hay películas en 'Ver más tarde'.\n";
                } else {
                    for (const QString &title : watchLater) {
                        std::cout << title.toStdString() << std::endl;
                    }
                }
                continue;
            }
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo.\n";
                continue;
        }

        if (foundMovies.empty()) {
            std::cout << "\nNo se ha encontrado registros de la película, verifique si está escrita correctamente.\n";
        } else {
            std::cout << "\n--- Películas encontradas ---\n";
            for (size_t i = 0; i < foundMovies.size(); ++i) {
                std::cout << i + 1 << ". " << foundMovies[i][1].toStdString() << std::endl;
            }

            int selection;
            do {
                std::cout << "Seleccione una película por su número: ";
                std::cin >> selection;
            } while (selection < 1 || selection > static_cast<int>(foundMovies.size()));

            const QStringList &selectedMovie = foundMovies[selection - 1];
            std::cout << "\nSeleccionó la película:\n";
            std::cout << "IMDB ID: " << selectedMovie[0].toStdString() << std::endl;
            std::cout << "Title: " << selectedMovie[1].toStdString() << std::endl;
            std::cout << "Plot Synopsis: " << selectedMovie[2].toStdString() << std::endl;
            std::cout << "Tags: " << selectedMovie[3].toStdString() << std::endl;
            std::cout << "Split: " << selectedMovie[4].toStdString() << std::endl;
            std::cout << "Synopsis Source: " << selectedMovie[5].toStdString() << std::endl;

            int option;
            std::cout << "1. Like\n";
            std::cout << "2. Ver más tarde\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> option;

            if (option == 1) {
                userPreferences->addLike(selectedMovie[1]);
                std::cout << "Película añadida a 'Like'.\n";
            } else if (option == 2) {
                userPreferences->addWatchLater(selectedMovie[1]);
                std::cout << "Película añadida a 'Ver más tarde'.\n";
            } else {
                std::cout << "Opción no válida.\n";
            }
        }

    } while (opcion != 5);

    return a.exec();
}
