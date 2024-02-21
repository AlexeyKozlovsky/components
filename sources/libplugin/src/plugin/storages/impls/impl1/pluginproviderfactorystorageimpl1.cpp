
#include "plugin/storages/impls/impl1/pluginproviderfactorystorageimpl1.h"


void PluginProviderFactoryStorageImpl1::addPluginProviderFactoryView(const std::string &name,
                                                                     const std::shared_ptr<PluginProviderFactory> &plugin_provider_factory) {
  if (plugin_provider_factory != nullptr) {
    _factory_providers.insert({name, plugin_provider_factory});
    rowInsertedNotify();
  }
}

std::shared_ptr<PluginProviderFactory> PluginProviderFactoryStorageImpl1::getPluginProviderFactory(const std::string &name) {
  std::shared_ptr<PluginProviderFactory> result = nullptr;
  if (_factory_providers.count(name) != 0) {
    result = _factory_providers.at(name);
  }
  return result;
}

std::shared_ptr<QWidget> PluginProviderFactoryStorageImpl1::getPluginProviderFactoryView(const std::string &name) {
  std::shared_ptr<QWidget> result = nullptr;

  auto factory_provider = getPluginProviderFactory(name);
  if (factory_provider != nullptr) {
    result = factory_provider->getPluginProviderFactoryView();
  }

  return result;
}

bool PluginProviderFactoryStorageImpl1::removePluginProviderFactoryView(const std::string &name) {
  bool result = false;
  if (_factory_providers.count(name)) {
    _factory_providers.erase(name);
    result = true;
    rowRemovedNotify();
  }

  return result;
}
int PluginProviderFactoryStorageImpl1::getRowCount() {
  return _factory_providers.size();
}

std::vector<std::string> PluginProviderFactoryStorageImpl1::getPluginProviderFactoryNames() {
  std::vector<std::string> names;
  for(auto it = _factory_providers.begin(); it != _factory_providers.end(); ++it) {
    names.push_back(it->first);
  }

  return names;
}


