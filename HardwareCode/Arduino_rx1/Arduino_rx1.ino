void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String string = "";
char letter = 0;
int wait = 0;

void loop() 
{
  // put your main code here, to run repeatedly:

    if (Serial.available() > 0) 
    {
      wait = 0;
      letter = Serial.read();
      if (letter != '\n') {
      // a character of the string was received
        string += letter;
      }
      else {
      // end of string
      }
    } 
    else 
    {
      delay(100);
      if(string != ""){
      Serial.println(string);
      string = "";
      }
    }
}
