#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

#include <array>
#include <memory>
#include "../pieces/Piece.h"

namespace chess{

class Board {
    std::array<shared_ptr<Piece>> data;
public:
    Board();
    bool movePiece();
    shared_ptr<Piece> getPiece();
    void putPiece(std::string pieceType, unsignedrowrow, uns                            
                    
            
}{
            
        }
    }cold 
};

}

#endif
