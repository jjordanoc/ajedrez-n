#ifndef PROYECTO_PIECEFACTORY_H
#define PROYECTO_PIECEFACTORY_H

#include <functional>
#include <memory>
#include <unordered_map>
// Librerias locales
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "global/Global.h"


namespace chess {

    using Callback = std::function<std::shared_ptr<chess::Piece>(Color color)>;

    class PieceFactory {
        std::unordered_map<std::string, Callback> callbacks;

    public:
        PieceFactory() {
            attach("King", [](const Color &color) { return std::make_shared<King>(color); });
            attach("Queen", [](const Color &color) { return std::make_shared<Queen>(color); });
            attach("Knight", [](const Color &color) { return std::make_shared<Knight>(color); });
            attach("Bishop", [](const Color &color) { return std::make_shared<Bishop>(color); });
            attach("Rook", [](const Color &color) { return std::make_shared<Rook>(color); });
            attach("Pawn", [](const Color &color) { return std::make_shared<Pawn>(color); });
        }
        std::shared_ptr<chess::Piece> create(const std::string &key, const Color &color) {
            return callbacks.at(key)(color);
        }
        void attach(const std::string &key, const Callback &constructor) {
            callbacks.insert({key, constructor});
        }
    };

}// namespace chess


#endif
