#include "BaseTask.h"

#include <cmath>
#include <string>

struct PrimesSimpleATask : public BaseTask<PrimesSimpleATask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        std::uint32_t res = 0;
        for (std::uint32_t i = 2; i <= N; ++i) {
            if (isPrime(i)) {
                ++res;
            }
        }

        return std::to_string(res);
    }

    bool isPrime(std::uint32_t p)
    {
        std::uint32_t count = 0;
        for (std::uint32_t d = 1; d <= p; ++d) {
            if (p % d == 0) {
                ++count;
            }
        }
        return count == 2;
    }
};

GENERATE_TEST(PrimesSimpleA, std::string)

struct PrimesSimpleBTask : public BaseTask<PrimesSimpleBTask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        std::uint32_t res = 0;
        for (std::uint32_t i = 2; i <= N; ++i) {
            if (isPrime(i)) {
                ++res;
            }
        }

        return std::to_string(res);
    }

    bool isPrime(std::uint32_t p)
    {
        for (std::uint32_t d = 2; d < p; ++d) {
            if (p % d == 0) {
                return false;
            }
        }
        return true;
    }
};

GENERATE_TEST(PrimesSimpleB, std::string)

struct PrimesSimpleCTask : public BaseTask<PrimesSimpleCTask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        std::uint32_t res = 0;
        for (std::uint32_t i = 2; i <= N; ++i) {
            if (isPrime(i)) {
                ++res;
            }
        }

        return std::to_string(res);
    }

    bool isPrime(std::uint32_t p)
    {
        auto limit = p / 2;
        for (std::uint32_t d = 2; d <= limit; ++d) {
            if (p % d == 0) {
                return false;
            }
        }
        return true;
    }
};

GENERATE_TEST(PrimesSimpleC, std::string)

struct PrimesSimpleDTask : public BaseTask<PrimesSimpleDTask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        std::uint32_t res = 0;
        for (std::uint32_t i = 2; i <= N; ++i) {
            if (isPrime(i)) {
                ++res;
            }
        }

        return std::to_string(res);
    }

    bool isPrime(std::uint32_t p)
    {
        auto limit = static_cast<std::uint32_t>(std::sqrt(p));
        for (std::uint32_t d = 2; d <= limit; ++d) {
            if (p % d == 0) {
                return false;
            }
        }
        return true;
    }
};

GENERATE_TEST(PrimesSimpleD, std::string)

struct PrimesSimpleETask : public BaseTask<PrimesSimpleETask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        std::uint32_t res = 0;
        for (std::uint32_t i = 2; i <= N; ++i) {
            if (isPrime(i)) {
                ++res;
            }
        }

        return std::to_string(res);
    }

    bool isPrime(std::uint32_t p)
    {
        if (p == 2 || p == 3)
            return true;
        if (p % 2 == 0 || p % 3 == 0)
            return false;
        auto limit = static_cast<std::uint32_t>(std::sqrt(p));
        for (std::uint32_t d = 5; d <= limit; d += 6) {
            if (p % d == 0 || p % (d + 2) == 0) {
                return false;
            }
        }
        return true;
    }
};

GENERATE_TEST(PrimesSimpleE, std::string)

struct PrimesSimpleArrayTask : public BaseTask<PrimesSimpleArrayTask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        return std::to_string(primesCount(N));
    }

    std::uint32_t primesCount(std::uint32_t N)
    {
        if (N < 2)
            return 0;

        std::uint32_t count = 0;
        auto* primes = new std::uint16_t[N];
        primes[count++] = 2;

        for (std::uint32_t p = 3; p <= N; p += 2) {
            if (isPrime(p, primes, count)) {
                primes[count++] = p;
            }
        }

        delete[] primes;
        return count;
    }

    bool isPrime(std::uint32_t p, const std::uint16_t* primes, std::uint32_t count)
    {
        auto limit = static_cast<std::uint32_t>(std::sqrt(p));
        for (std::uint32_t i = 0; i < count && primes[i] <= limit; ++i) {
            if (p % primes[i] == 0) {
                return false;
            }
        }
        return true;
    }
};

GENERATE_TEST(PrimesSimpleArray, std::string)

struct PrimesEratosfenTask : public BaseTask<PrimesEratosfenTask>
{
    std::string getPathImpl() const { return "../5.Primes"; }

    std::string run(const std::vector<std::string>& input)
    {
        std::uint32_t N = std::atoi(input[0].c_str());

        return std::to_string(primesCount(N));
    }

    std::uint32_t primesCount(std::uint32_t N)
    {
        if (N < 2)
            return 0;

        std::uint32_t count = 0;
        auto* primes = new bool[N + 1]();
        for (std::uint32_t p = 2; p <= N; ++p) {
            if (!primes[p]) {
                ++count;
                if (p <= sqrt(N)) {
                    for (std::uint32_t i = p * p; i <= N; i += p) {
                        primes[i] = true;
                    }
                }
            }
        }

        delete[] primes;
        return count;
    }
};

GENERATE_TEST(PrimesEratosfen, std::string)
