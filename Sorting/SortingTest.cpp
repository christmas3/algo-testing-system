#include <gtest/gtest.h>

#include "Sorting.h"

#define GENERATE_TEST_BUBBLE(Name) GENERATE_TEST_NAMESPACE(Name, std::string, Bubble)
#define GENERATE_TEST_INSERTION(Name) GENERATE_TEST_NAMESPACE(Name, std::string, Insertion)
#define GENERATE_TEST_SHELL_FIRST(Name) GENERATE_TEST_NAMESPACE(Name, std::string, ShellFirst)

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

namespace shell_first {
GENERATE_TEST_SHELL_FIRST(RandomSort)
GENERATE_TEST_SHELL_FIRST(DigitsSort)
GENERATE_TEST_SHELL_FIRST(SortedSort)
GENERATE_TEST_SHELL_FIRST(ReversSort)
} // namespace shell_first
