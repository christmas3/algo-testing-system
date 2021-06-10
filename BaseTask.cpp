#include "BaseTask.h"

void readFile(std::string* buf, const std::string& p, size_t size)
{
    std::ifstream is{ p.c_str(), std::ios::in | std::ios::binary };
    if (!is) {
        return;
    }
    buf->reserve(size);
    buf->assign(std::istreambuf_iterator<char>{ is }, {});
    buf->erase(std::find_if(buf->rbegin(), buf->rend(), [](char ch) { return !std::isspace(ch); }).base(), buf->end());
}

std::vector<TestParams> readTestParams(const char* path)
{
    namespace fs = std::filesystem;

    std::vector<TestParams> result;
    fs::path testPath(path);
    for (size_t i = 0;; ++i) {
        std::string fileNamePrefix = "test." + std::to_string(i);
        fs::path fileInPath = testPath / std::string(fileNamePrefix + ".in");
        fs::path fileOutPath = testPath / std::string(fileNamePrefix + ".out");

        if (!fs::exists(fileInPath) || !fs::exists(fileOutPath)) {
            break;
        }
        result.emplace_back(TestParams{});

        readFile(&result.back().input, fileInPath.c_str(), fs::file_size(fileInPath));
        readFile(&result.back().result, fileOutPath.c_str(), fs::file_size(fileOutPath));
    }

    return result;
}
