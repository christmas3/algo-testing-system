#pragma once

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include <gmpxx.h>

#define GENERATE_TEST(Name, Type)                                                 \
    struct Name##Test : public BaseTest                                           \
    {                                                                             \
    };                                                                            \
    static Name##Task task##Name;                                                 \
    TEST_P(Name##Test, Calculate##Name) { task##Name.runTest<Type>(GetParam()); } \
    INSTANTIATE_TEST_SUITE_P(Name##Suit, Name##Test, testing::ValuesIn(task##Name.getTestParams()));

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
void compareResult(T& result, T& val)
{
    EXPECT_EQ(result, val);
}
template<>
inline void compareResult<double>(double& result, double& val)
{
    std::cerr << "compareResult<double>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    EXPECT_FLOAT_EQ(result, val);
}
template<>
inline void compareResult<mpf_class>(mpf_class& result, mpf_class& val)
{
    mpf_set_prec(result.get_mpf_t(), val.get_prec());
    EXPECT_EQ(result, val);
}

template<typename T>
T convertResult(const std::string& result)
{
    return result;
}

template<>
inline double convertResult<double>(const std::string& result)
{
    char* end;
    return std::strtod(result.c_str(), &end);
}

template<>
inline mpz_class convertResult<mpz_class>(const std::string& result)
{
    mpz_class res;
    mpz_init(res.get_mpz_t());
    mpz_set_str(res.get_mpz_t(), result.c_str(), 10);
    return res;
}

template<>
inline mpf_class convertResult<mpf_class>(const std::string& result)
{
    mpf_class res(result.c_str());
    return res;
}

template<typename T>
struct BaseTask
{
    //    void runTestString(const TestParams& param)
    //    {
    //        double timeVal = 0;
    //        std::string result;
    //        TimeLapse(derived()->run(param.input), timeVal, result);
    //        EXPECT_EQ(param.result, result);
    //        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;
    //    }
    //
    //    void runTestDouble(const TestParams& param)
    //    {
    //        double timeVal = 0;
    //        double result;
    //        auto paramVec = splitString(param.input);
    //        TimeLapse(derived()->run(paramVec), timeVal, result);
    //        char* end;
    //        auto expected = std::strtod(param.result.c_str(), &end);
    //        EXPECT_FLOAT_EQ(expected, result);
    //        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;
    //    }

    template<typename D>
    void runTest(const TestParams& param)
    {
        double timeVal = 0;
        D result;
        auto paramVec = splitString(param.input);
        TimeLapse(derived()->run(paramVec), timeVal, result);
        D expected = convertResult<D>(param.result.c_str());
        compareResult(result, expected);

        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;
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

    static std::vector<std::string> splitString(const std::string& input)
    {
        std::vector<std::string> res;
        size_t begin = 0;
        auto end = input.find("\r\n");
        while (end != std::string::npos) {
            res.push_back(input.substr(begin, end));
            begin = end + 2;
            end = input.substr(begin).find("\r\n");
        }
        res.push_back(input.substr(begin));

        return res;
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
