/*
 *  版權: 2018 lin_jeng_cheng
 *  許可證: 可以隨便複製
 *  作者: 內湖高工 電機三忠 林正晟
 *
 *  實作原理:
 *     將多個紅外線感應器包起來，成為一個長度不固定的陣列
 *     TODO 增加插入紅外線感測器，刪除紅外線感測器
 *  使用概述:
 *     宣告IRsensorArray物件
 *
 *       constexpr auto pins_size = 5; //紅外線感測器數量
 *       uint16_t pins[pins_size] = {A4, A3, A2, A1, A0}; // 紅外線感測器接腳
 *       IRsensorArray ir_sensor_array = make_IRsensorArray(pins, pins_size);
 *
 *     使用索引取得IRsensorArray物件的IRSensor物件
 *
 *       ir_sensor_array[i].update();
 *
 *       如果i>ir_sensor_array.size()的話，會發生越界存取等不可預期之後果，請
 *       務必小心
 *       TODO 解決越界存取問題，可能是用拋異常
*/
#ifndef IRSENSOR_ARRAY
#define IRSENSOR_ARRAY

#include"IRSensor.h"

class IRsensorArray {
 public:
  IRsensorArray(const uint16_t* pins, const uint16_t size);
  IRsensorArray(const IRsensorArray& src);
  ~IRsensorArray(void);
  auto operator[](const uint16_t index)->IRSensor&;
  auto size()->uint16_t;
 private:
  uint16_t size_;
  typedef IRSensor* IRSensorPtr;
  IRSensorPtr* ir_array_;
};

IRsensorArray::IRsensorArray(const uint16_t* pins, const uint16_t size) {
  ir_array_ = new IRSensorPtr[size];
  size_ = size;
  for (uint16_t i = 0; i < size_; ++i) {
    ir_array_[i] = new IRSensor(pins[i]);
  }
}

IRsensorArray::~IRsensorArray(void) {
  for (uint16_t i = 0; i < size_; ++i) {
    delete ir_array_[i];
  }
  delete[] ir_array_;
}

auto IRsensorArray::operator[](const uint16_t index)->IRSensor& {
  return *ir_array_[index];
}

auto IRsensorArray::size()->uint16_t{
  return size_;
}

IRsensorArray make_IRsensorArray(const uint16_t* pins, const uint16_t size) {
  return IRsensorArray(pins, size);
}

#endif //IRSENSOR_ARRAY