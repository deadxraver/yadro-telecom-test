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

Time::Time(std::string time_str) : Time::Time(stoi(time.substr(0, 2)), stoi(time.substr(3, 5)));

Event::Event(
  std::string time,
  int code,
  std::string client_name
) : event_code_((EventCode)code) {
  this->time = Time(time);
  // NOTE: VVV checked in EventManager
  this->event_code_ = (EventCode)code;
  this->content_ = client_name;
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

Event::Event(std::string time, int code, std::string client_name, int table) : Event::Event(time, code, client_name) {
  this->table_ = table;
}

EventCode Event::event_code() const {
  return this->event_code_;
}

std::string Event::time() const {
  return this->time_->to_string();
}

const std::string& Event::msg() const {
  return this->content_;
}

const std::string& Event::client_name() const {
  return this->content_;
}

std::string Event::to_string() const {
  return this->time() + " "
  + std::to_string(this->event_code_) + " "
  + this->content_
  + (this->event_code_ == I_CLIENT_TOOK_PLACE || this->event_code_ == O_CLIENT_TOOK_PLACE ? 
    " " + std::to_string(this->table_) : "");
}
