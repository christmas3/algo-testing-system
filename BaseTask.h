#pragma once

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include <gmpxx.h>

#define GENERATE_TEST(Name, Type)                                                 \
    struct Name##Test : public BaseTest                                           \
    {                                                                             \
    };                                                                            \
    static Name##Task task##Name;                                                 \
    TEST_P(Name##Test, Calculate##Name) { task##Name.runTest<Type>(GetParam()); } \
    INSTANTIATE_TEST_SUITE_P(Name##Suit, Name##Test, testing::ValuesIn(task##Name.getTestParams()));

#define GENERATE_TEST_NAMESPACE(Name, Type, Namespace)                                                  \
    struct Namespace##Name##Test : public BaseTest                                                      \
    {                                                                                                   \
    };                                                                                                  \
    static Name##Task task##Name;                                                                       \
    TEST_P(Namespace##Name##Test, Calculate##Namespace##Name) { task##Name.runTest<Type>(GetParam()); } \
    INSTANTIATE_TEST_SUITE_P(Namespace##Name##Suit, Namespace##Name##Test, testing::ValuesIn(task##Name.getTestParams()));

#define TimeLapse(code, time, result)                     \
    {                                                     \
        auto begin_t = std::clock();                      \
        result = code;                                    \
        auto end_t = std::clock();                        \
        time = (float)(end_t - begin_t) / CLOCKS_PER_SEC; \
    }

#define TimeLapseWithoutResult(code, time)                \
    {                                                     \
        auto begin_t = std::clock();                      \
        code;                                             \
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
    //    EXPECT_EQ(result, val);
    EXPECT_TRUE(result == val);
}
template<>
inline void compareResult<double>(double& result, double& val)
{
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

template<>
inline std::uint64_t convertResult<std::uint64_t>(const std::string& result)
{
    try {
        size_t pos;
        return std::stoull(result, &pos);
    }
    catch (...) {
    }
    return 0;
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

void readFile(std::string* buf, const std::string& p, size_t size);

std::vector<TestParams> readTestParams(const char* path);

template<typename T>
struct BaseTask
{
    template<typename D>
    void runTest(const TestParams& param)
    {
        D result;
        auto paramVec = splitString(param.input);
        if (derived()->needTimeLapse()) {
            double timeVal = 0;
            TimeLapse(derived()->run(paramVec), timeVal, result);
            std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;
        }
        else {
            result = derived()->run(paramVec);
        }
        D expected = convertResult<D>(param.result.c_str());
        compareResult(result, expected);
    }

    std::vector<TestParams> getTestParams() { return readTestParams(derived()->getPathImpl().c_str()); }

protected:
    T* derived() { return static_cast<T*>(this); }

private:
    [[nodiscard]] bool needTimeLapse() const { return true; }
};

struct BaseTest : public testing::TestWithParam<TestParams>
{
};
