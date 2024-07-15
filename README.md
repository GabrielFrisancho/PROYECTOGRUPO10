# Programación III: Proyecto Final (2024-1)

## Integrantes

-Mikael Quinto Ramos

-Adrian Urbina Mendoza

-Camila Espinoza Cabrera

-Gabriel Frisancho Gálvez

## Plataforma de Streaming PELIS ++

PELIS++ es una aplicación en C++ utilizando la biblioteca Qt para gestionar y buscar películas basadas en un archivo CSV. La aplicación permite a los usuarios buscar películas por título o tags, así como gestionar listas de "Me gusta" y "Ver más tarde". Este proyecto utiliza varios patrones de diseño de software para una estructura y funcionalidad mejoradas.

## Base de Datos usada en el programa 

* El programa lee la base de datos en forma **.csv**. La base de datos actualizada y limpia , con el proposito de que nuestro programa pueda leer la data sin problemas , puede ser descargada desde el siguiente [link](https://drive.google.com/file/d/1EwILGKEVmbmWsGaDXd0gj9F6sE48oxh5/view?usp=sharing).

## Características

- **Búsqueda de películas por letras**
- **Búsqueda de películas por tags**
- **Visualización de detalles de películas**
- **Gestión de listas de "Me gusta"**
- **Gestión de listas de "Ver más tarde"**
- **Notificaciones al usuario sobre selecciones de películas**

## Estructura del Proyecto

El proyecto está organizado de la siguiente manera:

- **main.cpp**: Punto de entrada de la aplicación. Maneja la lógica principal de interacción con el usuario y el flujo de la aplicación.
- **MovieSearcher**: Clase responsable de buscar películas en el archivo CSV.
- **UserPreferences**: Clase Singleton que gestiona las preferencias del usuario, incluyendo listas de "Me gusta" y "Ver más tarde".
- **MovieNotifier**: Clase que implementa el patrón Observador para notificar a los observadores sobre cambios en el estado de las películas.
- **UserNotifier**: Clase que actúa como un observador y notifica al usuario sobre cambios en las selecciones de películas.

## Instalación

### Requisitos

- Qt 6.x o superior
- CMake 3.x o superior
- Un compilador C++ compatible (como CLION, GCC o Clang)

## USO
* Al ejecutar la aplicación, se te pedirá que ingreses tu nombre de usuario. Después, se mostrará un menú con las siguientes opciones:
1. **Buscar películas por letras: Permite buscar películas cuyo título contenga un conjunto de letras especificadas.**
2. **Buscar películas por tags: Permite buscar películas por tags (géneros).**
3. **Ver películas marcadas como "Me gusta": Muestra las películas que has marcado como "Me gusta".**
4. **Ver películas marcadas para "Ver más tarde": Muestra las películas que has marcado para ver más tarde.**
5. **Salir: Termina la aplicación.**

## Detalles Técnicos

### Estructura de Clases

#### `main.cpp`

El archivo `main.cpp` es el punto de entrada de la aplicación y contiene la lógica principal de interacción con el usuario. Aquí se configuran las instancias de las clases principales y se gestiona el flujo de la aplicación a través de un menú interactivo.

##### Inicialización

- **`QApplication`**: Instancia de la aplicación Qt.
- **`MovieSearcher`**: Clase responsable de buscar películas en el archivo CSV.
- **`UserPreferences`**: Clase Singleton que gestiona las preferencias del usuario.
- **`MovieNotifier`**: Clase que implementa el patrón Observador para notificar a los observadores sobre cambios.
- **`UserNotifier`**: Observador que notifica al usuario sobre cambios en las selecciones de películas.

##### Menú Principal

Se presenta un menú que permite al usuario elegir entre diferentes acciones. Dependiendo de la opción seleccionada, se llaman las funciones correspondientes para buscar películas, ver listas de "Me gusta" y "Ver más tarde", y salir de la aplicación.

#### `MovieSearcher`

Clase responsable de buscar películas en el archivo CSV. Proporciona métodos para buscar películas por letras y por tags, así como para obtener detalles de películas específicas.

- **`searchByLetters(const QString &letters)`**: Busca películas cuyos títulos contengan las letras especificadas.
- **`searchByTags(const QString &tags)`**: Busca películas que tengan los tags especificados.
- **`getMovieDetails(const QString &movieId)`**: Obtiene los detalles de una película específica por su ID.

#### `UserPreferences`

Clase Singleton que gestiona las preferencias del usuario, incluyendo las listas de "Me gusta" y "Ver más tarde". Asegura que solo haya una instancia de las preferencias del usuario en toda la aplicación.

- **`getInstance()`**: Obtiene la instancia única de `UserPreferences`.
- **`addLike(const QString &movieId)`**: Añade una película a la lista de "Me gusta".
- **`addWatchLater(const QString &movieId)`**: Añade una película a la lista de "Ver más tarde".
- **`getLikes()`**: Obtiene la lista de películas marcadas como "Me gusta".
- **`getWatchLater()`**: Obtiene la lista de películas marcadas para "Ver más tarde".

#### `MovieNotifier`

Clase que implementa el patrón Observador. Permite notificar a los observadores sobre cambios en el estado de las películas seleccionadas por el usuario.

- **`addObserver(UserNotifier *observer)`**: Añade un observador a la lista de observadores.
- **`removeObserver(UserNotifier *observer)`**: Elimina un observador de la lista de observadores.
- **`notifyObservers(const QString &message)`**: Notifica a todos los observadores sobre un cambio.

#### `UserNotifier`

Clase que actúa como observador de `MovieNotifier`. Notifica al usuario sobre cambios en las selecciones de películas.

- **`update(const QString &message)`**: Recibe las notificaciones del `MovieNotifier` y las muestra al usuario.

### Funciones Auxiliares

- **`handleSearchByLetters(MovieSearcher &searcher)`**: Gestiona la búsqueda de películas por letras.
  - Solicita al usuario que ingrese letras para buscar.
  - Llama a `searchByLetters` del `MovieSearcher`.
  - Muestra los resultados de la búsqueda.

- **`handleSearchByTags(MovieSearcher &searcher)`**: Gestiona la búsqueda de películas por tags.
  - Solicita al usuario que ingrese tags para buscar.
  - Llama a `searchByTags` del `MovieSearcher`.
  - Muestra los resultados de la búsqueda.

- **`handleViewLikes(UserPreferences &preferences)`**: Muestra las películas que el usuario ha marcado como "Me gusta".
  - Obtiene la lista de "Me gusta" de `UserPreferences`.
  - Muestra la lista de películas marcadas.

- **`handleViewWatchLater(UserPreferences &preferences)`**: Muestra las películas que el usuario ha marcado para "Ver más tarde".
  - Obtiene la lista de "Ver más tarde" de `UserPreferences`.
  - Muestra la lista de películas marcadas.

### Patrones de Diseño

El proyecto utiliza varios patrones de diseño de software para mejorar la estructura y la funcionalidad:

1. **Singleton**: Implementado en `UserPreferences` para asegurar una única instancia de preferencias del usuario en toda la aplicación.
2. **Observador**: Implementado en `MovieNotifier` y `UserNotifier` para notificar a los observadores sobre cambios en el estado de las películas seleccionadas por el usuario.

### Algoritmos

- **Eficiencia de Tiempo y Espacio**: Se han considerado criterios de eficiencia en el uso de algoritmos, optimizando tanto tiempo como espacio.
- **Algoritmos de la Librería Estándar**: Uso intensivo de algoritmos existentes de la librería estándar de C++ para operaciones comunes.
- **Algoritmos Creativos**: Implementación de algoritmos creativos y eficientes, como búsquedas optimizadas, que manejan grandes volúmenes de información con complejidades mayores a lineales (nlog).

#### Ejemplo de Algoritmo de Complejidad Mayor a Lineal
En la clase `MovieSearcher`, se utiliza un algoritmo de búsqueda binaria para encontrar películas, cuya complejidad es **O(log n)**, mayor a la complejidad lineal.

### QT (F.zip)
Archivos .qml.ui
