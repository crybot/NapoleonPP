#ifndef UTILS_H
#define UTILS_H
#include "defines.h"
#include "constants.h"
#include <string>

namespace Napoleon
{
    namespace Utils
    {
        namespace Square
        {
            int GetA1H8DiagonalIndex(int, int);
            int GetA1H8DiagonalIndex(int);
            int GetH1A8AntiDiagonalIndex(int, int);
            int GetH1A8AntiDiagonalIndex(int);
            int GetFileIndex(int);
            int GetRankIndex(int);
            int GetSquareIndex(int, int);
            int Parse(std::string);
            std::string ToAlgebraic(int);
        }

        namespace BitBoard
        {
            bool IsBitSet(Napoleon::BitBoard, int);
            void Display(Napoleon::BitBoard);

            int PopCount(Napoleon::BitBoard bitBoard);
            int BitScanForward( Napoleon::BitBoard bitBoard);
            int BitScanForwardReset(Napoleon::BitBoard& bitBoard);
        }

        namespace Piece
        {
            char GetInitial(Byte);
            char GetInitial(Napoleon::Piece);
            Byte GetOpposite(Byte);
        }

        INLINE int BitBoard::BitScanForward(Napoleon::BitBoard bitBoard)
        {
#ifdef __GNUG__
            return __builtin_ctzll(bitBoard); // conta il numero di 0 precedenti al primo bit piu` significativo

#elif defined(_MSC_VER)
            unsigned long index;
            _BitScanForward64(&index, bitBoard);

            return (int)index;
#else
            return Constants::DeBrujinTable[((bitBoard & -bitBoard) * Constants::DeBrujinValue) >> 58];
#endif
        }

        INLINE int BitBoard::BitScanForwardReset(Napoleon::BitBoard& bitBoard)
        {
            Napoleon::BitBoard bb = bitBoard;
            bitBoard &= (bitBoard - 1);
#ifdef __GNUG__
            return __builtin_ctzll(bb); // conta il numero di 0 precedenti al primo bit piu` significativo

#elif defined(_MSC_VER)
            unsigned long index;
            _BitScanForward64(&index, bb);

            return (int)index;
#else
            return Constants::DeBrujinTable[((bb & -bb) * Constants::DeBrujinValue) >> 58];
#endif
        }

        INLINE int BitBoard::PopCount(Napoleon::BitBoard bitBoard)
        {
#ifdef __GNUG__
            return __builtin_popcountll(bitBoard);
#else
            bitBoard -= ((bitBoard >> 1) & 0x5555555555555555UL);
            bitBoard = ((bitBoard >> 2) & 0x3333333333333333UL) + (bitBoard & 0x3333333333333333UL);
            bitBoard = ((bitBoard >> 4) + bitBoard) & 0x0F0F0F0F0F0F0F0FUL;
            return (int)((bitBoard * 0x0101010101010101UL) >> 56);
#endif
        }

        INLINE int Square::GetA1H8DiagonalIndex(int file, int rank)
        {
            return 7 + rank - file;
        }

        INLINE int Square::GetA1H8DiagonalIndex(int squareIndex)
        {
            return 7 + GetRankIndex(squareIndex) - GetFileIndex(squareIndex);
        }

        INLINE int Square::GetH1A8AntiDiagonalIndex(int file, int rank)
        {
            return rank + file;
        }

        INLINE int Square::GetH1A8AntiDiagonalIndex(int squareIndex)
        {
            return GetRankIndex(squareIndex) + GetFileIndex(squareIndex);
        }

        INLINE int Square::GetFileIndex(int squareIndex)
        {
            return squareIndex & 7;
        }

        INLINE int Square::GetRankIndex(int squareIndex)
        {
            return squareIndex >> 3;
        }

        INLINE int Square::GetSquareIndex(int file, int rank)
        {
            return file + 8 * rank;
        }

        INLINE Byte Piece::GetOpposite(Byte color)
        {
            return 1 ^ color;
        }
    }
}
#endif // UTILS_H
