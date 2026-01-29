#include "event.hpp"

#include <iostream>

Event::Event(std::string time, int code, std::string client_name) : event_code_((EventCode)code) {
  this->time_.hours = stoi(time.substr(0, 2));
  this->time_.minutes = stoi(time.substr(3, 5));
  if (this->time_.hours >= 24 || this->time_.minutes >= 60) {
    // TODO: throw exception
  }
  this->event_code_ = (EventCode)code; // TODO: check
  this->content_ = client_name; // TODO: check if no err
}

Event::Event(std::string time, int code, std::string client_name, int table) : Event::Event(time, code, client_name) {
  this->table_ = table;
}

EventCode Event::event_code() const {
  return this->event_code_;
}

std::string Event::time() const {
  std::string ret = this->time_.hours >= 10 ? "" : "0";
  ret += std::to_string(this->time_.hours);
  ret += ":";
  if (this->time_.minutes < 10)
    ret += "0";
  ret += std::to_string(this->time_.minutes);
  return ret;
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
