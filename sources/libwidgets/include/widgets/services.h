#ifndef OU_1U_SERVICES_SERVICES_H_
#define OU_1U_SERVICES_SERVICES_H_

#include "enums.h"
#include "consts.h"

/*!
 * Функция переводит значение числа из одних единиц измерения в наносекунды
 * @param value значение числа;
 * @param unit единица измерения.
 * @return Значение числа в наносекундах.
 */
static inline uint64_t toNano(double value, Units unit){
  double ns_value = value;
  for (int i = 0; i < unit; i++)
    ns_value *= 1000;
  return (uint64_t) ns_value;
};

namespace dev {
  namespace epss {
    static inline QString makeChannelConstName(int channel_num,
                                               int channel_group_size = DEFAULT_CHANNEL_GROUP_COUNT,
                                               int channels_count = DEFAULT_CHANNEL_COUNT,
                                               const QVector<QString> &group_letters = DEFAULT_CHANNEL_LETTERS) {
      if (channel_num < 0 || channel_num >= channels_count) return "";

      int channel_letter_id = channel_num / channel_group_size;
      int channel_num_in_group = channel_num % channel_group_size + 1;

      if (channel_letter_id >= group_letters.size()) return "";
      QString channel_const_name = group_letters[channel_letter_id] + QString::number(channel_num_in_group);
      return channel_const_name;
    }
  }
}

#endif //OU_1U_SERVICES_SERVICES_H_
