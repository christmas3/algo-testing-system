#include "BaseTask.h"

struct StringLengthTask : public BaseTask<StringLengthTask>
{
    std::string getPathImpl() const { return "../0.String"; }

    std::string run(const std::vector<std::string>& input) { return std::to_string(input[0].length()); }
};

GENERATE_TEST(StringLength, std::string)
