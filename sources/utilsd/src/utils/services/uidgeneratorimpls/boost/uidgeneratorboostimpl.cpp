#include "../../../../../include/utils/services/uidgeneratorimpls/boost/uidgeneratorboostimpl.h"

std::string UIDGeneratorBoostImpl::generateUIDString() {
  std::string result;
  boost::uuids::uuid uuid = _generator();
  result = boost::uuids::to_string(uuid);
  return result;
}
