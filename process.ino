/*Send time to webpage*/
void senddtime(){ //send live date & time if client is connected
const size_t capacity = JSON_OBJECT_SIZE(2) + 30; // + 30;
DynamicJsonDocument doc(capacity);
    doc["id"] = "clk";
    doc["tm"] = "1618575789";
    String date;
    serializeJson(doc, date);
    ws.textAll(date);
}

/*get on/off msg from webpage*/
void relaysts(const char* sw){ //Send & Store switch status

if (strcmp(sw, "on0")  == 0) {
sw0 = 1;
digitalWrite(relay0, sw0 ? HIGH : LOW);
}
else if (strcmp(sw, "off0")  == 0) {
sw0 = 0;
digitalWrite(relay0, sw0 ? HIGH : LOW);
}
if (strcmp(sw, "on1")  == 0) {
sw1 = 1;
digitalWrite(relay1, sw1 ? HIGH : LOW);
}
else if (strcmp(sw, "off1")  == 0) {
sw1 = 0;
digitalWrite(relay1, sw1 ? HIGH : LOW);
}
if (strcmp(sw, "on2")  == 0) {
sw2 = 1;
digitalWrite(relay2, sw2 ? HIGH : LOW);
}
else if (strcmp(sw, "off2")  == 0) {
sw2 = 0;
digitalWrite(relay2, sw2 ? HIGH : LOW);
}}

/*Spliting data from webpage*/
void ICACHE_FLASH_ATTR splitdata(String msg, AsyncWebSocketClient * client)
{
  DynamicJsonDocument root(1024);
  auto error = deserializeJson(root, msg);
  if (error) {

    return;
}
    const char* id = root["id"];
    if (strcmp(id, "connected")  == 0) 
    {
    }
else if (strcmp(id, "swsts")  == 0) 
    {
    const char* sw = root["sw"];
    relaysts(sw);
    }
          
else{
    Serial.print("undefinded msg");
    Serial.print(msg);
    }
}
