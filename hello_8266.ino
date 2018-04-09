//#define IP_FRAG                 1
//#define IP_FRAG_USES_STATIC_BUF 1
//#define IP_FRAG_MAX_MTU         1200

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char * ssid = "watson";
const char * password = "****";

ESP8266WebServer server(80);

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" connected");


  server.on("/other", []() {   //Define the handling function for the path
    server.send(200, "text/plain", "Other URL");
  });

  server.on("/art", []() {
    server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\" class=\"\"><head><meta charset='utf-8'><meta name=\"viewport\" content=\"width=device-width,initial-scale=1,user-scalable=no\"/><title>Sonoff - Main Menu</title><script>var cn,x,lt;cn=180;x=null;function u(){if(cn>=0){document.getElementById('t').innerHTML='Restart in '+cn+' seconds';cn--;setTimeout(u,1000);}}function c(l){document.getElementById('s1').value=l.innerText||l.textContent;document.getElementById('p1').focus();}function la(p){var a='';if(la.arguments.length==1){a=p;clearTimeout(lt);}if(x!=null){x.abort();}x=new XMLHttpRequest();x.onreadystatechange=function(){if(x.readyState==4&&x.status==200){var s=x.responseText.replace(/{t}/g,\"<table style='width:100%'>\").replace(/{s}/g,\"<tr><th>\").replace(/{m}/g,\"</th><td>\").replace(/{e}/g,\"</td></tr>\").replace(/{c}/g,\"%'><div style='text-align:center;font-weight:\");document.getElementById('l1').innerHTML=s;}};x.open('GET','ay'+a,true);x.send();lt=setTimeout(la,2345);}function lb(p){la('?d='+p);}function lc(p){la('?t='+p);}</script><style>div,fieldset,input,select{padding:5px;font-size:1em;}input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;}select{width:100%;}textarea{resize:none;width:98%;height:318px;padding:5px;overflow:auto;}body{text-align:center;font-family:verdana;}td{padding:0px;}button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}button:hover{background-color:#006cba;}a{text-decoration:none;}.p{float:left;text-align:left;}.q{float:right;text-align:right;}</style></head><body onload='la()'><div style='text-align:left;display:inline-block;min-width:340px;'><div style='text-align:center;'><h3>Sonoff Basic Module</h3><h2>Sonoff</h2></div><div id='l1' name='l1'></div><table style='width:100%'><tr><td style='width:100'><button onclick='la(\"?o=1\");'>Toggle</button></td></tr></table><br/><form action='cn' method='get'><button>Configuration</button></form><br/><form action='in' method='get'><button>Information</button></form><br/><form action='up' method='get'><button>Firmware Upgrade</button></form><br/><form action='cs' method='get'><button>Console</button></form><br/><form action='rb' method='get' onsubmit='return confirm(\"Confirm Restart\");'><button>Restart</button></form><br/><div style='text-align:right;font-size:11px;'><hr/><a href='https://bit.ly/tasmota' target='_blank' style='color:#aaa;'>Sonoff-Tasmota 5.12.0i by Theo Arends</a></div></div></body></html>");
  });
  
  server.on("/", handleRootPath);    //Associate the handler function to the path
 
  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());

}

void handleRootPath() {            //Handler for the rooth path 
  server.send(200, "text/plain", "Hello world");
}

void loop() {
  server.handleClient();         //Handling of incoming requests
}
