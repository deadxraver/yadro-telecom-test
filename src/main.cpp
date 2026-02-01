#include <fstream>
#include <iostream>

#include "event_manager.hpp"
#include "event.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Incorrect input, should be:\n$ " << argv[0] << " <input filename>" << std::endl;
    return -1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open()) {
    std::cerr << "Error opening file " << argv[1] << std::endl;
    return -2;
  }
  int tables_count, hour_cost;
  std::string open_time_str, close_time_str;
  fin >> tables_count;
  fin >> open_time_str >> close_time_str;
  fin >> hour_cost;
  EventManager em(tables_count, open_time_str, close_time_str, hour_cost);
  std::string time, client_name;
  int id, table;
  std::cout << open_time_str << std::endl;
  while (fin >> time >> id >> client_name) {
    Event* event;
    if (id == 2 || id == 12) {
      fin >> table;
      event = new Event(time, id, client_name, table);
    } else
      event = new Event(time, id, client_name);
    std::cout << event->to_string() << std::endl;
    Event o_event = em.apply_event(*event);
    if (o_event.event_code() != NO_EVENT)
      std::cout << o_event.to_string() << std::endl;
    delete event;
  }
  for (std::string s : em.cleanup()) {
    Event e(close_time_str, O_CLIENT_LEFT, s);
    std::cout << e.to_string() << std::endl;
  }
  std::cout << close_time_str << std::endl;
  fin.close();
  return 0;
}
