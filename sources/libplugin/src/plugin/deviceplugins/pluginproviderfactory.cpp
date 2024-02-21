#include "plugin/deviceplugins/pluginproviderfactory.h"


PluginProviderFactory::PluginProviderFactory(const std::shared_ptr<QWidget> &plugin_provider_factory_view,
                                             const std::shared_ptr<PluginProviderStorage> &plugin_provider_storage,
                                             const std::shared_ptr<ThreadPoolBuilder> &thread_pool_builder):
                                             _plugin_provider_factory_view(plugin_provider_factory_view),
                                             _plugin_provider_storage(plugin_provider_storage),
                                             _thread_pool_builder(thread_pool_builder) {

}

ErrorCode PluginProviderFactory::destroyPluginProvider(const std::string &uid) {
  auto result = OPERATION_INTERRUPTED;
  if (_plugin_provider_storage != nullptr && _thread_pool_builder != nullptr) {
    bool is_ok = _plugin_provider_storage->removeDevice(uid);
    auto new_thread_pool = _thread_pool_builder->removeTask(uid);

    if (is_ok && new_thread_pool != nullptr) {
      result = SUCCESS;
    }
  }
  return result;
}

std::shared_ptr<QWidget> PluginProviderFactory::getPluginProviderFactoryView() {
  return _plugin_provider_factory_view;
}
