#ifndef OU_1U_SERVICES_ENUMS_H_
#define OU_1U_SERVICES_ENUMS_H_

#include <vector>
#include <map>
#include <QString>
#include <QMap>

enum Units {
  NS = 0,
  MKS = 1,
  MS = 2
};

static QMap<int, QString> t831_modes { {0, QString("Внешний")},
                                       {1, QString("Внутренний")},
                                       {2, QString("Z-состояние")}};


static std::map<QString, Units> units_names{ {QString("нс"), Units::NS},
                                             {QString("мкс"), Units::MKS},
                                             {QString("мс"), Units::MS},
                                             {QString("ns"), Units::NS},
                                             {QString("mks"), Units::MKS},
                                             {QString("ms"), Units::MS}};

enum LampStates {
  LAMP_OFF = 0,
  LAMP_GOOD = 1,
  LAMP_BAD = 2
};

enum ChannelButtonStates {
  BUTTON_OFF = 0,
  BUTTON_ON = 1,
  BUTTON_CHOSEN = 2,
  BUTTON_INVERTED = 3
};

#endif //OU_1U_SERVICES_ENUMS_H_
