# Mastodon - Tooting from Arduino

A minimalistic implementation of a write-only Mastodon client for
Arduino. It can be used to post status messages, sensor telemetry,
etc.

## Usage

Once a Mastodon object (say, masto) is defined, only three members
functions are provided:

* masto.begin() initializes the object with server name, access token,
  and a pointer to an existing Client object. I have only tested it
  with the WiFiSSLClient client provided by the WiFiNINA library.

* masto.verify() verifies the credentials provided to the begin()
  member function.  Returns the HTTP status code (200 = OK).

* masto.toot() posts a status message (toot).  Returns the HTTP status
  code (200 = OK).

## Examples

### send_toot

This example sends a test toot (hardcoded in the loop() function). The
header file arduino_secrets.h must be populated with the following
constant strings:

* SECRET_HOSTNAME: hostname of the Arduino board for
  self-identification (it can be anything you want).

* SECRET_SSID, SECRET_PASS: SSID and password of Wi-Fi network to
  which the board will connect.

* SECRET_SERVER: The name of the Mastodon server, e.g., fosstodon.org.

* SECRET_TOKEN: The OAuth token that can be obtained from the Mastodon
  server (go to Preferences > Development > New application)

### verify_credentials

Similar to send_toot, but simply verifies the credentials provided
without posting anything.

## Acknowledgments

Partly inspired by NeoCat's Arduino Twitter Library
(https://github.com/NeoCat/Arduno-Twitter-library) of which I was a
very happy user until, on a very sad day in April 2023, the Twitter
API stopped working and I, like many others, made the jump to the
Fediverse along with my trusted robot
(https://mastodon.bot/@theRobotMark3).

