# Programación III: Proyecto Final (2024-1)

## Integrantes

-Mikael Quinto Ramos

-Adrian Urbina Mendoza

-Camila Espinoza Cabrera

-Gabriel Frisancho Gálvez

## Plataforma de Streaming PELIS ++

PELIS++ es una aplicación en C++ utilizando la biblioteca Qt para gestionar y buscar películas basadas en un archivo CSV. La aplicación permite a los usuarios buscar películas por título o tags, así como gestionar listas de "Me gusta" y "Ver más tarde". Este proyecto utiliza varios patrones de diseño de software para una estructura y funcionalidad mejoradas.

## Descripción del Proyecto

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

- Qt 5.x o superior
- CMake 3.x o superior
- Un compilador C++ compatible (como CLION, GCC o Clang)

## USO
* Al ejecutar la aplicación, se te pedirá que ingreses tu nombre de usuario. Después, se mostrará un menú con las siguientes opciones:
1. **Buscar películas por letras: Permite buscar películas cuyo título contenga un conjunto de letras especificadas.**
2. **Buscar películas por tags: Permite buscar películas por tags (géneros).**
3. **Ver películas marcadas como "Me gusta": Muestra las películas que has marcado como "Me gusta".**
4. **Ver películas marcadas para "Ver más tarde": Muestra las películas que has marcado para ver más tarde.**
5. **Salir: Termina la aplicación.**
