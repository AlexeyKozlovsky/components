#ifndef WIDGETS_LIBWIDGETS_WIDGETS_INCLUDE_WIDGETS_UTILS_H_
#define WIDGETS_LIBWIDGETS_WIDGETS_INCLUDE_WIDGETS_UTILS_H_

namespace dev {
struct SFPParameters {
  double temperature = 0;
  double voltage = 0;
  double tx_amperage_shift = 0;
  double tx_optical_power = 0;
  double rx_power = 0;
};

struct ModuleStatuses {
  bool rx_loss = false;
  bool tx_fault = false;
};
}

#endif //WIDGETS_LIBWIDGETS_WIDGETS_INCLUDE_WIDGETS_UTILS_H_
