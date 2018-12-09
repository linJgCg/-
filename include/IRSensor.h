/*
 *  版權: 2018 lin_jeng_cheng
 *  許可證: 可以隨便複製
 *  作者: 內湖高工 電機三忠 林正晟
 *
 *  實作原理:
 *     將取得的電壓最高值與最低值平均後與當前電壓進行比較，
 *     未觸發為false，觸發為true。
 *
 *  使用概述:
 *     宣告IRSensor物件
 *      auto ir_sensor = make_IRSensor(pin);
 *
 *     取得IRSensor物件的狀態
 *      auto ir_status = ir_sensor.get_status();
 *
 *     更新IRSensor物件的狀態
 *      ir_sensor.update();
 *
 *     調整IRSensor物件的平均值加權
 *      pinyin預設為1
 *      ir_sensor.set_pinyin(pinyin); //會將平均值乘上pinyin
 *
*/
#ifndef IR_SENSOR
#define IR_SENSOR
//關於類的說明移至文件最上面
class IRSensor {
 public:
  IRSensor(const uint16_t pin);
  auto set_high(const uint16_t low)->void;
  auto get_high()->uint16_t;
  auto set_low(const uint16_t low)->void;
  auto get_low()->uint16_t;
  auto get_status()->bool;
  auto set_pinyin(const double pinyin)->void;
  auto get_pinyin()->double;
  auto update()->void;

 private:
  int high_;
  int low_;
  int mean_;
  bool status_;
  double pinyin_;
  uint16_t pin_;

};

IRSensor::IRSensor(const uint16_t pin) {
  pin_ = pin;
  pinMode(pin, INPUT_PULLUP);
  high_ = 0;
  low_ = 1023;
  mean_ = 0;
  status_ = false;
  pinyin_ = 1;
}

auto IRSensor::get_high()->uint16_t{
  return high_;
}

auto IRSensor::get_low()->uint16_t{
  return low_;
}

auto IRSensor::get_status()->bool{
  return status_;
}

auto IRSensor::set_high(const uint16_t high)->void{
  high_ = high;
}

auto IRSensor::set_low(const uint16_t low)->void{
  low_ = low;
}

auto IRSensor::set_pinyin(double pinyin)->void{
  pinyin_ = pinyin;
}

auto IRSensor::get_pinyin()->double{
  return pinyin_;
}

auto IRSensor::update()->void{
  auto load_ir = analogRead(pin_);
  if (load_ir > high_)high_ = load_ir;
  if (load_ir < low_)low_ = load_ir;
  mean_ = (high_ + low_) / 2 * pinyin_;
  status_ = load_ir < mean_;
}

IRSensor make_IRSensor(const uint16_t pin) {
  return IRSensor(pin);
}

#endif //IR_SENSOR