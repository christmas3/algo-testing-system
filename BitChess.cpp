#include "MultilineResultBaseTask.h"

static std::uint8_t popcnt(std::uint64_t bits)
{
    std::uint8_t count = 0;
    while (bits > 0) {
        ++count;
        bits &= bits - 1;
    }

    return count;
}

struct KingTask : public MultilineResultBaseTask<KingTask>
{
    std::string getPathImpl() const { return "../0.BITS/1.BitboardKing"; }

    std::vector<std::uint64_t> run(const std::vector<std::string>& input)
    {
        std::uint8_t pos = std::atoi(input[0].c_str());

        std::uint64_t noA = 0xfefefefefefefefe;
        std::uint64_t noH = 0x7f7f7f7f7f7f7f7f;
        std::uint64_t king = 1ull << pos;
        std::uint64_t kingA = noA & king;
        std::uint64_t kingH = noH & king;
        // clang-format off
        std::uint64_t mask = ~king & ((kingA << 7) | (king << 8) | (kingH << 9) |
                                      (kingA >> 1) |               (kingH << 1) |
                                      (kingA >> 9) | (king >> 8) | (kingH >> 7));
        // clang-format on

        return { popcnt(mask), mask };
    }
};

GENERATE_TEST(King, std::uint64_t)

struct HorseTask : public MultilineResultBaseTask<HorseTask>
{
    std::string getPathImpl() const { return "../0.BITS/2.BitboardHorse"; }

    std::vector<std::uint64_t> run(const std::vector<std::string>& input)
    {
        std::uint8_t pos = std::atoi(input[0].c_str());

        std::uint64_t horse = 1ull << pos;
        std::uint64_t noA = 0xfefefefefefefefe;
        std::uint64_t noHG = 0x3f3f3f3f3f3f3f3f;
        std::uint64_t noAB = 0xfcfcfcfcfcfcfcfc;
        std::uint64_t noH = 0x7f7f7f7f7f7f7f7f;
        std::uint64_t horseA = noA & horse;
        std::uint64_t horseAB = noAB & horse;
        std::uint64_t horseH = noH & horse;
        std::uint64_t horseHG = noHG & horse;
        // clang-format off
        std::uint64_t mask = /*~horse &*/ ((horseA << 15) | (horseH << 17) |
                                       (horseAB << 6) | (horseH << 10) |
                                       (horseA >> 10) | (horseHG >> 6) |
                                       (horseA >> 17) | (horseH >> 15));
        // clang-format on

        return { popcnt(mask), mask };
    }
};

GENERATE_TEST(Horse, std::uint64_t)

struct RookTask : public MultilineResultBaseTask<RookTask>
{
    std::string getPathImpl() const { return "../0.BITS/3.BitboardRook"; }

    std::vector<std::uint64_t> run(const std::vector<std::string>& input)
    {
        std::uint8_t pos = std::atoi(input[0].c_str());

        std::uint64_t rook = 1ull << pos;
        std::uint64_t mask = moveUp(rook) | moveSide(rook);

        return { popcnt(mask), mask };
    }

    static std::uint64_t moveUp(std::uint64_t bits)
    {
        std::uint64_t mask[] = { 0x0101010101010101, 0x0202020202020202, 0x0404040404040404, 0x0808080808080808 };

        for (auto i = 0; i < 4; ++i) {
            if (mask[i] & bits) {
                return ~bits & (mask[i] | bits);
            }
            std::uint64_t mask2 = mask[i] << 4;
            if (mask2 & bits) {
                return ~bits & (mask2 | bits);
            }
        }

        return bits;
    }

    static std::uint64_t moveSide(std::uint64_t bits)
    {
        std::uint64_t mask = 0xff;
        for (auto i = 0; i < 8; ++i) {
            if (mask & bits) {
                return ~bits & (mask | bits);
            }
            mask <<= 8;
        }
        return bits;
    }
};

GENERATE_TEST(Rook, std::uint64_t)

struct BishopTask : public MultilineResultBaseTask<BishopTask>
{
    std::string getPathImpl() const { return "../0.BITS/4.BitboardBishop"; }

    std::vector<std::uint64_t> run(const std::vector<std::string>& input)
    {
        std::uint8_t pos = std::atoi(input[0].c_str());

        std::uint64_t bishop = 1ull << pos;

        std::uint64_t mask = moveDiag(bishop, 0x8040201008040201) | moveDiag(bishop, 0x0102040810204080);

        return { popcnt(mask), mask };
    }

    static std::uint64_t moveDiag(std::uint64_t bits, std::uint64_t mask)
    {
        std::uint64_t maskMove = mask;

        while (maskMove) {
            if (bits & maskMove) {
                return ~bits & (maskMove | bits);
            }
            maskMove >>= 8;
        }

        maskMove = mask << 8;
        while (maskMove) {
            if (bits & maskMove) {
                return ~bits & (maskMove | bits);
            }
            maskMove <<= 8;
        }

        return bits;
    }
};

GENERATE_TEST(Bishop, std::uint64_t)

struct QueenTask : public MultilineResultBaseTask<QueenTask>
{
    std::string getPathImpl() const { return "../0.BITS/5.BitboardQueen"; }

    std::vector<std::uint64_t> run(const std::vector<std::string>& input)
    {
        std::uint8_t pos = std::atoi(input[0].c_str());

        std::uint64_t queen = 1ull << pos;

        std::uint64_t mask = RookTask::moveUp(queen) | RookTask::moveSide(queen) | BishopTask::moveDiag(queen, 0x8040201008040201) |
                             BishopTask::moveDiag(queen, 0x0102040810204080);

        return { popcnt(mask), mask };
    }
};

GENERATE_TEST(Queen, std::uint64_t)
