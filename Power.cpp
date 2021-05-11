#include "BaseTask.h"

#include <string>

struct PowerIterationTask : public BaseTask<PowerIterationTask>
{
    std::string getPathImpl() const { return "../3.Power"; }

    double run(const std::vector<std::string>& input)
    {
        char* end;
        auto A = std::strtod(input[0].c_str(), &end);
        auto N = std::strtod(input[1].c_str(), &end);
        double res = 1;
        while (N-- > 0) {
            res *= A;
        }

        return res;
    }
};

GENERATE_TEST(PowerIteration, double)

struct PowerPostMultipleTask : public BaseTask<PowerPostMultipleTask>
{
    std::string getPathImpl() const { return "../3.Power"; }

    double run(const std::vector<std::string>& input)
    {
        char* end;
        auto A = std::strtod(input[0].c_str(), &end);
        std::uint64_t N = std::atol(input[1].c_str());

        double res = 1;
        double curRes = A;
        std::uint64_t pos = 2;

        while (pos < N) {
            curRes *= curRes;
            pos <<= 1;
        }
        if (curRes > A) {
            pos >>= 1;
            while (pos++ < N) {
                curRes *= A;
            }
            res = curRes;
        }

        return res;
    }
};

GENERATE_TEST(PowerPostMultiple, double)

struct PowerBinaryDecomposeTask : public BaseTask<PowerBinaryDecomposeTask>
{
    std::string getPathImpl() const { return "../3.Power"; }

    double run(const std::vector<std::string>& input)
    {
        char* end;
        auto A = std::strtod(input[0].c_str(), &end);
        std::uint64_t N = std::atol(input[1].c_str());
        double res = 1;

        while (N) {
            if (N & 1) {
                res *= A;
            }
            if (!(N >>= 1)) {
                break;
            }
            A *= A;
        }

        return res;
    }
};

GENERATE_TEST(PowerBinaryDecompose, double)
