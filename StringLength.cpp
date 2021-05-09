#include "BaseTask.h"

struct StringLengthTask : public BaseTask<StringLengthTask>
{
    std::string getPathImpl() const { return "../0.String"; }

    std::string run(const std::string& input) { return std::to_string(input.length()); }
};

GENERATE_TEST(StringLength)
