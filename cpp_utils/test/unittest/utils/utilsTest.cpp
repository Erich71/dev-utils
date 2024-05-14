// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include <cstdint>
#include <stdexcept>

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/utils.hpp>

using namespace eprosima::utils;

/**
 * Test \c set_of_ptr_contains method for a set of pointers to integers
 *
 * Cases:
 *  empty set
 *  element with same ptr contained
 *  element contained
 *  element not contained
 *  nullptr not contained
 */
TEST(utilsTest, set_of_ptr_contains_int)
{
    // Create an empty set
    std::set<std::shared_ptr<int>> set;

    // Elements to add
    std::shared_ptr<int> ptr0 = std::make_shared<int>(0);
    std::shared_ptr<int> ptr1 = std::make_shared<int>(1);
    std::shared_ptr<int> ptr2 = std::make_shared<int>(2);
    std::shared_ptr<int> ptr3 = std::make_shared<int>(3);

    // Elements to look for
    std::shared_ptr<int> ptr_0b = ptr0; // same ptr
    std::shared_ptr<int> ptr_1b = std::make_shared<int>(1); // different ptr
    std::shared_ptr<int> ptr_4 = std::make_shared<int>(4);
    std::shared_ptr<int> ptr_null; // nullptr

    {
        // empty set
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_0b));
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_1b));
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_4));
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_null));
    }

    // Add elements to set
    set.insert(ptr0);
    set.insert(ptr1);
    set.insert(ptr2);
    set.insert(ptr3);

    {
        // element with same ptr contained
        ASSERT_EQ(ptr0, ptr_0b);
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_0b));
    }

    {
        // element contained
        ASSERT_NE(ptr1, ptr_1b);
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_1b));
    }

    {
        // element not contained
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_4));
    }

    {
        // nullptr not contained
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_null));
    }
}

/**
 * Test \c set_of_ptr_contains method for a set of pointers to integers that contains a nullptr
 *
 * Cases:
 *  nullptr contained
 *  element contained
 *  element not contained
 */
TEST(utilsTest, set_of_ptr_with_null_contains_int)
{
    // Create an empty set
    std::set<std::shared_ptr<int>> set;

    // Elements to add
    std::shared_ptr<int> ptr0 = std::make_shared<int>(0);
    std::shared_ptr<int> ptr1 = std::make_shared<int>(1);
    std::shared_ptr<int> ptr2 = std::make_shared<int>(2);
    std::shared_ptr<int> ptr3 = std::make_shared<int>(3);
    std::shared_ptr<int> ptrn; // nullptr

    // Elements to look for
    std::shared_ptr<int> ptr_0b = ptr0; // same ptr
    std::shared_ptr<int> ptr_1b = std::make_shared<int>(1); // different ptr
    std::shared_ptr<int> ptr_4 = std::make_shared<int>(4);
    std::shared_ptr<int> ptr_null_b = ptrn; // same direction as ptrn
    std::shared_ptr<int> ptr_null; // nullptr

    // Add elements
    set.insert(ptr0);
    set.insert(ptr1);
    set.insert(ptr2);
    set.insert(ptr3);
    set.insert(ptrn);

    {
        // nullptr contained
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_null_b));
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_null));
    }

    {
        // element contained
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_0b));
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_1b));
    }

    {
        // element not contained
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_4));
    }
}

/**
 * Test \c set_of_ptr_contains method for a set of pointers to string
 *
 * Cases:
 *  element contained
 *  element not contained
 */
