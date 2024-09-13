/*
Prints the weight to one decimal place
Written: 25/08/2024
*/
//Print the weight to one decimal place
String weigh(void){
  data_x = scale.getValue();
  weight = _slope * data_x + _intercept;

  float weight_kg = float(weight) / 1000;
  return String(abs(weight_kg), 1);
}

/*
Grain outlet opens until desired weight has been measured
Prompts added on Tues, 27/08/2024
*/
void dispense(){
  String actualWeight = weigh();

    lcd.setCursor(0, 0);
    lcd.print("Inapima...");
    lcd.setCursor(0, 1);
    lcd.print("Kilo ");

  while(!weightSelected.equals(actualWeight)) {
    openLid();
    lcd.setCursor(5, 1);
    lcd.print(actualWeight);
    actualWeight = weigh();
  }
    closeLid();
    lcd.clear();
    lcd.print("Tayari!");
    delay(1000);
}

//openLid() function opens the lid of the container
void openLid() {
  servo.write(153);
  servo.write(100);
}

//closeLid() function closes the lid of the servo
void closeLid() {
  servo.write(100);
  servo.write(153);
}