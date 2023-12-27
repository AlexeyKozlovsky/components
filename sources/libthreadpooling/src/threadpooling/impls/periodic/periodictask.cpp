#include "../../../../include/threadpooling/impls/periodictask.h"

PeriodicTask::PeriodicTask(const std::shared_ptr<IProcessable> &processable,
    std::chrono::system_clock::duration period): _period(period), _processable(processable) {
  _last_time_processed = std::chrono::system_clock::now();
}

bool PeriodicTask::setPeriod(int period_in_ms) {
  _mutex.lock();
  bool result = false;
  if (period_in_ms > 0) {
    _period = std::chrono::milliseconds(period_in_ms);
    result = true;
  }

  _mutex.unlock();
  return result;
}

void PeriodicTask::process() {
  if (_processable != nullptr) {
    _processable->process();
    _last_time_processed = std::chrono::system_clock::now();
  }
}

void PeriodicTask::setBusy(bool busy) {
  _is_busy = busy;
}

bool PeriodicTask::isReady() {
  _mutex.lock();
  bool result = false;
  auto now = std::chrono::system_clock::now();
  bool cond = now - _last_time_processed >= _period;
  result = (cond && !_is_busy);
  _mutex.unlock();
  return result;
}