TEST(utilsTest, set_of_ptr_contains_string)
{
    // Create an empty set
    std::set<std::shared_ptr<std::string>> set;

    // Elements to add
    std::shared_ptr<std::string> ptr_a = std::make_shared<std::string>("a");
    std::shared_ptr<std::string> ptr_barro = std::make_shared<std::string>("Barro");
    std::shared_ptr<std::string> ptr_with_spaces = std::make_shared<std::string>("String with spaces");
    std::shared_ptr<std::string> ptr_very_long_st = std::make_shared<std::string>(
        "I count him braver who overcomes his desires than him who conquers his enemies, "
        "for the hardest victory is over self. ― Aristotle"
        );

    // Add elements to set
    set.insert(ptr_a);
    set.insert(ptr_barro);
    set.insert(ptr_with_spaces);
    set.insert(ptr_very_long_st);

    // Elements to look for
    std::shared_ptr<std::string> ptr_ab = std::make_shared<std::string>("a");  // contained
    std::shared_ptr<std::string> ptr_b = std::make_shared<std::string>("Barro");  // contained
    std::shared_ptr<std::string> ptr_b2 = std::make_shared<std::string>("Barr");  // substring contained
    std::shared_ptr<std::string> ptr_spaces_b = std::make_shared<std::string>("Stringwithspaces"); // almost contained
    std::shared_ptr<std::string> ptr_4 = std::make_shared<std::string>("4"); // not contained

    {
        // element contained
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_ab));
        ASSERT_TRUE(set_of_ptr_contains(set, ptr_b));
    }

    {
        // element not contained
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_spaces_b));
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_b2));
        ASSERT_FALSE(set_of_ptr_contains(set, ptr_4));
    }
}

/**
 * Test \c are_set_of_ptr_equal method for a set of pointers to integers
 *
 * Each case is tested in both directions to check commutativity
 *
 * Cases:
 *  both empty set
 *  one empty set
 *  same elements
 *  different elements different size
 *  different elements same size
 *  different elements one with nullptr
 *  same elements with nullptr
 *  each with itself
 */
