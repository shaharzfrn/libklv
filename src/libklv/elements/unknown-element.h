#ifndef __UNKNOW_ELEMENT_H__
#define __UNKNOW_ELEMENT_H__

#include "element.h"
#include <cstdint>
#include <string>

class UnknowElement : public Element {

public:
  UnknowElement(const uint8_t key, const std::string &key_name);

  bool Encode(std::vector<uint8_t> &buffer, Json &json) override;
  bool Decode(std::vector<uint8_t> &buffer, Json &json) override;
};

#endif //__UNKNOW_ELEMENT_H__
