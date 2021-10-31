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

#include "base64.h"

//! Conversion array for base64.
static const char* base64_to_char =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 *
 */
std::string base64::encode(const char* buffer, const size_t& length)
{
  size_t encoded_length = (length / 3) * 4;
  size_t rest = length % 3;
  if (rest != 0) encoded_length += rest + 1;
  std::string output_string;
  output_string.reserve(encoded_length);

  // Loop over the char array.
  unsigned int count = 0;
  unsigned int count_output = 0;
  while (count < length)
  {
    // Get the combined value of 3 chars.
    int three_char_value = 0;
    for (unsigned int inner_count = 0; inner_count < 3; inner_count++)
    {
      // Shift the value by 8 bits in order to make room for the next value.
      three_char_value <<= 8;

      if (count < length)
      {
        // Add the 8 bits of the current value. It is important to to a bitwise operation here, as
        // otherwise there are issues with negative values.
        three_char_value |= buffer[count] & 0xFF;
      }

      count++;
    }

    // Convert to 4 ASCI characters.
    for (unsigned int i_encoded = 0; i_encoded < 4; i_encoded++)
    {
      // Read the bits 23-18
      const int index = (three_char_value & 0xFC0000) >> 18;

      // Shift the bits in the result variable.
      three_char_value <<= 6;

      // Add the encoded character to the result string.
      if (count_output < encoded_length) output_string.push_back(base64_to_char[index]);
      count_output++;
    }
  }

  return output_string;
}

/**
 *
 */
std::vector<char> base64::decode(const std::string& string)
{
  size_t string_size = string.size();
  size_t length_result = (string_size / 4) * 3;
  size_t rest = string_size % 4;
  if (rest != 0) length_result += rest - 1;

  // Initialize the return vector.
  std::vector<char> char_vector(length_result);

  // Loop over the string data.
  const char* data_char = string.c_str();

  unsigned int count = 0;
  unsigned int count_output = 0;
  while (count < string_size)
  {
    // Get the combined value of 4 base64 items.
    int four_base64_value = 0;
    for (unsigned int inner_count = 0; inner_count < 4; inner_count++)
    {
      char this_value = 0;

      if (count < string_size)
      {
        auto this_char = data_char[count];

        if (this_char >= 'A' && this_char <= 'Z')
          this_value = this_char - 'A';
        else if (this_char >= 'a' && this_char <= 'z')
          this_value = this_char - 'a' + ('Z' - 'A') + 1;
        else if (this_char >= '0' && this_char <= '9')
          this_value = this_char - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
        else if (this_char == '+')
          this_value = 62;
        else if (this_char == '/')
          this_value = 63;
        else
          throw(this_value);
      }

      four_base64_value <<= 6;
      four_base64_value |= this_value & 0x3F;
      count++;
    }

    // Convert the 4 ASCI characters to 3 'char'.
    for (unsigned int i_encoded = 0; i_encoded < 3; i_encoded++)
    {
      // Read the bits 23-16
      const char index = (char)((four_base64_value & 0xFF0000) >> 16);

      // Shift the bits.
      four_base64_value <<= 8;

      // Add to the output vector.
      if (count_output < length_result) char_vector[count_output] = index;
      count_output++;
    }
  }

  return char_vector;
}
