#pragma once

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#define GENERATE_TEST(Name)                                           \
    struct Name##Test : public BaseTest                               \
    {                                                                 \
    };                                                                \
    static Name##Task task;                                           \
    TEST_P(Name##Test, Calculate##Name) { task.runTest(GetParam()); } \
    INSTANTIATE_TEST_SUITE_P(Name##Suit, Name##Test, testing::ValuesIn(task.getTestParams()));

#define TimeLapse(code, time, result)                     \
    {                                                     \
        auto begin_t = std::clock();                      \
        result = code;                                    \
        auto end_t = std::clock();                        \
        time = (float)(end_t - begin_t) / CLOCKS_PER_SEC; \
    }

struct TestParams
{
    std::string input;
    std::string result;
};

template<typename T>
struct BaseTask
{
    void runTest(const TestParams& param)
    {
        double timeVal = 0;
        std::string result;
        TimeLapse(derived()->run(param.input), timeVal, result);
        EXPECT_EQ(param.result, result);
        std::cerr << "time passed: " << timeVal << " seconds" << std::endl;
    }

    std::vector<TestParams> getTestParams()
    {
        namespace fs = std::filesystem;

        std::vector<TestParams> result;
        fs::path testPath(derived()->getPathImpl());
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

private:
    T* derived() { return static_cast<T*>(this); }
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
};

struct BaseTest : public testing::TestWithParam<TestParams>
{
};
