const char index_ESP[] PROGMEM= { R"delimiter(
  <html>
  <head>
    <title>
      ESP8266 Server  
    </title>
    <style>
      html { 
          background: url("https://i.pinimg.com/originals/89/61/0e/89610e51686fc18228e108cc081d0bdd.jpg") no-repeat center center fixed; 
          -webkit-background-size: cover;
          -moz-background-size: cover;
          -o-background-size: cover;
          background-size: cover;
}
    </style>
  </head>
  <body>
    <h1> ESP8266 Server</h1>
    <br>
    <a href = "http://192.168.0.147/LED"> 1.LED </a>
    <br>
    <a href = "http://192.168.0.147/DHT"> 2.DHT </a>
  </body>
</html>)delimiter"};
