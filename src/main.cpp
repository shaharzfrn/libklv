#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "libklv/domain.h"
#include "libklv/elements/number-element.h"
#include "libklv/elements/string-element.h"
#include "libklv/elements/unknown-element.h"
#include "libklv/logger.h"

int main() {

  Logger::SetLogLevel(LogLevel::DEBUG);

  LOG_DEBUG() << "Hello World";
  std::cout << "hello world" << std::endl;

  Domain<uint8_t> base_domain;
  LOG_DEBUG() << "" << std::to_string(base_domain.GetRange());

  std::cout << std::to_string(base_domain.GetMax()) << "\t"
            << std::to_string(base_domain.GetMin()) << std::endl;
  ;

  std::vector<uint8_t> vec;
  Json json;

  UnknowElement element(123, "Test Element");
  element.Encode(vec, json);

  StringElement str(3, "Mission ID");
  Json s = 330;

  NumberElement<uint8_t, uint8_t> aaa(12, "DDD", base_domain, base_domain);
  aaa.Encode(vec, s);

  return 0;
}
