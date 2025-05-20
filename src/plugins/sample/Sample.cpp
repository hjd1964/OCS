// Sample plugin

#include "Sample.h"
#include "../../Common.h"
#include "../../lib/tasks/OnTask.h"

#include "../../observatory/safety/Safety.h"

void sampleWrapper() { sample.loop(); }

void Sample::init() {
  VLF("MSG: Plugins, starting: sample");

  // start a task that runs once every five seconds, run at priority level 7 so
  // we can block using tasks.yield(); fairly aggressively without significant impact on operation
  tasks.add(5000, 0, true, 7, sampleWrapper);
}

void Sample::loop() {
  Serial.print("OCS is reporting ");
  if (safety.isSafe()) Serial.println("safe"); else Serial.println("unsafe");
}

// no command processing in this example, so just return false (not handled)
bool Sample::command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError) {
  UNUSED(*reply);
  UNUSED(*command);
  UNUSED(*parameter);
  UNUSED(*supressFrame);
  UNUSED(*numericReply);
  UNUSED(*commandError);
  return false;
}

Sample sample;
