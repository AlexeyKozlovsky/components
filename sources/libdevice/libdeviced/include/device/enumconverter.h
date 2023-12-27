#ifndef DIALTEK_LIBDEVICE_ENUMCONVERTER_H_
#define DIALTEK_LIBDEVICE_ENUMCONVERTER_H_

#include <modbus.h>
#include "enums.h"


namespace device {
ErrorCode toErrorCode(modbus::ModbusResult input_code);
}

#endif //DIALTEK_LIBDEVICE_ENUMCONVERTER_H_
