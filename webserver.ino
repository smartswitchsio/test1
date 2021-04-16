
/*Socket messages*/
 void ICACHE_FLASH_ATTR onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
 {
  //Handle WebSocket event, onEvent
   if(type == WS_EVT_CONNECT){
  
     dtdisplay = true;
  } else if(type == WS_EVT_DISCONNECT){
    
   
    dtdisplay = false;
  } else if(type == WS_EVT_ERROR){
  
  } else if(type == WS_EVT_PONG){

  } else if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
    
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
    
     splitdata(msg.c_str(),client);
      
     }
  }
}

/*webserver*/
void startserver(){
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

    server.on("/icomoon.woff", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/woff", icomoon_woff_gz, icomoon_woff_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
    server.on("/ediys.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", ediys_min_css_gz, ediys_min_css_gz_len);//SIZE
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
  server.on("/ediys.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", ediys_min_js_gz, ediys_min_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
  server.on("/server.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", server_js_gz, server_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, index_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

 server.begin();

}
