#include "string-element.h"

#include "libklv/logger.h"

StringElement::StringElement(const uint8_t key, const std::string &key_name)
    : Element(key, key_name) {}

bool StringElement::Encode(std::vector<uint8_t> &buffer, Json &json) {

  if (!json.is_string()) {
    LOG_ERROR() << "Data for tag '" << m_key_name << "' is not a string";
    return false;
  }

  std::string value = json.template get<std::string>();
  size_t length = value.length();

  if (length > 127) {
    LOG_WARNING() << "String length for key '" << m_key_name
                  << "' exceeds 127 bytes. Truncating to 127 bytes.";
    length = std::min(length, size_t(127));
  }

  buffer.push_back(m_key);
  buffer.push_back(length);
  std::copy_n(value.begin(), length, std::back_inserter(buffer));

  return true;
};

bool StringElement::Decode(std::vector<uint8_t> &buffer, Json &json) {

  if (buffer.empty()) {
    LOG_ERROR() << "Buffer is empty, Cannot decode";
    return false;
  }

  uint8_t key = buffer[0];
  if (key != m_key) {
    LOG_ERROR() << "Key mismatch during decoding.";
    return false;
  }

  uint8_t length = buffer[1];

  if (buffer.size() < 2 + length) {
    LOG_ERROR() << "Buffer does not contain enough data for the expected length.";
    return false;
  }

  // insert the data into the json as key value
  json[std::to_string(m_key)] =
      std::string(buffer.begin() + 2, buffer.begin() + 2 + length);

  // remove the element from the buffer
  buffer.erase(buffer.begin(), buffer.begin() + 2 + length);

  return true;
};

