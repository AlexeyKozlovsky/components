#include "request.h"

#include <memory>

void Request::onCreated() {
  time_created = std::chrono::system_clock::now();
  state = RequestState::CREATED;
}

void Request::onRequested() {
  time_requested = std::chrono::system_clock::now();
  state = RequestState::REQUESTED;
}

void Request::onResponsed() {
  time_responsed = std::chrono::system_clock::now();
  state = RequestState::RESPONSED;

  finished = true;

  if (on_responsed_callback != nullptr)
    on_responsed_callback(nullptr, this);
}
