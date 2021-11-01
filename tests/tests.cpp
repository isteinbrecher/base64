// -----------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2021 Ivo Steinbrecher
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// -----------------------------------------------------------------------------

/**
 * \brief Test the base64 de- and encode functions.
 */

#include "base64.h"
#include <chrono>
#include "tests_utils.h"
#include <gtest/gtest.h>


#define TEST_BASE64_STRING(test_name, input_str, decoded_str)           \
  TEST(base64_tests, test_name)                                         \
  {                                                                     \
    const std::string input = input_str;                                \
    const auto encoded = base64::encode(input.c_str(), input.length()); \
    EXPECT_EQ(decoded_str, encoded);                                    \
    const auto decoded = base64::decode(encoded);                       \
    const std::string decoded_string(decoded.data(), decoded.size());   \
    EXPECT_EQ(input, decoded_string);                                   \
  }

/**
 * \brief Test the string examples form https://en.wikipedia.org/wiki/Base64.
 */
TEST_BASE64_STRING(test_string_wikipedia_1, "Man", "TWFu")
TEST_BASE64_STRING(test_string_wikipedia_2, "Ma", "TWE")
TEST_BASE64_STRING(test_string_wikipedia_3, "M", "TQ")
TEST_BASE64_STRING(test_string_wikipedia_4, "light work.", "bGlnaHQgd29yay4")
TEST_BASE64_STRING(test_string_wikipedia_5, "light work", "bGlnaHQgd29yaw")
TEST_BASE64_STRING(test_string_wikipedia_6, "light wor", "bGlnaHQgd29y")
TEST_BASE64_STRING(test_string_wikipedia_7, "light wo", "bGlnaHQgd28")
TEST_BASE64_STRING(test_string_wikipedia_8, "light w", "bGlnaHQgdw")

/**
 * \brief Test that all characters can be in a decoded string.
 */
TEST(base64_tests, test_all_characters_decode)
{
  const std::vector<char> input = {0, 16, -125, 16, 81, -121, 32, -110, -117, 48, -45, -113, 65, 20,
      -109, 81, 85, -105, 97, -106, -101, 113, -41, -97, -126, 24, -93, -110, 89, -89, -94, -102,
      -85, -78, -37, -81, -61, 28, -77, -45, 93, -73, -29, -98, -69, -13, -33, -65, 0, 16, -125, 16,
      81, -121, 32, -110, -117, 48, -45, -113, 65, 20, -109, 81, 85, -105, 97, -106, -101, 113, -41,
      -97, -126, 24, -93, -110, 89, -89, -94, -102, -85, -78, -37, -81, -61, 28, -77, -45, 93, -73,
      -29, -98, -69, -13, -33, -65};
  const auto encoded = base64::encode(input.data(), input.size());
  EXPECT_EQ(
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
      encoded);
  const auto decoded = base64::decode(encoded);
  EXPECT_EQ(input, decoded);
}

/**
 * \brief Test that all characters can be input.
 */
TEST(base64_tests, test_all_characters_encode)
{
  std::vector<char> input(1000);
  for (unsigned int i = 0; i < 1000; i++) input[i] = i;
  const auto encoded = base64::encode(input.data(), input.size());
  EXPECT_EQ(
      "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+"
      "P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+"
      "AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/"
      "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/"
      "wABAgMEBQYHCAkKCwwNDg8QERITFBUWFxgZGhscHR4fICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDR"
      "EVGR"
      "0hJSktMTU5PUFFSU1RVVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX5/"
      "gIGCg4SFhoeIiYqLjI2Oj5CRkpOUlZaXmJmam5ydnp+goaKjpKWmp6ipqqusra6vsLGys7S1tre4ubq7vL2+"
      "v8DBwsPExcbHyMnKy8zNzs/Q0dLT1NXW19jZ2tvc3d7f4OHi4+Tl5ufo6err7O3u7/Dx8vP09fb3+Pn6+/z9/"
      "v8AAQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/"
      "QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+"
      "f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/"
      "AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f7/"
      "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+"
      "P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+"
      "AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/"
      "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5w",
      encoded);
  const auto decoded = base64::decode(encoded);
  EXPECT_EQ(input, decoded);
}

/**
 * \brief Test the conversion of a long string.
 */
void test_long_string(
    const unsigned int factor, const std::size_t expected_hash, const double expected_time)
{
  std::string very_long_string("");
  for (unsigned int i = 0; i < factor; i++) very_long_string += long_string;

  auto time_begin = std::chrono::system_clock::now();

  const auto encoded = base64::encode(very_long_string.c_str(), very_long_string.length());
  const std::size_t encoded_hash = std::hash<std::string>{}(encoded);
  EXPECT_EQ(expected_hash, encoded_hash);
  const auto decoded = base64::decode(encoded);
  const std::string decoded_string(decoded.data(), decoded.size());
  EXPECT_EQ(very_long_string, decoded_string);

  const std::chrono::duration<double> duration = std::chrono::system_clock::now() - time_begin;

  EXPECT_LT(duration.count(), expected_time);
}

/**
 * \brief Define multiple long string tests.
 */
TEST(base64_tests, test_long_string_1) { test_long_string(1, 14064419678309408447U, 0.005); }
TEST(base64_tests, test_long_string_10) { test_long_string(10, 11796950950356069221U, 0.05); }
TEST(base64_tests, test_long_string_100) { test_long_string(100, 14617901939564356506U, 0.5); }