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
 * \brief Define the de- and encode functions for base64.
 */

#pragma once

#include <string>
#include <vector>

namespace base64
{
  /**
   * @brief Encode a character array to a base 64 string.
   *
   * The char array is converted to base64 according to https://en.wikipedia.org/wiki/Base64.
   *
   * @param buffer (in) Input character array.
   * @param length (in) Length of the buffer.
   * @return String representation of the base64 ending.
   */
  std::string encode(const char* buffer, const size_t& length);

  /**
   * @brief Decode a base64 string to a character array.
   *
   * The string is converted from base64 according to https://en.wikipedia.org/wiki/Base64.
   *
   * @param string (in) Base64 encoded string.
   * @return Vector with the decoded character data.
   */
  std::vector<char> decode(const std::string& string);
}  // namespace base64
