//#include <ESP_MS.h>

const char menupage[] PROGMEM= {R"delimiter(
<html>
<head>
<title> Milind's ESP8266 Server </title>
<script src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.js" integrity="sha512-dqw6X88iGgZlTsONxZK9ePmJEFrmHwpuMrsUChjAw1mRUhUITE5QU9pkcSox+ynfLhL15Sv2al5A0LVyDCmtUw==" crossorigin="anonymous"></script>
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.css" integrity="sha512-8bHTC73gkZ7rZ7vpqUQThUDhqcNFyYi2xgDgPDHc+GXVGHXq+xPjynxIopALmOPqzo9JZj0k6OqqewdGO3EsrQ==" crossorigin="anonymous" />
<style>
  a {
    color: white;
  }
</style>
</head>
<body>
<h1 class="ui center aligned icon header">
  <i class="circular users icon"></i>
  ESP8266 Server
</h1>
<a  class="ui button" href = "http://108.46.156.22:7777/LED" > 1.LED Toggle </a>
<br>
<a class="ui button" href = "http://108.46.156.22:7777/LED2" > 2.LED Toggle(Board 5) </a>
<br>
<a class="ui button" href = "http://108.46.156.22:7777/DHT"> 3.DHT Reading </a>
<br>
<a class="ui button" href = "http://108.46.156.22:7777/Q"> 4.Get a Quote! </a>
</body>
</html>
)delimiter"};
