#ifndef _EVENT_MANAGER_HPP

#define _EVENT_MANAGER_HPP

#include "event.hpp"

#include <string>
#include <vector>
#include <queue>

struct Place {
  bool is_taken;
  std::string client_name;
  Place();
};

class EventManager {
private:
  std::vector<Place> tables_;
  std::vector<std::string> clients_queue_;
  std::vector<std::string> clients_in_;
  int tables_count_;
  Time open_time_;
  Time close_time_;
  int cost_;
  bool remove_from_queue(std::string client);
public:
  EventManager(
    int tables_count,
    std::string open_time,
    std::string close_time,
    int cost
  );
  Event check_queue(Time time);
  std::vector<std::string> cleanup();
  Event apply_event(const Event& event);
};

#endif // !_EVENT_MANAGER_HPP
