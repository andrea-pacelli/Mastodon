//////////////////////////////////////////////////////////////////
//
// Mastodon - Tooting from Arduino
// AP2023-2024.
//
//////////////////////////////////////////////////////////////////

#include <Mastodon.h>

//////////////////////////////////////////////////////////////////
//
// Public functions
//
// Begin: Initialize object
//
void Mastodon::begin(const char *server, const char *token,
		     Client *client) {
  server_ = server;
  token_ = token;
  client_ = client;
}

//
// End: Do nothing
//
void Mastodon::end(void) {
}

//
// Verify credentials
//
int Mastodon::verify(Print *debug) {
  if (connect(debug)) {
    client_->println("GET /api/v1/accounts/verify_credentials HTTP/1.1");
    sendHeaders();
    client_->println("");
    return parseReturnCode(debug);
  } else {
    return -1;
  }
}

//
// Send toot
//
int Mastodon::toot(const char *status, Print *debug) {
  if (connect(debug)) {
    client_->println("POST /api/v1/statuses HTTP/1.1");
    sendHeaders();
    client_->print("Content-length: ");
    client_->println(strlen(status) + 7);
    client_->println("");
    client_->print("status=");
    client_->print(status);
    return parseReturnCode(debug);
  } else {
    return -1;
  }
}

//////////////////////////////////////////////////////////////////
//
// Private functions
//
// SSL connection to server
//
bool Mastodon::connect(Print *debug) {
  debug->print("Attempting to establish TCP connection to ");
  debug->println(server_);
  if (client_->connect(server_, 443)) {
    debug->print("Connected to ");
    debug->println(server_);
    return true;
  } else {
    debug->print("Failed to connect to ");
    debug->println(server_);
    return false;
  }
}

//
// Send HTTP headers
//
void Mastodon::sendHeaders(void) {
  // Mastodon specific
  client_->print("Host: ");
  client_->println(server_);
  client_->print("Authorization: Bearer ");
  client_->println(token_);
  // Generic headers
  client_->println("Accept: text/html");
}

//
// Crude parsing of return code
//
int Mastodon::parseReturnCode(Print *debug) {
  enum class State {head, value, tail};
  State state = State::head;
  char c;
  int code = 0;
  unsigned long millisStart = millis();
  const unsigned long millisTimeOut = 2000UL;
  const unsigned long millisTimeOutMax = 60000UL;

  debug->println("Returned from server:");
  while (client_->connected() &&
	 (state != State::tail ||
	  millis() - millisStart < millisTimeOut) &&
	 millis()  - millisStart < millisTimeOutMax) {
    if (!client_->available())
      continue;
    c = client_->read();
    if (state != State::tail)
      debug->print(c);
    switch (state) {
    case State::head:
      if (c == ' ')
	state = State::value;
      break;
    case State::value:
      if (c >= '0' && c <= '9') {
	code = 10 * code + (c - '0');
      } else if (c == ' ') {
	state = State::tail;
      }
      break;
    case State::tail:
      // do nothing
      break;
    }
  }
  debug->println();
  return (state == State::tail ? code : -1);
}

