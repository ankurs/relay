
#define WEBDUINO_COMMANDS_COUNT 16
#include "WebServer.h"

#define PREFIX ""
WebServer webserver(PREFIX, 80);

void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
    P(helloMsg) = "<h1>Hello, World!</h1>";

    server.printP(helloMsg);
  }
}


int d0_status;
int d1_status;
int d2_status;
int d3_status;

void switchPin(int pin, int power) {
    switch (pin){
        case D0:
        digitalWrite(D0, power);
        d0_status = power;
        break;
        case D1:
        digitalWrite(D1, power);
        d1_status = power;
        break;
        case D2:
        digitalWrite(D2, power);
        d2_status = power;
        break;
        case D3:
        digitalWrite(D3, power);
        d3_status = power;
        break;
    }
}

// D0
void d0On(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D0, HIGH);
    server.httpSuccess();
    server.print("OK");
    server.flushBuf();
}

void d0Off(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D0, LOW);
    server.httpSuccess();
    server.print("OK");
}

void d0Status(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete){
    server.httpSuccess();
    if (d0_status == HIGH){
        server.print("ON");
    } else {
        server.print("OFF");
    }
}


// D1
void d1On(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D1, HIGH);
    server.httpSuccess();
    server.print("OK");
}

void d1Off(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D1, LOW);
    server.httpSuccess();
    server.print("OK");
}

void d1Status(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete){
    server.httpSuccess();
    if (d1_status == HIGH){
        server.print("ON");
    } else {
        server.print("OFF");
    }
}

// D2
void d2On(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D2, HIGH);
    server.httpSuccess();
    server.print("OK");
}

void d2Off(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    digitalWrite(D2, LOW);
    server.httpSuccess();
    server.print("OK");
}

void d2Status(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    server.httpSuccess();
    if (d2_status == HIGH){
        server.print("ON");
    } else {
        server.print("OFF");
    }
}

// D3
void d3On(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D3, HIGH);
    server.httpSuccess();
    server.print("OK");
}

void d3Off(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
    switchPin(D3, LOW);
    server.httpSuccess();
    server.print("OK");
}

void d3Status(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete){
    server.httpSuccess();
    if (d3_status == HIGH){
        server.print("ON");
    } else {
        server.print("OFF");
    }
}

void setup()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  // reset pins on startup
  switchPin(D0, LOW);
  switchPin(D1, LOW);
  switchPin(D2, LOW);
  switchPin(D3, LOW);

  webserver.setDefaultCommand(&helloCmd);

  webserver.addCommand("index.html", &helloCmd);

  webserver.addCommand("d0On", &d0On);
  webserver.addCommand("d0Off", &d0Off);
  webserver.addCommand("d0Status", &d0Status);

  webserver.addCommand("d1On", &d1On);
  webserver.addCommand("d1Off", &d1Off);
  webserver.addCommand("d1Status", &d1Status);

  webserver.addCommand("d2On", &d2On);
  webserver.addCommand("d2Off", &d2Off);
  webserver.addCommand("d2Status", &d2Status);

  webserver.addCommand("d3On", &d3On);
  webserver.addCommand("d3Off", &d3Off);
  webserver.addCommand("d3Status", &d3Status);

  webserver.begin();
}

void loop()
{
  char buff[64];
  int len = 64;

  webserver.processConnection(buff, &len);
}
