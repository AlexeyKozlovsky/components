#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_CONNECTIONMANAGER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_CONNECTIONMANAGER_H_

#include <utils/baseutils.h>

class ConnectionManager {
 public:
  virtual bool getHWConnectionStatus() = 0;
  virtual ErrorCode connectHW(bool connect) = 0;

  /**
   * Для тех девайсов, которые обрабатываются клиент-серверно
   * @return true - если, например tango device, false -- если standalone
   */
  virtual bool isServerSide() = 0;
  virtual bool getServerConnectionStatus() = 0;
  virtual ErrorCode connectServer(bool connect) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_CONNECTIONMANAGER_H_
