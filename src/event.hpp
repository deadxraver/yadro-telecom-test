#ifndef _EVENT_HPP

#define _EVENT_HPP

#include <cstdint>
#include <string>

enum EventCode {
  I_CLIENT_CAME = 1,
  I_CLIENT_TOOK_PLACE,
  I_CLIENT_WAITS,
  I_CLIENT_LEFT,
  O_CLIENT_LEFT = 11,
  O_CLIENT_TOOK_PLACE,
  O_ERROR,
};

struct Time {
  uint8_t hours;
  uint8_t minutes;
};

class Event {
private:
  EventCode event_code_;
  Time time_;
  std::string content_;
  int table_;
public:
  Event(std::string time, int code, std::string client_name);
  Event(std::string time, int code, std::string client_name, int table);
  EventCode event_code() const;
  std::string time() const;
  const std::string& msg() const;
  const std::string& client_name() const;
  std::string to_string() const;
};

#endif // !_EVENT_HPP
