#pragma once

#include "BaseTask.h"

template<typename T>
struct MultilineResultBaseTask : public BaseTask<T>
{
    template<typename D>
    void runTest(const TestParams& param)
    {
        double timeVal = 0;
        std::vector<D> calculated;
        auto paramVec = splitString(param.input);
        TimeLapse(BaseTask<T>::derived()->run(paramVec), timeVal, calculated);
        auto splitRes = splitString(param.result);

        ASSERT_EQ(calculated.size(), splitRes.size());
        for (size_t i = 0; i < calculated.size(); ++i) {
            D expected = convertResult<D>(splitRes[i]);
            compareResult(calculated[i], expected);
        }
        std::cerr << std::fixed << "time passed: " << timeVal << " seconds" << std::endl;
    }

private:
    //    T* derived() { return static_cast<T*>(this); }
};
