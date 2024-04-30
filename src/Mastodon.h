//////////////////////////////////////////////////////////////////
//
// Mastodon - Tooting from Arduino
// AP2023-2024.
//
// This code is licensed under the MIT license (see LICENSE.md)
//
//////////////////////////////////////////////////////////////////

#ifndef _MASTODON_H_
#define _MASTODON_H_

#include <Arduino.h>
#include <Client.h>

class Mastodon {
public:
  void begin(const char *server, const char *token, Client *client);
  void end(void);
  int verify(Print *debug = &Serial);
  int toot(const char *status, Print *debug = &Serial);
private:
  const char *server_;
  const char *token_;
  Client *client_;
  bool connect(Print *debug);
  void sendHeaders(void);
  int parseReturnCode(Print *debug);
};

#endif // _MASTODON_H_

