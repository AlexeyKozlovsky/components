#ifndef PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_COMMANDPROVIDERS_COMMANDPROVIDERIMPL1_H_
#define PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_COMMANDPROVIDERS_COMMANDPROVIDERIMPL1_H_

#include <QMap>

#include "plugin/deviceplugins/commandprovider.h"
#include <plugin/export.h>


class PLUGIN_EXPORT CommandProviderImpl1: public PluginCommandProvider {
 public:
  bool hasCommand(const QString &command_name) override;
  CommandResponse executeCommand(CommandRequest request) override;
  ErrorCode addCommand(const QString &command_name, const std::shared_ptr<Command> &command) override;
  ErrorCode removeCommand(const QString &command_name) override;

 private:
  QMap<QString, std::shared_ptr<Command>> _commands;
};

#endif //PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_COMMANDPROVIDERS_COMMANDPROVIDERIMPL1_H_
