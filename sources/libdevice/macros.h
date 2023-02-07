#ifndef DIALTEK_LIBDEVICE_MACROS_H_
#define DIALTEK_LIBDEVICE_MACROS_H_

#include <variant>
#include <string>
#include <vector>


#define SCALAR_VARIANT \
std::variant<bool, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, \
uint64_t, int64_t, float, double, std::string, char>

#define VARIANT \
std::variant<SCALAR_VARIANT, std::vector<SCALAR_VARIANT>>

// TODO: Пройтись по библиотеки и прописать все взаимодействия с кодом ошибки через макросы

#define IS_ERROR(error_code, instruction) if (error_code != nullptr && *error_code == ErrorCode::SUCCESS) { \
  instruction;                                                                                                            \
}

#define IS_NOT_ERROR(error_code, instruction) if (error_code != nullptr && *error_code != ErrorCode::SUCCESS) { \
  instruction;                                                                                                            \
}

#define SET_ERROR_CODE(error_code, error_code_value) if (error_code != nullptr) { \
  *error_code = error_code_value;                                                                                  \
}



#endif //DIALTEK_LIBDEVICE_MACROS_H_
