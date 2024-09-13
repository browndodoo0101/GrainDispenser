/*
Function used to select the type of grain to dispense
Written: 23/08/2024
*/
char selectGrain(void) {
      //Store user input
    lcd.clear();
    char key = keypad.getKey();
    while(!(isAlpha(key)) ){
    lcd.setCursor(0, 0);
    lcd.print(grains1);
    lcd.setCursor(0, 1);
    lcd.print(grains2);
    key = keypad.getKey();
  }
  lcd.clear();
  return key;
}

/*
Function used to input weight of grains
Written: 24/08/2024
*/
String weightInput(){
  bool loop = true; //Loop condition
  String myWeight; //Desired weight of grains
  String _myWeight; //Dummy variable to store weight
  char key;

  lcd.setCursor(0, 0);
  lcd.print("Kilo ngapi za ");
  lcd.print(grainSelected);
  lcd.print("?");

  while(loop){
     //Print the pressed key
  char key = keypad.getKey();

  if(key){   
    if(key == '#') {
      myWeight = _myWeight;
      _myWeight = "";
      lcd.setCursor(0, 1);
      lcd.print(myWeight);
      delay(100);
      lcd.clear();
      break;
      }
    if(!isAlpha(key)){
       _myWeight.concat(key);
      lcd.setCursor(0, 1);
      lcd.print(_myWeight);
    }   
    }
  }
  return myWeight;
}

/*Verify weight input
Written: 24/08/2024
*/
String correctWeight(){
  //Loop status
  bool status = true;

  String msg1 = "Mmh! Kilo mbaya";
  String msg2 = "CHINI:0.1 JUU:19";

  while(status){
  String _weight = weightInput();
  float _weigh = _weight.toFloat();
  String weight = String(_weigh, 1);
  float weigh = weight.toFloat();
  
  if(weigh < 19.0 && weigh > 0.0) return weight;
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    delay(3000);
    lcd.clear();  
    } 
  }
}

/*
Verifies user input
Written: 25/08/2024
*/
void verify(){
  bool loop = true;

  while(loop){
    lcd.setCursor(0, 0);
    lcd.print("Kilo ");
    lcd.print(weightSelected);
    lcd.print(" za ");
    lcd.print(grainSelected);
    lcd.print("?");
    lcd.setCursor(0, 1);
    lcd.print("*.Sawa #.Hapana");
    
    char key = keypad.getKey();
    if(key){
    if(key == '.') {
      lcd.clear();
      delay(100);
      break;
    }
    else if(key == '#'){
      grainSelected = selectGrain();
      weightSelected = correctWeight();       
    }
    }
  }
  delay(200);
}
