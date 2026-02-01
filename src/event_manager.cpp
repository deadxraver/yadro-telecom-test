#include "event_manager.hpp"

#include <algorithm>

Place::Place() {
  this->is_taken = false;
  this->client_name = "";
}

EventManager::EventManager(
  int tables_count,
  std::string open_time,
  std::string close_time,
  int cost
) : tables_count_(tables_count),
  cost_(cost),
  open_time_(open_time),
  close_time_(close_time),
  tables_(tables_count)
{}

bool EventManager::remove_from_queue(std::string client) {
  for (size_t i = 0; i < this->clients_queue_.size(); ++i) {
    if (this->clients_queue_[i] == client) {
      clients_queue_.erase(this->clients_queue_.begin() + i);
      return true;
    }
  }
  return false;
}

Event EventManager::apply_event(const Event& event) {
  if (event.time().is_less(this->open_time_))
    return Event(event.time(), O_ERROR, "NotOpenYet");
  if (event.event_code() == I_CLIENT_CAME) {
    return Event(event.time(), NO_EVENT, "");
  }
  else if (event.event_code() == I_CLIENT_TOOK_PLACE) {
    if (this->tables_[event.table_no()].is_taken)
      return Event(event.time(), O_ERROR, "PlaceIsBusy");
    for (size_t i = 0; i < this->tables_count_; ++i) { // in case a client is switching place
      Place p = this->tables_[i];
      if (p.is_taken && p.client_name == event.client_name()) {
        // TODO: count income
        this->tables_[i].is_taken = false;
        this->tables_[i].client_name = "";
        goto took_place_ok;
      }
    }
    if (this->remove_from_queue(event.client_name()))
      goto took_place_ok;
  took_place_ok:
    return Event(event.time(), O_CLIENT_TOOK_PLACE, event.client_name(), event.table_no());
  }
  else if (event.event_code() == I_CLIENT_WAITS) {
    for (Place p : this->tables_) {
      if (!p.is_taken)
        return Event(event.time(), O_ERROR, "ICanWaitNoLonger!");
    }
    if (clients_queue_.size() >= this->tables_count_)
      return Event(event.time(), O_CLIENT_LEFT, event.client_name());
    this->clients_queue_.push_back(event.client_name());
    return Event(event.time(), NO_EVENT, "");
  }
  else if (event.event_code() == I_CLIENT_LEFT) {
    for (size_t i = 0; i < this->tables_count_; ++i) {
      if (this->tables_[i].is_taken && this->tables_[i].client_name == event.client_name()) {
        // TODO: count income
        this->tables_[i].is_taken = false;
        this->tables_[i].client_name = "";
        goto left_ok;
      }
    }
    if (this->remove_from_queue(event.client_name()))
      goto left_ok;
    // BUG: returns NoSuchClient when shouldn't
    //return Event(event.time(), O_ERROR, "NoSuchClient");
  left_ok:
    return Event(event.time(), O_CLIENT_LEFT, event.client_name());
  }
  else
    return Event(event.time(), O_ERROR, "UnknownEventId");
}

std::vector<std::string> EventManager::cleanup() {
  std::vector<std::string> ret;
  for (; !this->clients_queue_.empty(); this->clients_queue_.erase(this->clients_queue_.begin())) {
    ret.push_back(this->clients_queue_.front());
  }
  for (size_t i = 0; i < this->tables_count_; ++i) {
    Place p = this->tables_[i];
    if (p.is_taken) {
      ret.push_back(p.client_name);
      this->tables_[i].is_taken = false;
    }
  }
  std::sort(ret.begin(), ret.end());
  return ret;
}
