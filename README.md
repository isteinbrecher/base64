# base64

This is a simple implementation for the conversion of a `char` stream to a [*base64*](https://en.wikipedia.org/wiki/Base64) encoded `std::string` and back.

## Usage

The following code is a minimal example which involves the functionality of *base64*.

```c++
#include <iostream>
#include "base64.h"

int main()
{
  const char* input = "base64 encoding example!";
  const size_t input_length = 24;

  // This is where the actual encoding and decoding takes place.
  std::string base64_encoded = base64::encode(input, input_length);
  std::vector<char> base64_decoded = base64::decode(base64_encoded);

  std::string decoded_string(base64_decoded.data(), base64_decoded.size());
  const bool results_match = std::string(input, input_length) == decoded_string;

  std::cout << "Input char stream:      \"" << input << "\"\n";
  std::cout << "Base64 endocded string: \"" << base64_encoded << "\"\n";
  std::cout << "Decoded string:         \"" << decoded_string << "\"\n";
  std::cout << "Results match:          " << results_match << "\n";
  return !results_match;
}
```

The expected output is

```bash
Input char stream:      "base64 encoding example!"
Base64 endocded string: "YmFzZTY0IGVuY29kaW5nIGV4YW1wbGUh"
Decoded string:         "base64 encoding example!"
Results match:          1
```
