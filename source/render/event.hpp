#ifndef H_RENDER_EVENT_SINGLE
#define H_RENDER_EVENT_SINGLE

enum event_type {
  EVENT_CLOSE,
  EVENT_KEYDOWN,EVENT_KEYUP,EVENT_KEY,
  EVENT_RESIZE,EVENT_MINIMIZE };

class event {
public:
  event_type type;
  
  char  key;
  const char* specialKey;
  
  bool status=false,special=false; };

#endif