TEST(utilsTest, are_set_of_ptr_equal_int)
{
    // Create an empty set
    std::set<std::shared_ptr<int>> set1;
    std::set<std::shared_ptr<int>> set2;

    // Elements to add to set 1
    std::shared_ptr<int> ptra_0 = std::make_shared<int>(0);
    std::shared_ptr<int> ptra_1 = std::make_shared<int>(1);
    std::shared_ptr<int> ptra_2 = std::make_shared<int>(2);
    std::shared_ptr<int> ptra_3 = std::make_shared<int>(3);
    std::shared_ptr<int> ptra_4 = std::make_shared<int>(4);
    std::shared_ptr<int> ptra_n; // nullptr

    // Elements to add to set 2
    std::shared_ptr<int> ptrb_0 = ptra_0; // same object
    std::shared_ptr<int> ptrb_1 = std::make_shared<int>(1);
    std::shared_ptr<int> ptrb_2 = std::make_shared<int>(2);
    std::shared_ptr<int> ptrb_3 = std::make_shared<int>(3);
    std::shared_ptr<int> ptrb_4 = std::make_shared<int>(4);
    std::shared_ptr<int> ptrb_n; // nullptr

    {
        // both empty set
        ASSERT_TRUE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add elements to set 1
    set1.insert(ptra_0);
    set1.insert(ptra_1);
    set1.insert(ptra_2);

    {
        // one empty set
        ASSERT_FALSE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add elements to set 2
    set2.insert(ptrb_0);
    set2.insert(ptrb_1);
    set2.insert(ptrb_2);

    {
        // same elements
        ASSERT_TRUE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add elements to set 1
    set1.insert(ptra_3);

    {
        // different elements different size
        ASSERT_FALSE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add elements to set 2
    set2.insert(ptrb_4);

    {
        // different elements same size
        ASSERT_FALSE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add nullptr to set 1
    set1.insert(ptra_n);
    // Add 3 to set 2 so both has same size
    set2.insert(ptrb_3);

    {
        // different elements one with nullptr
        ASSERT_FALSE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    // Add nullptr to set 2
    set2.insert(ptrb_n);
    // Add 4 to set 1 so both has same elements
    set1.insert(ptra_4);

    {
        // same elements with nullptr
        ASSERT_TRUE(are_set_of_ptr_equal(set1, set2));
        ASSERT_EQ(are_set_of_ptr_equal(set1, set2), are_set_of_ptr_equal(set2, set1));
    }

    {
        // each with itself
        ASSERT_TRUE(are_set_of_ptr_equal(set1, set1));
        ASSERT_TRUE(are_set_of_ptr_equal(set2, set2));
    }
}

/**
 * Test \c to_lowercase call
 */
TEST(utilsTest, to_lowercase)
{
    // Uppercase
    {
        std::string str = "FOO";
        to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }
    // Invariant
    {
        std::string str = "foo";
        to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }
    // With non-letter characters
    {
        std::string str = "!_-.,FoO";
        to_lowercase(str);
        ASSERT_EQ(str, "!_-.,foo");
    }
    // Empty
    {
        std::string str = "";
        to_lowercase(str);
        ASSERT_EQ(str, "");
    }
}

/**
 * Test \c to_uppercase call
 */
TEST(utilsTest, to_uppercase)
{
    // Uppercase
    {
        std::string str = "FOO";
        to_uppercase(str);
        ASSERT_EQ(str, "FOO");
    }
    // Invariant
    {
        std::string str = "foo";
        to_uppercase(str);
        ASSERT_EQ(str, "FOO");
    }
    // With non-letter characters
    {
        std::string str = "!_-.,FoO";
        to_uppercase(str);
        ASSERT_EQ(str, "!_-.,FOO");
    }
    // Empty
    {
        std::string str = "";
        to_uppercase(str);
        ASSERT_EQ(str, "");
    }
}

/**
 * Test \c to_bytes call
 */
TEST(utilsTest, to_bytes)
{
    // VALID

    // Invariant
    {
        const std::string bytes_str = "100B";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 100ULL;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Lowercase
    {
        const std::string bytes_str = "123kb";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 123ULL * 1000;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Uppercase
    {
        const std::string bytes_str = "100MB";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 100ULL * 1000 * 1000;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Milibytes
    {
        const std::string bytes_str = "82GiB";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 82ULL * 1024 * 1024 * 1024;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Large
    {
        const std::string bytes_str = "742TB";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 742ULL * 1000 * 1000 * 1000 * 1000;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Extra Large
    {
        const std::string bytes_str = "51pib";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 51ULL * 1024 * 1024 * 1024 * 1024 * 1024;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Small decimal number
    {
        const std::string bytes_str = "1.50KB";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = 1ULL * 1000 + 500;
        ASSERT_EQ(bytes, bytes_expected);
    }
    // Large decimal number
    {
        const std::string bytes_str = "23.9999GB";
        const std::uint64_t bytes = to_bytes(bytes_str);
        const std::uint64_t bytes_expected = ((23ULL * 1000 + 999) * 1000 + 900) * 1000;
        ASSERT_EQ(bytes, bytes_expected);
    }

    // INVALID

    // Empty
    {
        const std::string bytes_str = "";
        ASSERT_THROW(to_bytes(bytes_str), std::invalid_argument);
    }
    // No unit
    {
        const std::string bytes_str = "100";
        ASSERT_THROW(to_bytes(bytes_str), std::invalid_argument);
    }
    // No number
    {
        const std::string bytes_str = "MB";
        ASSERT_THROW(to_bytes(bytes_str), std::invalid_argument);
    }
    // Invalid unit
    {
        const std::string bytes_str = "100G";
        ASSERT_THROW(to_bytes(bytes_str), std::invalid_argument);
    }
    // Number too large
    {
        const std::string bytes_str = "18446744073709551616PiB";
        ASSERT_THROW(to_bytes(bytes_str), std::invalid_argument);
    }
}

/**
 * Test \c from_bytes call
 */
TEST(utilsTest, from_bytes)
{
    // Zero
    {
        const std::uint64_t bytes = 0ULL;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "0B";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Bytes
    {
        const std::uint64_t bytes = 100ULL;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "100B";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Kilobytes
    {
        const std::uint64_t bytes = 555ULL * 1000 + 559;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "555.56KB";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Megabytes
    {
        const std::uint64_t bytes = (100ULL * 1000 + 104) * 1000;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "100.10MB";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Gigabytes
    {
        const std::uint64_t bytes = 82ULL * 1000 * 1000 * 1000;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "82GB";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Terabytes
    {
        const std::uint64_t bytes = 742ULL * 1000 * 1000 * 1000 * 1000;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "742TB";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
    // Extra Large
    {
        const std::uint64_t bytes = 12345ULL * 1000 * 1000 * 1000 * 1000 * 1000;
        const std::string bytes_str = from_bytes(bytes);
        const std::string bytes_str_expected = "12345PB";
        ASSERT_EQ(bytes_str, bytes_str_expected);
    }
}

/**
 * Test \c tsnh call
 */
TEST(utilsTest, tsnh_call)
{
    // Call tsnh
    ASSERT_DEATH(tsnh(Formatter() << "Calling tsnh from test."), "");
}

/**
 * Test \c is_file_accessible method
 *
 * CASES:
 * - File exist
 * - File is readable
 * - File does not exist and not readable
 */
TEST(utilsTest, is_file_accessible)
{
    // TODO. We should ideally change the RWX permissions with chmod and test all cases

    // File exist
    {
        // Default argument
        ASSERT_TRUE(is_file_accessible("resources/exist.test"));

        // Set argument
        ASSERT_TRUE(is_file_accessible("resources/exist.test", FileAccessMode::exist));
    }

    // File is readable
    {
        ASSERT_TRUE(is_file_accessible("resources/exist.test", FileAccessMode::read));
    }

    // File does not exist and not readable
    {
        ASSERT_FALSE(is_file_accessible("resources/not_exist.test"));
        ASSERT_FALSE(is_file_accessible("resources/not_exist.test", FileAccessMode::exist));
        ASSERT_FALSE(is_file_accessible("resources/not_exist.test", FileAccessMode::read));
    }
}

TEST(utilsTest, combined_file_permissions)
{
    // Compositions with '|' operator
    ASSERT_EQ(FileAccessMode::read | FileAccessMode::write, FileAccessMode::read_write);
    ASSERT_EQ(FileAccessMode::read | FileAccessMode::exec, FileAccessMode::read_exec);
    ASSERT_EQ(FileAccessMode::read | FileAccessMode::write | FileAccessMode::exec, FileAccessMode::read_write_exec);
    ASSERT_EQ(FileAccessMode::write | FileAccessMode::exec, FileAccessMode::write_exec);

    // Match exist
    ASSERT_EQ(FileAccessMode::read & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::write & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::exist & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::read_write & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::read_exec & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::write_exec & FileAccessMode::exist, FileAccessMode::exist);
    ASSERT_EQ(FileAccessMode::read_write_exec & FileAccessMode::exist, FileAccessMode::exist);

    // Match read
    ASSERT_EQ(FileAccessMode::read & FileAccessMode::read, FileAccessMode::read);
    ASSERT_NE(FileAccessMode::write & FileAccessMode::read, FileAccessMode::read);
    ASSERT_NE(FileAccessMode::exec & FileAccessMode::read, FileAccessMode::read);
    ASSERT_EQ(FileAccessMode::read_write & FileAccessMode::read, FileAccessMode::read);
    ASSERT_EQ(FileAccessMode::read_exec & FileAccessMode::read, FileAccessMode::read);
    ASSERT_EQ(FileAccessMode::read_write_exec & FileAccessMode::read, FileAccessMode::read);
    ASSERT_NE(FileAccessMode::write_exec & FileAccessMode::read, FileAccessMode::read);

    // Match write
    ASSERT_NE(FileAccessMode::read & FileAccessMode::write, FileAccessMode::write);
    ASSERT_EQ(FileAccessMode::write & FileAccessMode::write, FileAccessMode::write);
    ASSERT_NE(FileAccessMode::exec & FileAccessMode::write, FileAccessMode::write);
    ASSERT_EQ(FileAccessMode::read_write & FileAccessMode::write, FileAccessMode::write);
    ASSERT_NE(FileAccessMode::read_exec & FileAccessMode::write, FileAccessMode::write);
    ASSERT_EQ(FileAccessMode::read_write_exec & FileAccessMode::write, FileAccessMode::write);
    ASSERT_EQ(FileAccessMode::write_exec & FileAccessMode::write, FileAccessMode::write);

    // Match exec
    ASSERT_NE(FileAccessMode::read & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_NE(FileAccessMode::write & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_EQ(FileAccessMode::exec & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_NE(FileAccessMode::read_write & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_EQ(FileAccessMode::read_exec & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_EQ(FileAccessMode::read_write_exec & FileAccessMode::exec, FileAccessMode::exec);
    ASSERT_EQ(FileAccessMode::write_exec & FileAccessMode::exec, FileAccessMode::exec);
}

/**
 * Test method split_string(string, string)
 */
TEST(utilsTest, split_string_one_delimiter)
{
    std::vector<
        std::pair<
            std::pair<
                std::string,  /* first argument */
                std::string>,  /* second argument */
            std::vector<std::string>  /* expected result */
            >
        > test_cases =
    {
        {
            {"trivial", " "},
            {"trivial"}
        },

        {
            {"one space", " "},
            {"one", "space"}
        },

        {
            {"with other\ndelimiters", "\n"},
            {"with other", "delimiters"}
        },

        {
            {"e be ce", "e"},
            {"", " b", " c", ""}
        },

        {
            {"longer delimiter", "r d"},
            {"longe", "elimiter"}
        },
    };

    for (const auto& test_case : test_cases)
    {
        auto& result_expected = test_case.second;
        auto result = split_string(test_case.first.first, test_case.first.second);

        ASSERT_EQ(result_expected, result);
    }
}

/**
 * Test method split_string(vector<string>, string)
 */
TEST(utilsTest, split_strings_one_delimiter)
{
    std::vector<
        std::pair<
            std::pair<
                std::vector<std::string>,  /* first argument */
                std::string>,  /* second argument */
            std::vector<std::string>  /* expected result */
            >
        > test_cases =
    {
        {
            {{"trivial"}, " "},
            {"trivial"}
        },

        {
            {{"one space"}, " "},
            {"one", "space"}
        },

        {
            {{"more than", "one", "sentence here"}, " "},
            {"more", "than", "one", "sentence", "here"}
        },

        {
            {{"other\ndelimiter", "\nhere"}, "\n"},
            {"other", "delimiter", "", "here"}
        },
    };

    for (const auto& test_case : test_cases)
    {
        auto& result_expected = test_case.second;
        auto result = split_string(test_case.first.first, test_case.first.second);

        ASSERT_EQ(result_expected, result);
    }
}

/**
 * Test method split_string(string, set<string>)
 */
TEST(utilsTest, split_string_delimiters)
{
    std::vector<
        std::pair<
            std::pair<
                std::string,  /* first argument */
                std::set<std::string>>,  /* second argument */
            std::vector<std::string>  /* expected result */
            >
        > test_cases =
    {
        {
            {"trivial", {" "}},
            {"trivial"}
        },

        {
            {"one space", {" "}},
            {"one", "space"}
        },

        {
            {"with other\ndelimiters", {" ", "\n"}},
            {"with", "other", "delimiters"}
        }
    };

    for (const auto& test_case : test_cases)
    {
        auto& result_expected = test_case.second;
        auto result = split_string(test_case.first.first, test_case.first.second);

        ASSERT_EQ(result_expected, result);
    }
}

/**
 * Test method get_keys from std::map
 */
TEST(utilsTest, get_map_keys)
{
    // std::string keys
    {
        std::set<std::string> keys = {"a", "b", "c", "d"};
        std::map<std::string, std::string> map;
        for (auto key: keys)
        {
            map.emplace(key, "value");
        }

        ASSERT_EQ(keys, get_keys(map));
    }

    // int keys
    {
        std::set<int> keys = {1, 2, 3, 4};
        std::map<int, std::string> map;
        for (auto key: keys)
        {
            map.emplace(key, "value");
        }

        ASSERT_EQ(keys, get_keys(map));
    }
}

/**
 * Test method get_keys from std::unordered_map
 */
TEST(utilsTest, get_unordered_map_keys)
{
    // std::string keys
    {
        std::set<std::string> keys = {"a", "b", "c", "d"};
        std::unordered_map<std::string, std::string> map;
        for (auto key: keys)
        {
            map.emplace(key, "value");
        }

        ASSERT_EQ(keys, get_keys(map));
    }

    // int keys
    {
        std::set<int> keys = {1, 2, 3, 4};
        std::unordered_map<int, std::string> map;
        for (auto key: keys)
        {
            map.emplace(key, "value");
        }

        ASSERT_EQ(keys, get_keys(map));
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
