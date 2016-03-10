// Libraries
#include "Arduino.h"

void handleRoot() {
 digitalWrite ( ledWiFi, 0 );
  char temp[2000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  // Convert the floats to strings
  char tc[6];
  char tf[6];
  char hm[6];
  dtostrf(getTempCelsius(), 3, 2, tc);
  dtostrf(getTempFahrenheit(), 3, 2, tf);
  dtostrf(getHumidityRH(), 3, 2, hm);

  snprintf ( temp, 2000,

"<html class=\"no-js\" lang=\"en\"><head><meta charset=\"utf-8\">\
<!--meta http-equiv=\"refresh\" content=\"13\"-->\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
<title>ESP8266 Temp/Humidity Sensors</title>\
<script src=\"//cdnjs.cloudflare.com/ajax/libs/modernizr/2.8.3/modernizr.min.js\"></script>\
<link rel=\"stylesheet\" href=\"//cdn.jsdelivr.net/foundation/6.2.0/foundation.min.css\">\
<style>\
body{background-color: lightslategrey;}\
.callout{color:dimgrey!important;text-align:center;margin:1rem;padding:.25rem}\
.callout h2{font-weight:600;font-style:italic}\
header{background-color:rgba(0,0,139,.25);text-align:center;color:oldlace;padding:13px;}\
</style>\
</head><body>\
<header><h1>ESP8266 Temp/Humidity Sensors</h1><h3 class=\"subheader\">Uptime: %02d:%02d:%02d</h3></header>\
<section class=\"row\">\
<article class=\"medium-4 columns\"><div class=\"secondary large callout\"><h2 id=\"tc\">%s</h2><p><strong>Celsius</strong></p></div></article>\
<article class=\"medium-4 columns\"><div class=\"secondary large callout\"><h2 id=\"tf\">%s</h2><p><strong>Fahrenheit</strong></p></div></article>\
<article class=\"medium-4 columns\"><div class=\"secondary large callout\"><h2 id=\"rh\">%s</h2><p><strong>Relative Humidity</strong></p></div></article>\
</section>\
<script src=\"//code.jquery.com/jquery-1.9.1.min.js\"></script>\
<script src=\"//cdn.jsdelivr.net/foundation/6.2.0/foundation.min.js\"></script>\
<script>\
$(document).foundation();\
//$(document).ready(function(){\
//setInterval($.getJSON(\"/temperature/celsius\").done(function(data){$(\"#tc\").html(data.temperature.celsius);}), 5000);\
//setInterval($.getJSON(\"/temperature/fahrenheit\").done(function(data){$(\"#tf\").html(data.temperature.fahrenheit);}), 5000);\
//setInterval($.getJSON(\"/humidity\").done(function(data){$(\"#rh\").html(data.humidity.relative);}), 5000);\
//});\
</script>\
</body>\
</html>",

    hr, min % 60, sec % 60, tc, tf, hm
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( ledWiFi, 1 );
}
