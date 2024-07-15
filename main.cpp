#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "MovieSearcher.h"
#include "UserPreferences.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString filePath = "mpst_fulldatadr_clean.csv";
    MovieSearcher searcher(filePath);
    UserPreferences userPreferences;

    int opcion;
    QString keyword;
    std::vector<QStringList> foundMovies;

    QTextStream qin(stdin);
    QTextStream qout(stdout);

    do {
        qout << "\n--- MENU ---\n";
        qout << "1. Buscar película por letras\n";
        qout << "2. Buscar película por tags (géneros)\n";
        qout << "3. Ver películas 'Like'\n";
        qout << "4. Ver películas 'Ver más tarde'\n";
        qout << "5. Salir\n";
        qout << "Seleccione una opción: " << Qt::flush;
        qin >> opcion;

        switch (opcion) {
            case 1:
                qout << "Introduzca letras para buscar películas: " << Qt::flush;
                qin >> keyword;
                foundMovies = searcher.searchMovieByLetters(keyword);
                break;
            case 2:
                qout << "Introduzca un tag para buscar películas: " << Qt::flush;
                qin >> keyword;
                foundMovies = searcher.searchMovieByTags(keyword);
                break;
            case 3:
                qout << "\n--- Películas 'Like' ---\n";
                for (const QString &title : userPreferences.getLikes()) {
                    qout << title << Qt::endl;
                }
                foundMovies.clear();
                break;
            case 4:
                qout << "\n--- Películas 'Ver más tarde' ---\n";
                for (const QString &title : userPreferences.getWatchLater()) {
                    qout << title << Qt::endl;
                }
                foundMovies.clear();
                break;
            case 5:
                qout << "Saliendo del programa...\n";
                break;
            default:
                qout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }

        if (!foundMovies.empty()) {
            qout << "\n--- Películas encontradas ---\n";
            for (size_t i = 0; i < foundMovies.size(); ++i) {
                qout << i + 1 << ". " << foundMovies[i][1] << Qt::endl; // Mostrar título de la película
            }

            int selection;
            do {
                qout << "Seleccione una película por su número: " << Qt::flush;
                qin >> selection;
            } while (selection < 1 || selection > static_cast<int>(foundMovies.size()));

            qout << "Seleccionó la película: " << foundMovies[selection - 1][1] << Qt::endl;

            qout << "1. Like\n";
            qout << "2. Ver más tarde\n";
            qout << "Seleccione una opción: " << Qt::flush;
            int subOption;
            qin >> subOption;

            switch (subOption) {
                case 1:
                    userPreferences.addLike(foundMovies[selection - 1][1]);
                    break;
                case 2:
                    userPreferences.addWatchLater(foundMovies[selection - 1][1]);
                    break;
                default:
                    qout << "Opción no válida.\n";
                    break;
            }

            foundMovies.clear(); // Limpiar la lista después de procesarla
        }

    } while (opcion != 5);

    return a.exec();
}
