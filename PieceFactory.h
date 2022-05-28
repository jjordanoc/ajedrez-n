#ifndef PROYECTO_PIECEFACTORY_H
#define PROYECTO_PIECEFACTORY_H

#include <unordered_map>
#include <functional>
#include <memory>
#include "Piece.h"

using namespace std;

template<typename T>
using smart_ptr = shared_ptr<T>;

enum Color {
    black,
    white
};

class PieceFactory {
    unordered_map<string, function<smart_ptr<Piece>(Color)>> callbacks;
protected:

};


#endif //PROYECTO_PIECEFACTORY_H
