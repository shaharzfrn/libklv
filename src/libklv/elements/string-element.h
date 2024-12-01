
#ifndef __STRING_ELEMENT_H__
#define __STRING_ELEMENT_H__

#include "element.h"
#include <cstdint>
#include <string>

class StringElement : public Element {

public:
  StringElement(const uint8_t key, const std::string &key_name);

  bool Encode(std::vector<uint8_t> &buffer, Json &json_data) override;
  bool Decode(std::vector<uint8_t> &buffer, Json &json_data) override;
};

#endif //__STRING_ELEMENT_H__
