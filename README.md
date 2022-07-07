# $$Ajedrez^{n}$$
## Proyecto Computacional
### Programación III - 2021 - 1

[![N|Solid](https://utec.edu.pe/sites/all/themes/utec_theme/LOGO_UTEC.png)](https://utec.edu.pe/carreras/ciencia-de-la-computacion)

| Participante                      | Papel    |
| --------------------------------- | -------: |
| Joaquín Francisco Jordán O'Connor | Backend  |
| Renato Aurelio Cernades Ames      | Backend  |
| Nicolás Mateo Arroyo Chávez       | Backend  |
| Josué Mauricio Arriaga Colchado   | Frontend |
| José Rafael Chachi Rodriguez      | Frontend |

## Descripción del proyecto
$$Ajedrez^{n}$$ es un juego de ajedrez distinto al tradicional, pues ofrece infinitas posibilidades de juego. Según la elección del usuario, la aplicación generará un ambiente con reglas únicas y diferentes al ajedrez original.

## Guía de intalación

1. Clonar nuestro repositorio a la carpeta deseada.
2. Instalar la librería [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) para el correcto funcionamiento de la UI dentro de la carpeta del proyecto.
3. (**Opcional**) Instalar el framework [Google Test](https://github.com/google/googletest) para poder realizar los test a la aplicación.

## Guía de uso

- ya no hay menu pipipi

## Licencia de uso

Proyecto realizado bajo la licencia [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0). 

## Características principales

- Interfaz gráfica para el tablero implementado con la librería SFML.
- [Inteligencia artifical](https://www.cs.cornell.edu/boom/2004sp/ProjectArch/Chess/algorithms.html) generada por computadora que servirá como contrincante para el jugador implementada con el algoritmo [_depth-limited minimax_](https://cs.stanford.edu/people/eroberts/courses/soco/projects/2003-04/intelligent-search/minimax.html) y optimizado con [_alpha-beta pruning_](https://cs.stanford.edu/people/eroberts/courses/soco/projects/2003-04/intelligent-search/alphabeta.html).
- Implementación del programa haciendo uso de la Programación Orientada a Objetos.
- Creación de partidas personalizadas con reglas en base al dígito elegido por el usuario.

## Test de aplicación

- Board Test: Permite comprobar que el tablero se ha podido iniciar correctamente con todas las piezas necesarias.
- Checkmate Test: Evalua si funciona el jaque mate al realizar una serie de movimientos con las piezas ya testeadas con anterioridad.

## Bibliografía



