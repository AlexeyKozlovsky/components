#include "../../../../include/threadpooling/impls/threadpoolperiodicimpl.h"

#include <algorithm>


ThreadPoolPeriodicImpl::ThreadPoolPeriodicImpl(int threads_count, std::chrono::system_clock::duration sleep_duration):
  _threads_count(threads_count), _sleep_duration(sleep_duration) {

}

ThreadPoolPeriodicImpl::~ThreadPoolPeriodicImpl() {
  stop();
}

void ThreadPoolPeriodicImpl::process() {
  while (_is_running) {
    std::for_each(std::begin(_tasks), std::end(_tasks), [&](const std::pair<std::string, std::shared_ptr<ThreadPoolTask>> &task_pair) {
      auto task = task_pair.second;
      if (task != nullptr) {
        bool is_ready = task->isReady();
        if (is_ready) {
          task->setBusy(true);
          task->process();
          task->setBusy(false);
        }
      }
    });

    std::this_thread::sleep_for(_sleep_duration);
  }
}

bool ThreadPoolPeriodicImpl::start() {
  bool result = false;
  if (!_is_running) {
    _is_running = true;

    for (int i = 0; i < _threads_count; i++) {
      _threads.emplace_back(&ThreadPoolPeriodicImpl::process, this);
    }
    result = true;
  }
  return result;
}

void ThreadPoolPeriodicImpl::stop() {
  if (_is_running) {
    _is_running = false;
    std::for_each(std::begin(_threads), std::end(_threads), [&](std::thread &thread) {
      thread.join();
    });
  }
}

bool ThreadPoolPeriodicImpl::isRunning() {
  return _is_running;
}

void ThreadPoolPeriodicImpl::addTask(const std::string &task_uid,
                                     const std::shared_ptr<ThreadPoolTask> &thread_pool_task) {
  _tasks.insert({task_uid, thread_pool_task});
}

void ThreadPoolPeriodicImpl::removeTask(const std::string &task_uid) {
  for( auto it = std::begin(_tasks); it != std::end(_tasks); ) {
    if( it->first == task_uid) it = _tasks.erase(it);
    else ++it;
  }
}
std::shared_ptr<ThreadPoolTask> ThreadPoolPeriodicImpl::getTask(const std::string &uid) {
  std::shared_ptr<ThreadPoolTask> result = nullptr;
  for( auto it = std::begin(_tasks); it != std::end(_tasks); ) {
    if( it->first == uid) {
      result = it->second;
      break;
    }
    ++it;
  }
  return result;
}
