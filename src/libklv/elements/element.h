
#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <stdint.h>
#include <stdio.h>
#include <string>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

class Element {

public:
  Element(const uint8_t key, const std::string key_name);

  virtual bool Encode(std::vector<uint8_t> &buffer, Json &json) = 0;
  virtual bool Decode(std::vector<uint8_t> &buffer, Json &json) = 0;

protected:
  uint8_t m_key;
  std::string m_key_name;
};

#endif // !__ELEMENT_H__
