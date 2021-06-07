#include <gtest/gtest.h>

#include "Sorting.h"

#define GENERATE_TEST_BUBBLE(Name) GENERATE_TEST_NAMESPACE(Name, std::string, Bubble)
#define GENERATE_TEST_INSERTION(Name) GENERATE_TEST_NAMESPACE(Name, std::string, Insertion)

namespace bubble {

GENERATE_TEST_BUBBLE(RandomSort)
GENERATE_TEST_BUBBLE(DigitsSort)
GENERATE_TEST_BUBBLE(SortedSort)
GENERATE_TEST_BUBBLE(ReversSort)
} // namespace bubble

namespace insertion {

GENERATE_TEST_INSERTION(RandomSort)
GENERATE_TEST_INSERTION(DigitsSort)
GENERATE_TEST_INSERTION(SortedSort)
GENERATE_TEST_INSERTION(ReversSort)
} // namespace insertion
