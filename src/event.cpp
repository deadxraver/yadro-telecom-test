#include "event.hpp"

#include <iostream>

Time::Time(uint8_t hours, uint8_t minutes) : hours_(hours), minutes_(minutes) {
  if (hours < 0 || hours >= 24) {
    // TODO: throw exception
  }
  if (minutes < 0 || hours >= 60) {
    // TODO: throw exception
  }
}

Time::Time(std::string time_str) : Time::Time(stoi(time_str.substr(0, 2)), stoi(time_str.substr(3, 5))) {}

bool Time::is_less(const Time& time) const {
  if (time.hours_ > this->hours_)
    return true;
  if (time.hours_ < this->hours_)
    return false;
  return time.minutes_ > this->minutes_;
}

std::string Time::to_string() const {
  std::string ret = this->hours_ >= 10 ? "" : "0";
  ret += std::to_string(this->hours_);
  ret += ":";
  if (this->minutes_ < 10)
    ret += "0";
  ret += std::to_string(this->minutes_);
  return ret;
}

Event::Event(
  Time time,
  int code,
  std::string content
) : time_(time), event_code_((EventCode)code), content_(content) {}

Event::Event(
  Time time,
  int code,
  std::string content,
  int table_count
) : Event(time, code, content) {
  this->table_ = table_count;
}

Event::Event(
  std::string time,
  int code,
  std::string client_name
) : event_code_((EventCode)code), time_(time) {
  // NOTE: VVV checked in EventManager
  this->event_code_ = (EventCode)code;
  this->content_ = client_name;
}

Event::Event(std::string time, int code, std::string client_name, int table) : Event::Event(time, code, client_name) {
  this->table_ = table;
}

EventCode Event::event_code() const {
  return this->event_code_;
}

Time Event::time() const {
  return this->time_;
}

const std::string& Event::msg() const {
  return this->content_;
}

const std::string& Event::client_name() const {
  return this->content_;
}

std::string Event::to_string() const {
  return this->time().to_string() + " "
  + std::to_string(this->event_code_) + " "
  + this->content_
  + (this->event_code_ == I_CLIENT_TOOK_PLACE || this->event_code_ == O_CLIENT_TOOK_PLACE ? 
    " " + std::to_string(this->table_) : "");
}
