const char menupage[] PROGMEM = {R"delimiter(
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title> Milind's ESP8266 Server </title>
<script src="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.js" integrity="sha512-dqw6X88iGgZlTsONxZK9ePmJEFrmHwpuMrsUChjAw1mRUhUITE5QU9pkcSox+ynfLhL15Sv2al5A0LVyDCmtUw==" crossorigin="anonymous"></script>
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.css" integrity="sha512-8bHTC73gkZ7rZ7vpqUQThUDhqcNFyYi2xgDgPDHc+GXVGHXq+xPjynxIopALmOPqzo9JZj0k6OqqewdGO3EsrQ==" crossorigin="anonymous" />
<style>
  body{
    background-image: url("https://img.wallpapersafari.com/desktop/1920/1080/6/90/6gNyaX.jpg");
  }
  a {
    color: white;
  }
</style>
</head>
<body>
</br>
<h1 class="ui center aligned icon header">
  <i class="server icon"></i>
  Milind ESP8266 Server
</h1>
<br>
<br>
<div class="ui center aligned one row grid">
<a  class="ui button" href = "http://108.46.156.22:7777/LED" > LED Toggle </a>
<a class="ui button" href = "http://108.46.156.22:7777/LED2" > LED Toggle (5)</a>
<a class="ui button" href = "http://108.46.156.22:7777/DHT"> DHT Reading </a>
<a class="ui button" href = "http://108.46.156.22:7777/Q"> Get a Quote! </a>
<a class="ui button" href = "http://108.46.156.22:7777/clr"> Clear Screen </a>
</div>
</body>
</html>
)delimiter"};
