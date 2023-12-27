#include "../../../../include/threadpooling/impls/threadpoolperiodicimplbuilder.h"

#include "../../../../include/threadpooling/impls/periodictask.h"


static const int MIN_THREADS_COUNT = 1;
static const int MAX_THREADS_COUNT = 8;
static const int DEFAULT_SLEEP_IN_MS = 10;


ThreadPoolPeriodicImplBuilder::ThreadPoolPeriodicImplBuilder(const std::shared_ptr<UIDGenerator> &uid_generator):
 _uid_generator(uid_generator), _sleep_in_ms(DEFAULT_SLEEP_IN_MS) {

}

void ThreadPoolPeriodicImplBuilder::setThreadBuilderSleep(int sleep_in_ms) {
  _sleep_in_ms = sleep_in_ms;
}

std::shared_ptr<ThreadPool> ThreadPoolPeriodicImplBuilder::createBase(int threads_count) {
  clear();
  if (_uid_generator == nullptr) {
    clear();
    return _thread_pool;
  }

  if (threads_count  < MIN_THREADS_COUNT || threads_count > MAX_THREADS_COUNT) {
    clear();
    return _thread_pool;
  }

  if (_sleep_in_ms <= 0) {
    clear();
    return _thread_pool;
  }

  auto duration = std::chrono::duration<int, std::milli>(_sleep_in_ms);
  _thread_pool = std::make_shared<ThreadPoolPeriodicImpl>(threads_count, duration);
  return _thread_pool;
}

std::shared_ptr<ThreadPool> ThreadPoolPeriodicImplBuilder::setThreadsCount(int threads_count) {
  _threads_count = threads_count;
  return _thread_pool;
}

std::shared_ptr<ThreadPool> ThreadPoolPeriodicImplBuilder::addTask(const std::shared_ptr<IProcessable> &task,
                                                                   const std::string &task_uid,
                                                                   int period_in_ms) {
  if (_uid_generator == nullptr) {
    clear();
    return _thread_pool;
  }

//  task_uid = _uid_generator->generateUIDString();
  if (_thread_pool == nullptr) {
    return _thread_pool;
  }

  if (period_in_ms < 0) {
    clear();
    return _thread_pool;
  }

  auto period_for_task = std::chrono::milliseconds(period_in_ms);
  auto periodic_task = std::make_shared<PeriodicTask>(task, period_for_task);

  _thread_pool->addTask(task_uid, periodic_task);
  return _thread_pool;
}

std::shared_ptr<ThreadPool> ThreadPoolPeriodicImplBuilder::removeTask(const std::string &task_uid) {
  if (_thread_pool == nullptr) {
    return _thread_pool;
  }

  _thread_pool->removeTask(task_uid);
  return _thread_pool;
}

std::shared_ptr<ThreadPool> ThreadPoolPeriodicImplBuilder::getThreadPool() {
  return _thread_pool;
}

void ThreadPoolPeriodicImplBuilder::clear() {
  _thread_pool = nullptr;
}
