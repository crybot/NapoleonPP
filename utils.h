#ifndef UTILS_H
#define UTILS_H
#include "defines.h"
#include "constants.h"
#include <string>
#include <vector>
#include <cmath>

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
            int RelativeRank(Color, int);
            int MirrorSquare(int);
            int Distance(int, int);
            int Parse(std::string);
            std::string ToAlgebraic(Napoleon::Square);
        }

        namespace BitBoard
        {
            bool IsBitSet(Napoleon::BitBoard, int);
            void Display(Napoleon::BitBoard);
            void SetBit(Napoleon::BitBoard&, unsigned int);
            std::string ToString(Napoleon::BitBoard);

            int PopCount(Napoleon::BitBoard);
            int BitScanForward(Napoleon::BitBoard);
            int BitScanForwardReset(Napoleon::BitBoard&);
            int BitScanReverse(Napoleon::BitBoard);
            Napoleon::BitBoard SouthFill(Napoleon::BitBoard);
        }

        namespace Piece
        {
            Byte GetPiece(char);
            char GetInitial(Byte);
            char GetInitial(Napoleon::Piece);
            Color GetOpposite(Color);
        }

        namespace Math
        {
            // visual studio does not provide log2 function
            double Log2(double);
        }

        namespace String
        {
           void Split(std::vector<std::string> &, const std::string &, char);
        }

        INLINE void BitBoard::SetBit(Napoleon::BitBoard& bitboard, unsigned int sq)
        {
            bitboard |= (static_cast<Napoleon::BitBoard>(1) << sq);
        }

#if defined(__GNUC__) && defined(__LP64__)
        INLINE int BitBoard::BitScanForward(Napoleon::BitBoard bitBoard)
        {
            __asm__("bsfq %0, %0": "=r"(bitBoard): "0" (bitBoard) );
            return bitBoard;
        }

        INLINE int BitBoard::BitScanForwardReset(Napoleon::BitBoard& bitBoard)
        {
            Napoleon::BitBoard index;
            __asm__("bsfq %1, %0": "=r"(index): "rm"(bitBoard) );

            bitBoard &= (bitBoard - 1);

            return  index;
        }

#elif defined(__GNUC__)
        INLINE int BitBoard::BitScanForward(Napoleon::BitBoard bitBoard)
        {
            return __builtin_ctzll(bitBoard);
        }

        INLINE int BitBoard::BitScanForwardReset(Napoleon::BitBoard& bitBoard)
        {
            Napoleon::BitBoard bb = bitBoard;
            bitBoard &= (bitBoard - 1);

            return __builtin_ctzll(bb);
        }


#elif defined(_MSC_VER) && defined(_WIN64)
        INLINE int BitBoard::BitScanForward(Napoleon::BitBoard bitBoard)
        {
            unsigned long index;
            _BitScanForward64(&index, bitBoard);

            return (int)index;
        }

        INLINE int BitBoard::BitScanForwardReset(Napoleon::BitBoard& bitBoard)
        {
            unsigned long index;
            _BitScanForward64(&index, bitBoard);

            bitBoard &= (bitBoard - 1);

            return (int)index;
        }
#else
        INLINE int BitBoard::BitScanForward(Napoleon::BitBoard bitBoard)
        {
            return Constants::DeBrujinTable[((bitBoard & -bitBoard) * Constants::DeBrujinValue) >> 58];
        }

        INLINE int BitBoard::BitScanForwardReset(Napoleon::BitBoard& bitBoard)
        {
            Napoleon::BitBoard bb = bitBoard;
            bitBoard &= (bitBoard - 1);

            return Constants::DeBrujinTable[((bb & -bb) * Constants::DeBrujinValue) >> 58];
        }
#endif

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

        INLINE Napoleon::BitBoard BitBoard::SouthFill(Napoleon::BitBoard bitboard)
        {
            bitboard |= bitboard >> 8;
            bitboard |= bitboard >> 16;
            bitboard |= bitboard >> 32;
            return bitboard;
        }

        inline int Square::GetA1H8DiagonalIndex(int file, int rank)
        {
            return 7 + rank - file;
        }

        inline int Square::GetA1H8DiagonalIndex(int squareIndex)
        {
            return 7 + GetRankIndex(squareIndex) - GetFileIndex(squareIndex);
        }

        inline int Square::GetH1A8AntiDiagonalIndex(int file, int rank)
        {
            return rank + file;
        }

        inline int Square::GetH1A8AntiDiagonalIndex(int squareIndex)
        {
            return GetRankIndex(squareIndex) + GetFileIndex(squareIndex);
        }

        inline int Square::GetFileIndex(int squareIndex)
        {
            return squareIndex & 7;
        }

        inline int Square::GetRankIndex(int squareIndex)
        {
            return squareIndex >> 3;
        }

        inline int Square::GetSquareIndex(int file, int rank)
        {
            return file + 8 * rank;
        }

        inline int Square::MirrorSquare(int square)
        {
            return square ^ 56;
        }

        inline int Square::Distance(int sq1, int sq2)
        {
            int f1, f2, r1, r2;
            f1 = GetFileIndex(sq1);
            f2 = GetFileIndex(sq2);
            r1 = GetRankIndex(sq1);
            r2 = GetRankIndex(sq2);
            return std::max(std::abs(r1 - r2), std::abs(f1 - f2));
        }

        inline Color Piece::GetOpposite(Color color)
        {
            return Color(1 ^ color);
        }

        inline int Square::RelativeRank(Color color, int rank)
        {
            return color == PieceColor::White ? rank : 7 - rank;
        }
    }
}
#endif // UTILS_H
