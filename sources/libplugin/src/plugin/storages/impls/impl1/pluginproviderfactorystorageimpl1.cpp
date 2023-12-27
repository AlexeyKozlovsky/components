
#include "plugin/storages/impls/impl1/pluginproviderfactorystorageimpl1.h"


void PluginProviderFactoryStorageImpl1::addPluginProviderFactoryView(const std::string &name,
                                                                     const std::shared_ptr<QWidget> &view) {
  if (view != nullptr) {
    _factory_views.insert({name, view});
  }
}

std::shared_ptr<QWidget> PluginProviderFactoryStorageImpl1::getPluginProviderFactoryView(const std::string &name) {
  std::shared_ptr<QWidget> result = nullptr;
  if (_factory_views.count(name) != 0) {
    result = _factory_views.at(name);
  }

  return result;
}

bool PluginProviderFactoryStorageImpl1::removePluginProviderFactoryView(const std::string &name) {
  _factory_views.erase(name);
  return true;
}
