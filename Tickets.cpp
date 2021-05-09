#include "BaseTask.h"

struct TicketsTask : public BaseTask<TicketsTask>
{
    std::string getPathImpl() const { return "../1.Tickets"; }

    std::string run(const std::string& input)
    {
        const std::uint8_t N = std::atoi(input.c_str());

        std::vector<std::uint32_t> sumPrev(N * 9 + 1, 0);
        std::fill(sumPrev.begin(), sumPrev.begin() + 10, 1);

        std::vector<std::uint32_t> sum = sumPrev;
        for (std::uint8_t num = 1; num < N; ++num) {
            std::uint8_t limit = (num + 1) * 9 - 8;
            for (std::uint8_t i = 1; i < 10; ++i) {
                for (std::uint8_t j = i, k = 0; j < limit + i; ++j, ++k) {
                    sum[j] += sumPrev[k] == 0 ? 1 : sumPrev[k];
                }
            }
            sumPrev = sum;
        }

        unsigned long long res = 0;
        for (size_t i = 0; i < sumPrev.size(); ++i) {
            res += (unsigned long)sumPrev[i] * (unsigned long)sumPrev[i];
        }

        return std::to_string(res);
    }
};

GENERATE_TEST(Tickets)
