#include "BaseTask.h"

#include <string>

struct FiboRecursionTask : public BaseTask<FiboRecursionTask>
{
    std::string getPathImpl() const { return "../4.Fibo"; }

    mpz_class run(const std::vector<std::string>& input)
    {
        std::uint64_t N = std::atol(input[0].c_str());

        return calc(N);
    }

    mpz_class calc(std::uint32_t nr)
    {
        if (nr <= 1)
            return nr;
        return calc(nr - 1) + calc(nr - 2);
    }
};

GENERATE_TEST(FiboRecursion, mpz_class)

struct FiboIterationTask : public BaseTask<FiboIterationTask>
{
    std::string getPathImpl() const { return "../4.Fibo"; }

    mpz_class run(const std::vector<std::string>& input)
    {
        std::uint64_t N = std::atol(input[0].c_str());

        mpz_class arr[] = { 0, 1 };

        mpz_class res = 0;

        if (N <= 1)
            res = arr[N];
        else {
            while (N-- > 1) {
                res = arr[0] + arr[1];
                arr[0] = arr[1];
                arr[1] = res;
            }
        }
        return res;
    }
};

GENERATE_TEST(FiboIteration, mpz_class)

struct FiboGoldenRatioTask : public BaseTask<FiboGoldenRatioTask>
{
    std::string getPathImpl() const { return "../4.Fibo"; }

    mpf_class run(const std::vector<std::string>& input)
    {
        std::uint64_t N = std::atol(input[0].c_str());

        mpf_class sqrtFive(5, N);
        sqrtFive = sqrt(sqrtFive);

        mpf_class ratio(1, N);
        ratio += sqrtFive;
        ratio /= 2;

        mpf_class res(0, N);
        mpf_pow_ui(res.get_mpf_t(), ratio.get_mpf_t(), N);
        res /= sqrtFive;
        res += mpf_class(0.5);
        res = floor(res);

        return res;
    }
};

GENERATE_TEST(FiboGoldenRatio, mpf_class)

struct FiboMatrixTask : public BaseTask<FiboMatrixTask>
{
    std::string getPathImpl() const { return "../4.Fibo"; }

    mpz_class run(const std::vector<std::string>& input)
    {
        std::uint64_t N = std::atol(input[0].c_str());

        if (N <= 1)
            return N;

        N -= 1;
        SimpleMatrix res;
        SimpleMatrix base({ { 1, 1 }, { 1, 0 } });
        for (; N > 1; N >>= 1) {
            if (N & 1) {
                res *= base;
            }
            base *= base;
        }
        res *= base;

        return res[0][0];
    }

    class SimpleMatrix
    {
    public:
        typedef std::vector<mpz_class> ValueType;

        SimpleMatrix()
            : m_{ { 1, 0 }, { 0, 1 } }
        {
        }

        explicit SimpleMatrix(std::vector<std::vector<mpz_class>>&& m)
            : m_(std::move(m))
        {
        }

        SimpleMatrix& operator*=(const SimpleMatrix& rhs)
        {
            SimpleMatrix tmp({ { 0, 0 }, { 0, 0 } });
            for (std::uint8_t i = 0; i < 2; ++i) {
                for (std::uint8_t j = 0; j < 2; ++j) {
                    for (std::uint8_t k = 0; k < 2; ++k) {
                        tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j];
                    }
                }
            }
            std::swap(*this, tmp);
            return *this;
        }

        ValueType& operator[](int i) { return m_[i]; };

    private:
        std::vector<std::vector<mpz_class>> m_;
    };
};

GENERATE_TEST(FiboMatrix, mpz_class)
