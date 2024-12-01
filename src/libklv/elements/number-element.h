
#ifndef __NUMBER_ELEMENT_H__
#define __NUMBER_ELEMENT_H__

#include <cstdint>
#include <string>
#include <type_traits>

#include "element.h"
#include "libklv/domain.h"
#include "libklv/logger.h"

/*
 * S type: Software type
 * K type: KLV type
 * */
template <typename S, typename K> class NumberElement : public Element {

public:
  NumberElement(const uint8_t key, const std::string &key_name,
                const Domain<S> &soft_domain, const Domain<K> &klv_domain,
                const int offset = 0)
      : Element(key, key_name), m_soft_domain(soft_domain),
        m_klv_domain(klv_domain), m_offset(offset) {};

  bool Encode(std::vector<uint8_t> &buffer, Json &json) override {

    if (!json.is_number()) {
      LOG_ERROR() << "Value should be number";
      return false;
    }

    if (std::is_integral_v<S> && json.is_number_float()) {
      LOG_ERROR() << " type mishmatch";
      return false;
    }

    Json data = json;
    if (!m_soft_domain.Contains(data)) {
      LOG_WARNING() << "Tag" << std::to_string(m_key) << " '" << m_key_name
                    << "' data should be in range of ["
                    << m_soft_domain.GetMin() << ", " << m_soft_domain.GetMax()
                    << "]";

      data = std::min(m_soft_domain.GetMax(),
                      std::max(m_soft_domain.GetMin(), static_cast<S>(data)));
    }

    size_t value =
        ((double)m_klv_domain.GetRange() / (double)m_soft_domain.GetRange()) *
        ((double)data + m_offset);

    buffer.push_back(m_key);
    buffer.push_back(sizeof(K));
    for (int i = sizeof(K) - 1; i >= 0; i--) {
      buffer.push_back(((value >> (i * 8)) & 0xFF));
    }

    return true;
  };

  bool Decode(std::vector<uint8_t> &buffer, Json &json) override {

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
      LOG_ERROR()
          << "Buffer does not contain enough data for the expected length.";
      return false;
    }

    size_t value = 0;
    for (int i = 0; i < sizeof(K); i++) {
      value |= (buffer[i + 2] << ((length - i - 1) * 8));
    }

    // insert the data into the json as key value
    json[std::to_string(m_key)] = static_cast<S>(
        (((double)m_soft_domain.GetRange() / (double)m_klv_domain.GetRange()) *
         value) -
        m_offset);

    // remove the element from the buffer
    buffer.erase(buffer.begin(), buffer.begin() + 2 + length);

    return true;
  };

private:
  const int m_offset;
  const Domain<S> &m_soft_domain;
  const Domain<K> &m_klv_domain;
};

#endif //__NUMBER_ELEMENT_H__
