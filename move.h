#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "defines.h"

namespace Napoleon
{
    class Move
    {

    public:

        const Byte FromSquare;
        const Byte ToSquare;
        const Byte PieceMoved; // overloaded to manage castle (KING)
        const Byte PieceCaptured;
        const Byte PiecePromoted;// overloaded to manage castle (ROOK) // overloaded to manage en-passant (PAWN)

        Move(Byte, Byte, Byte, Byte, Byte);

        bool operator== (const Move&) const;
        bool operator!= (const Move&) const;
        bool IsNull() const;
        bool IsCapture() const;
        bool IsCastle() const;
        bool IsCastleOO() const;
        bool IsCastleOOO() const;
        bool IsPromotion() const;
        bool IsEnPassant() const;
        std::string ToAlgebraic() const;

    };

}
#endif // MOVE_H
