
#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#define WEBSERVER_PORT                  (80)

static const char *INDEX_HTML =
"<!DOCTYPE html>"
"<html><head>"
"<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP-FM Radio</title>"
"<style>"
"label{width:6em;display:inline-block;padding:5px;text-align:right}"
"input{width:5em;height:1.5em;font-size:1em}"
"</style></head>"
"<body style=\"font-family:Arial, Helvetica, sans-serif\">"
"<div style=\"text-align:center\">"
"<h3>ESP-FM Radio Configuration</h3>"
"<form action=\"/config\" method=\"post\" style=\"border: 2px #eee solid\">"
"<div style=\"padding:5px\"><label>Frequency:</label><input type=\"number\" name=\"frequency\" value=97.9 step=\"0.05\" min=87.5 max=108 required></input></div>"
"<div style=\"padding:5px\"><label>Volume:</label><input type=\"number\" name=\"volume\" value=50 min=0 max=100 required></input></div>"
"<div style=\"padding:5px\"><span style=\"width:6.5em;display:inline-block\"></span><input type=\"submit\" value=\"Set\" style=\"width:5em;height:2em;font-size:1.2em\"></input></div>"
"</form></div></body></html>";

static const char *REDIRECT_HTML =
"<!DOCTYPE html><html lang=\"en\">"
"<head><meta charset=\"utf-8\"/></head>"
"<script type=\"text/javascript\">"
"window.setTimeout('window.location.replace(\"/\")', 200);"
"</script></html>";

#endif // __WEBSERVER_H__
