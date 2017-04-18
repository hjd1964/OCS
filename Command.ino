// -----------------------------------------------------------------------------------
// Command processing

// help with commands
enum Commands {COMMAND_NONE, COMMAND_SERIAL, COMMAND_ETHERNET, COMMAND_ETHERNET1, COMMAND_ETHERNET2};
char reply[50];
char command[3];
char parameter[25];
boolean commandError = false;
boolean quietReply   = false;

cb cmd;
cb cmde;
cb cmde1;

// process commands
void processCommands() {
    boolean supress_frame = false;
    char *conv_end;

    // accumulate the command
    if ((Serial.available()>0) && (!cmd.ready())) cmd.add(Serial.read());
    if ((Cmd.available()>0) && (!cmde.ready())) cmde.add(Cmd.read());
    if ((Cmd1.available()>0) && (!cmde1.ready())) cmde1.add(Cmd1.read());

    // if a command is ready, process it
    Commands process_command = COMMAND_NONE;
    if (cmd.ready()) { strcpy(command,cmd.getCmd()); strcpy(parameter,cmd.getParameter()); cmd.flush(); process_command=COMMAND_SERIAL; } else
    if (cmde.ready()) { strcpy(command,cmde.getCmd()); strcpy(parameter,cmde.getParameter()); cmde.flush(); process_command=COMMAND_ETHERNET; } else
    if (cmde1.ready()) { strcpy(command,cmde1.getCmd()); strcpy(parameter,cmde1.getParameter()); cmde1.flush(); process_command=COMMAND_ETHERNET1; }
    else return;

    if (process_command) {
      quietReply=false;
// Command is two chars followed by an optional parameter...
      commandError=false;
// Handles empty and one char replies
      reply[0]=0; reply[1]=0;

//   G - Get Commands ------------------------------------------------------
      if (command[0]=='G') {
//  :G1#  Get outside temperature
//         Returns: nnn.n#
        if ((command[1]=='1') && (parameter[1]==0)) {
          dtostrf(weatherOutsideTemp(),3,1,reply);
          quietReply=true;
        } else
//  :G2#  Get sky IR temperature
//         Returns: nnn.n#
        if ((command[1]=='2') && (parameter[1]==0)) {
          dtostrf(weatherSkyTemp(),3,1,reply);
          quietReply=true;
        } else
//  :G3#  Get differential sky temperature
//         Returns: nnn.n#
//         where <=21 is cloudy
        if ((command[1]=='3') && (parameter[1]==0)) {
          dtostrf(getSkyDiffTemp(),3,1,reply);
          quietReply=true;
        } else
//  :GAn#  Get Analog n state
//         Example: :GA1#
//         Returns: 124# (0 to 1023, 0 to 5V)
        if ((command[1]=='A') && (parameter[1]==0)) {
          if ((parameter[0]>='0') && (parameter[0]<='5')) {
            int i=parameter[0]-'0'; if (i>9) i-=7;
            analogState[i]=analogRead(i);
            quietReply=true;
            sprintf(reply,"%d",analogState[i]);
          } else
            commandError=true;
        } else
//  :Gb#  Get absolute barometric pressure as Float
//         Returns: n.nnn#
//         where n ranges from about 980.0 to 1050.0 (mbar, sea-level compensated)
        if ((command[1]=='b') && (parameter[0]==0)) {
          dtostrf(weatherPressure(),1,1,reply);
          quietReply=true;
        } else
//  :GC#  Get cloud description
//         Example: :GC#
//         Returns: sssss...#
        if ((command[1]=='C') && (parameter[0]==0)) {
          quietReply=true;
          strcpy(reply,weatherCloudCoverDescription().c_str());
        } else
#if defined(THERMOSTAT_ON) && defined(HEAT_RELAY)
//  :GH#  Get Heat setpoint
//         Example: :GH#
//         Returns: 0# or 21#, 0 or temperature in C
        if (command[1]=='H') {
          if (parameter[0]==0) {
            int i=getHeatSetpoint();
            quietReply=true;
            sprintf(reply,"%d",i);
          } else
            commandError=true;
        } else
#endif
#if defined(WEATHER_HUMIDITY_ON) && defined(WEATHER_ON)
//  :Gh#  Get relative humidity reading as Float
//         Returns: n.n#
//         where n ranges from 0.0 to 100.0
        if (command[1]=='h') {
          dtostrf(weatherHumidity(),1,1,reply);
          quietReply=true;
        } else
#endif
//  :GP#  Get power status
//         Returns: OK#, OUT#, or N/A#
//         
        if ((command[1]=='P') && (parameter[0]==0)) {
#if defined(STAT_MAINS_SENSE) && defined(WEATHER_ON)
          // check for mains power out
          if (digitalRead(sensePin[STAT_MAINS_SENSE])!=HIGH) strcpy(reply,"OUT"); else strcpy(reply,"OK");
#else
          strcpy(reply,"N/A");
#endif
          quietReply=true;
        } else
//  :GR#  Get rain sensor status
//         Returns: n#
//         -1000 is invalid, 0 is N/A, 1# is Rain, 2# is Warn, and 3# is Dry
        if ((command[1]=='R') && (parameter[0]==0)) {
#if defined(WEATHER_RAIN_ON) && defined(WEATHER_ON)
          sprintf(reply,"%d",weatherRain());
#else
          strcpy(reply,"0");
#endif
          quietReply=true;
        } else
//  :GRn#  Get Relay n state
//         Example: :GR1#
//         Returns: ON#, OFF#, n# (pwm 0-9)
        if ((command[1]=='R') && (parameter[1]==0)) {
          if (((parameter[0]>='1') && (parameter[0]<='9')) || ((parameter[0]>='A') && (parameter[0]<='E'))) {
            int i=parameter[0]-'0'; if (i>9) i-=7;
            quietReply=true;
            if (relayState[i]==0) {
              strcpy(reply,"OFF");
            } else
            if (relayState[i]==1) {
              strcpy(reply,"ON");
            } else
            if (relayState[i]>1) {
              sprintf(reply,"%d",relayState[i]/10);
            } else {
              strcpy(reply,"?");
            }
          } else
            commandError=true;
        } else
//  :GS#  Get averaged sky differential temperature
//         Returns: nnn.n#
//         where <=21 is cloudy
        if ((command[1]=='S') && (parameter[0]==0)) {
          dtostrf(getAvgSkyDiffTemp(),3,1,reply);
          quietReply=true;
        } else
//  :GSn#  Get Digital Sense n state
//         Example: :GS1#
//         Returns: LOW#, HIGH#
        if ((command[1]=='S') && (parameter[1]==0)) {
          if ((parameter[0]>='1') && (parameter[0]<='6')) {
            int i=parameter[0]-'0'; if (i>9) i-=7;
            senseState[i]=digitalRead(sensePin[i]);
            quietReply=true;
            if (senseState[i]==HIGH) strcpy(reply,"HIGH"); else strcpy(reply,"LOW");
          } else
            commandError=true;
        } else
//  :Gs#  Get safety status
//         Example: :Gs#
//         Returns: SAFE#, UNSAFE#
        if ((command[1]=='s') && (parameter[0]==0)) {
          quietReply=true;
          if (isSafe()) strcpy(reply,"SAFE"); else strcpy(reply,"UNSAFE");
        } else
#if defined(THERMOSTAT_ON) && defined(COOL_RELAY)
//  :GV#  Get Cool/Vent setpoint
//         Example: :GC#
//         Returns: 0# or 30#, 0 or temperature in C
        if (command[1]=='V') {
          if (parameter[0]==0) {
            int i=getCoolSetpoint();
            quietReply=true;
            sprintf(reply,"%d",i);
          } else
            commandError=true;
        } else
#endif
//  :GW#  Get wind status
//         Returns: OK#, HIGH#, or N/A#
//         
        if ((command[1]=='W') && (parameter[0]==0)) {
#if defined(WEATHER_WIND_SPD_ON) && defined(WEATHER_ON)
          if (weatherWindspeed()>WEATHER_WIND_SPD_THRESHOLD) strcpy(reply,"HIGH"); else 
          if (weatherWindspeed()==invalid) strcpy(reply,"Invalid"); else strcpy(reply,"OK");
#else
          strcpy(reply,"N/A");
#endif
          quietReply=true;
        } else
          commandError=true;
      } else

//   I - Info Commands -----------------------------------------------------
      if (command[0]=='I') {
//  :IN#  get version Number
//         Returns: s#
        if ((command[1]=='N') && (parameter[0]==0)) {
          strcpy(reply,FirmwareNumber);
          quietReply=true;
        } else
//  :IP#  get Product (compatibility)
//         Returns: s#
        if ((command[1]=='P') && (parameter[0]==0)) {
          strcpy(reply,FirmwareName);
          quietReply=true;
        } else
          commandError=true;
      } else

//   R - Roof Commands -----------------------------------------------------
#ifdef ROR_ON
      if (command[0]=='R') {
//  :RC#  Roof Close
//         Returns: nothing
        if ((command[1]=='C') && (parameter[0]==0)) {
          startRoofClose();
          quietReply=true;
        } else
//  :RO#  Roof Open
//         Returns: nothing
        if ((command[1]=='O') && (parameter[0]==0)) {
          startRoofOpen();
          quietReply=true;
        } else
//  :RH#  Roof Stop
//         Returns: 1 on success
        if ((command[1]=='H') && (parameter[0]==0)) {
          stopRoof();
        } else
//  :R!#  Roof Safety Override
//         Returns: 1 on success
        if ((command[1]=='!') && (parameter[0]==0)) {
          roofSafetyOverride=true;
        } else
//  :R+#  Roof high power mode
//         Returns: 1 on success
        if ((command[1]=='!') && (parameter[0]==0)) {
          roofMaxPower=true;
        } else
//  :RS#  Roof Status
//         Returns: status code
        if ((command[1]=='S') && (parameter[0]==0)) {
          quietReply=true;
          sprintf(reply,"%d",roofStatusRegister);
        } else
//  :RSE#  Roof Status Expanded
//         Returns: status string
        if ((command[1]=='S') && (parameter[0]=='E') && (parameter[1]==0)) {
          quietReply=true;
          senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
          senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
          if ((senseState[ROR_CLOSED_LIMIT_SENSE]) && (!senseState[ROR_OPENED_LIMIT_SENSE])) strcpy(reply,"CLOSED"); else
          if ((!senseState[ROR_CLOSED_LIMIT_SENSE]) && (senseState[ROR_OPENED_LIMIT_SENSE])) strcpy(reply,"OPEN"); else
          strcpy(reply,getRoofStatus().c_str());
        } else
//  :RSL#  Roof Status Last Error
//         Returns: status string
        if ((command[1]=='S') && (parameter[0]=='L') && (parameter[1]==0)) {
          quietReply=true;
          strcpy(reply,roofLastError.c_str());
        } else
          commandError=true;
      } else
#endif

//   S - Set Commands ------------------------------------------------------
      if (command[0]=='S') {
//  :SRn,[state]#  Set Relay n [state] = ON, OFF, DELAY, n (pwm 1-9)
//         Example: :SR1,ON#
//         Returns: 1 on success
        if ((command[1]=='R') && (parameter[1]==',')) {
          if (((parameter[0]>='1') && (parameter[0]<='9')) || ((parameter[0]>='A') && (parameter[0]<='E'))) {
            int i=parameter[0]-'0'; if (i>9) i-=7;
            String ws=String(parameter);
            ws=ws.substring(2);
            if ((i>=1) && (i<=14) && (ws=="DELAY")) {
              relayState[i]=9;
            } else
            if ((i>=1) && (i<=14) && (ws=="ON")) {
              relayState[i]=1; digitalWrite(relayPin[i],HIGH);
            } else
            if ((i>=1) && (i<=14) && (ws=="OFF")) {
              relayState[i]=0; digitalWrite(relayPin[i],LOW);
            } else
            if ((i>=7) && (i<=14) && (ws.length()==1)) {
              int j=ws[0]-'0';
              relayState[i]=j*10;
            } else
              commandError=true;
          } else
            commandError=true;
        } else
#ifdef THERMOSTAT_ON
#ifdef HEAT_RELAY
//  :SHnn#  Set heat nn = temperature in deg. C
//         Example: :SH0# turns heat off
//         Example: :SH21# heat setpoint 21 deg. C
//         Returns: 1 on success
        if (command[1]=='H') {
          String ws=String(parameter);
          int i=ws.toInt();
          if (i==0) {
            setHeatSetpoint(0); digitalWrite(relayPin[HEAT_RELAY], LOW);
          } else
          if ((i>=1) && (i<=40)) {
            setHeatSetpoint(i);
            msFiveMinuteCounter=millis()+5000UL;
          } else
            commandError=true;
        } else
#endif
#ifdef COOL_RELAY
//  :SCnnn#  Set cool nnn = temperature in deg. C
//         Example: :SC0# turns cooling off
//         Example: :SC30# cool setpoint 30 deg. C
//         Returns: 1 on success
        if (command[1]=='C') {
          String ws=String(parameter);
          int i=ws.toInt();
          if (i==0) {
            setCoolSetpoint(0); digitalWrite(relayPin[6], LOW);
          } else
          if ((i>=1) && (i<=40)) {
            setCoolSetpoint(i);
            msFiveMinuteCounter=millis()+5000UL;
          } else
          commandError=true;
        } else
#endif
#endif
        commandError=true;

      } else 
        commandError=true;
      
      if (!quietReply) {
        if (commandError) reply[0]='0'; else reply[0]='1';
        reply[1]=0;
        supress_frame=true;
      }
      
      if (strlen(reply)>0) {
        if (process_command==COMMAND_SERIAL) {
          if (cmd.checksum) checksum(reply);
          if (!supress_frame) strcat(reply,"#");
          Serial.print(reply);
        }
        if (process_command==COMMAND_ETHERNET) {
          if (cmde.checksum) checksum(reply);
          if (!supress_frame) strcat(reply,"#");
          Cmd.print(reply);
        }
        if (process_command==COMMAND_ETHERNET1) {
          if (cmde1.checksum) checksum(reply);
          if (!supress_frame) strcat(reply,"#");
          Cmd1.print(reply);
        }
      }
      quietReply=false;
   }
}

// calculate the checksum and add to string
void checksum(char s[]) {
  char HEXS[3]="";
  byte cks=0; for (unsigned int cksCount0=0; cksCount0<strlen(s); cksCount0++) {  cks+=s[cksCount0]; }
  sprintf(HEXS,"%02X",cks);
  strcat(s,HEXS);
}

