#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERFACTORYSTORAGE_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERFACTORYSTORAGE_H_

#include <string>
#include <memory>

#include <QWidget>
#include <utils/storages/basestorage.h>


// !note Для плагинов используются имена плагинов вместо UID для упрощения


class PluginProviderFactoryStorage: public BaseStorage {
 public:
  virtual void addPluginProviderFactoryView(const std::string &name, const std::shared_ptr<QWidget> &view) = 0;

  virtual std::shared_ptr<QWidget> getPluginProviderFactoryView(const std::string &name) = 0;
  virtual bool removePluginProviderFactoryView(const std::string &name) = 0;

  virtual std::vector<std::string> getPluginProviderFactoryNames() = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_PLUGINPROVIDERFACTORYSTORAGE_H_
