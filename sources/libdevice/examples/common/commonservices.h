#ifndef LIBDEVICE_EXAMPLES_COMMON_COMMONSERVICES_H_
#define LIBDEVICE_EXAMPLES_COMMON_COMMONSERVICES_H_

struct SFPStatuses {
  double temperature;
  double voltage;
  double tx_shift_amperage;
  double tx_optical_power;
  double rx_power;
};

struct ModuleStatuses {
  bool rx;
  bool tx;
  bool rx_loss;
  bool tx_fault;
};

#endif //LIBDEVICE_EXAMPLES_COMMON_COMMONSERVICES_H_
