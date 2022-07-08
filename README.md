# $$Ajedrez^{n}$$
## Proyecto Computacional
### Programación III - 2022 - 1

[![N|Solid](https://utec.edu.pe/sites/all/themes/utec_theme/LOGO_UTEC.png)](https://utec.edu.pe/carreras/ciencia-de-la-computacion)

|            Participante             |   Papel   |
|:-----------------------------------:|:---------:|
|  Joaquín Francisco Jordán O'Connor  |  Backend  |
|    Renato Aurelio Cernades Ames     |  Backend  |
|     Nicolás Mateo Arroyo Chávez     |  Backend  |
|   Josué Mauricio Arriaga Colchado   | Frontend  |
|    José Rafael Chachi Rodriguez     | Frontend  |

## Descripción del proyecto
$Ajedrez^{n}$ es un juego de ajedrez distinto al tradicional, pues ofrece infinitas posibilidades de juego. Según la elección del usuario, la aplicación generará un ambiente con reglas únicas y diferentes al ajedrez original.

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
- Con [2] se implementó una **inteligencia artifical** generada por computadora implementada con el algoritmo *__depth-limited minimax__* y optimizado con *__alpha-beta pruning__* de [1] que servirá como contrincante para el jugador.
- Implementación del programa haciendo uso de la Programación Orientada a Objetos.
- Creación de partidas personalizadas con reglas en base al dígito elegido por el usuario.

## Test de aplicación

- Board Test: Permite comprobar que el tablero se ha podido iniciar correctamente con todas las piezas necesarias.
- Checkmate Test: Evalua si funciona el jaque mate al realizar una serie de movimientos con las piezas ya testeadas con anterioridad.


## Autores

|                     <a target="_blank">**Joaquín Jordán**</a>                     |                           <a target="_blank">**Renato Cernades**</a>                            |                   <a target="_blank">**Josué Arriaga**</a>                    |                       <a target="_blank">**José Chachi**</a>                        |      <a target="_blank">**Nicolás Arroyo**</a>      |
|:---------------------------------------------------------------------------------:|:-----------------------------------------------------------------------------------------------:|:-----------------------------------------------------------------------------:|:-----------------------------------------------------------------------------------:|:---------------------------------------------------:|
|           ![Joaquín](https://avatars.githubusercontent.com/u/83974213)            |                   ![Renato](https://avatars.githubusercontent.com/u/83974266)                   |          ![Josué](https://avatars.githubusercontent.com/u/83974555)             |              ![José](https://avatars.githubusercontent.com/u/83974741)              |       ![Nicolás](https://avatars.githubusercontent.com/u/83975293)                                              |
| <a href="https://github.com/jjordanoc" target="_blank">`github.com/jjordanoc`</a> | <a href="https://github.com/RenatoCernades0107" target="_blank">`github.com/RenatoCernades`</a> | <a href="https://github.com/jmac-94" target="_blank">`github.com/jmac94`</a>  | <a href="https://github.com/JoseChachi" target="_blank">`github.com/JoseChachi`</a> |<a href="https://github.com/NicolasArroyo" target="_blank">`github.com/NicolasArroyo`</a>|

## Bibliografía

- [1] Standford, "Strategies and tactics for intelligent search", 2003. [Online]. Available: https://cs.stanford.edu/people/eroberts/courses/soco/projects/2003-04/intelligent-search/intro.html [Accessed: May. 3, 2022]
- [2] Cornell, "AI Chess Algorithms", 2004. [Online]. Available: https://www.cs.cornell.edu/boom/2004sp/ProjectArch/Chess/algorithms.html [Accessed: May. 8, 2022]

