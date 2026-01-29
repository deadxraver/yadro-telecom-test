#include <fstream>
#include <iostream>

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
  std::string time, client_name;
  int id, table;
  while (fin >> time >> id >> client_name) {
    Event* event;
    if (id == 2 || id == 12) {
      fin >> table;
      event = new Event(time, id, client_name, table);
    } else
      event = new Event(time, id, client_name);
    std::cout << event->to_string() << std::endl; // TEST:
    delete event;
  }
  fin.close();
  return 0;
}
