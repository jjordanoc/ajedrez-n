#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

// Liberias de terceros
#include "iomanip"
#include <array>
#include <memory>
// Liberias locales
#include "../global/Global.h"
#include "../pieces/Piece.h"
#include "../pieces/PieceFactory.h"


namespace chess {
    using BoardType = std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE>;
    class Board {
        BoardType mainBoard;
        std::unique_ptr<chess::PieceFactory> pieceFactory;
        bool isMakingCastling = false;
        bool isMakingShortCastling = false;
        bool isMakingLongCastling = false;
    public:
        Board();
        void checkPawnPromotion(PosType newRow, PosType newCol);
        void checkCastling(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol);
        bool movePiece(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol);
        std::shared_ptr<Piece> getPiece(PosType row, PosType col);
        void putPiece(const std::string &pieceType, const Color &color, PosType row, PosType col);
        void print();
        void putKingChecked(const Color &color);
        bool isChecked(const Color &color);
        bool isCheckMate();
        BoardType &getBoardData() {
            return mainBoard;
        }
    };

}// namespace chess

#endif
