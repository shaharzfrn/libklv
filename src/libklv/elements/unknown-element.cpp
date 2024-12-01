#include "unknown-element.h"

#include "libklv/logger.h"

UnknowElement::UnknowElement(const uint8_t key, const std::string &key_name)
    : Element(key, key_name) {}

bool UnknowElement::Encode(std::vector<uint8_t> &buffer, Json &json) {
  LOG_WARNING() << "Tag " << m_key_name << " [" << std::to_string(m_key)
                << "] is not supported!";
  return false;
}
bool UnknowElement::Decode(std::vector<uint8_t> &buffer, Json &json) {
  LOG_WARNING() << "Tag " << m_key_name << " [" << std::to_string(m_key)
                << "] is not supported!";
  return false;
};
