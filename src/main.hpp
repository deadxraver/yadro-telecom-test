#ifndef _MAIN_HPP

#define _MAIN_HPP

enum InputEvent {
  I_CLIENT_CAME = 1,
  I_CLIENT_TOOK_PLACE,
  I_CLIENT_WAITS,
  I_CLIENT_LEFT,
};

enum OutputEvent {
  O_CLIENT_LEFT = 11,
  O_CLIENT_TOOK_PLACE,
  O_ERROR,
};

#endif // !_MAIN_HPP
