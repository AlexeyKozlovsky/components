#ifndef DIALTEK_LIBDEVICE_ENUMS_ENUMS_H_
#define DIALTEK_LIBDEVICE_ENUMS_ENUMS_H_

namespace device {

enum DeviceState {
  ON = 0,
  OFF = 1,
  OPEN = 2,
  CLOSE = 3,
  WAIT = 255,
};

namespace attrs {
  enum RequestType {
    READ = 0,
    WRITE = 1,
    EXECUTE = 2
  };
}

}

#endif //DIALTEK_LIBDEVICE_ENUMS_ENUMS_H_
