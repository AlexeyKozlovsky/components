#include "callbacks/models/impls/standaloneimpl/background/threadpooldevicetask.h"

ThreadPoolDeviceTask::ThreadPoolDeviceTask(const std::shared_ptr<IProcessable> &modbus_wrapper_device_task,
                                           const std::shared_ptr<IProcessable> &device_task):
                                           _modbus_wrapper_device_task(modbus_wrapper_device_task),
                                           _device_task(device_task) {

}

void ThreadPoolDeviceTask::process() {
  if (_modbus_wrapper_device_task != nullptr) {
    _modbus_wrapper_device_task->process();
  }

  if (_device_task != nullptr) {
    _device_task->process();
  }
}
