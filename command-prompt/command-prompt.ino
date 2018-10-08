void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Terminal Example");

  Serial.println("d) Dial position");
  Serial.println("t) Go home");
}

void loop() {
  // put your main code here, to run repeatedly:
  byte incoming;
  if (Serial.available()) {
    incoming = Serial.read();
    Serial.print("You pressed: ");
    Serial.write(incoming);
    Serial.println();

    if (incoming == 'd') {
      Serial.print("Enter dial position: ");
      while (!Serial.available());
      int dialPosition = Serial.parseInt();

      Serial.print("You told me to go to ");
      Serial.println(dialPosition);
    }
  }
}
