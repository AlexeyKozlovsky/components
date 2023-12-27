#ifndef OU_1U_STYLESHEETS_DEFAULT_H_
#define OU_1U_STYLESHEETS_DEFAULT_H_

#include <QFont>

#include "widgets/enums.h"

static std::map<ChannelButtonStates, const char*> ChannelButtonStyles {
    {ChannelButtonStates::BUTTON_OFF, "background-color: rgb(241, 241, 241);"},
    {ChannelButtonStates::BUTTON_ON, "background-color: lightgreen;"},
    {ChannelButtonStates::BUTTON_CHOSEN, "font-weight:bold; border-style: inset;"},
//  {ChannelButtonStates::BUTTON_INVERTED, "background-color: red;"}
    {ChannelButtonStates::BUTTON_INVERTED, ""
                                           "border-width: 1px;\n"
                                           "border-radius: 10px;\n"
                                           "border-color: grey;"}
};

struct styles_struct_t {
  std::vector<const char*> states{
      "background-color: orange",
      "background-color: lightblue",
      "background-color: lightgreen"
  };
};

static const styles_struct_t softValidationLineEditStyles;

struct fonts_struct_t {
  const QFont channl_box_name = QFont("Arial", 24, QFont::Bold);
};

static const fonts_struct_t fonts;

static std::map<LampStates, const char*> lampWidgetStyles{
    {LampStates::LAMP_OFF, "border: 1px solid black;"},
    {LampStates::LAMP_GOOD, "background-color: green; border: 1px solid black;"},
    {LampStates::LAMP_BAD, "background-color: red; border: 1px solid black;"}
};

#endif //OU_1U_STYLESHEETS_DEFAULT_H_
