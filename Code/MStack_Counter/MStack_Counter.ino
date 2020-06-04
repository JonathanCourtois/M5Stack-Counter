#include<M5Stack.h>

// sensors pin
const int trigPin = 22;
const int echoPin = 21;
const int trigPin2 = 16;
const int echoPin2 = 17;

// Variables
  // Distance tmp
float dist, dist2;
float oldDist, oldDist2;
  // room area
long area = 0 ;
  // timer loop -> display update
unsigned long timerLoop = millis();
  // To know which menu is highlighted and selected
int select[4];
int buttonSelect = 0;
int menu = 0;
  // To know which action is done
int action; //action {0, 1, 2, 3} -> {None, buttonA, buttonB, buttonC}
  // some usefull boolean 
bool refresh = false;
bool aeraAutoCount = false;
bool majDistance = false;
  // Peoples number count
unsigned int peoplesNumber = 0;

// area int 
int digits[] = {0,1,2,3,4,5,6,7,8,9};
  // iD[0] = 10e3, iD[1] = 10e2, iD[2] = 10e1, iD[3] = 10e0
int indexDigits[] = {0,0,0,0};
  // to know which digit has to be modify
int modifDigit = 0; 
int selectDigits[] = {1,0,0,0};

  // define the perfect gray color <3
#define GRAY  BLUE+0.3*RED

// distance function working with the ultrasonic sensors
// write by ltombak
double distance(int triggerPin, int echoPin){
  
  float SOUND_SPEED = 340.0 / 1000; // son speed in mm/uS
  unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m at 340m/s
  
  digitalWrite(triggerPin, LOW);// checking if the sensor is low
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);// Wake up the sensor for 10uS
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);// Switch off

  long measure = pulseIn(echoPin, HIGH, MEASURE_TIMEOUT);// measuring ultrasonic impulsion time and echo (if exist)
  float distance_cm = measure / 2.0 * SOUND_SPEED;// convert echo time to distance

  if (distance_cm < 1 || distance_cm > 3000) {// checking if the distance is ok
        return -1.0 ;// if not, sending error value
    } else {
        return (distance_cm / 10.0);// sending cm distance
    }
}

// update the distance with the two sensors
void takeDistance(){
  dist = 0;
  dist2 = 0;
  for(int i=0;i<5;i++){
    dist += distance(trigPin, echoPin);
    delay(5);
    dist2 += distance(trigPin2, echoPin2);
    delay(5);
  }
  dist /= 5;
  dist2 /= 5;
}

// draw a button, start at x and y, with w (width), h (height), 
//              backC : Background color
//              textC : Text Color
//              btn1 : String displayed on the sensor
void drawButton(int x, int y, int w, int h, uint16_t backC, uint16_t textC , String btn1, bool center, bool highlight){
  M5.Lcd.setTextColor(textC);
  if (highlight){
    M5.Lcd.fillRoundRect(x-2, y-2, w+4 , h+4, 12,WHITE);
  }
  M5.Lcd.fillRoundRect(x, y, w , h, 10,backC); 
  if (center){
    M5.Lcd.setCursor(x+int(w/2)-int(btn1.length()*6) , y+8); 
  }
  else {
    M5.Lcd.setCursor(x+5 , y+8); 
  }
  
  M5.Lcd.print(btn1);
}

// drawing the action button legend on the buttom screen
void drawButtonSection(String btn1, String btn2, String btn3){
  M5.Lcd.setTextSize(2);
  drawButton(35,205,70,30,GRAY,WHITE,btn1,true,false);
  drawButton(128,205,70,30,GRAY,WHITE,btn2,true,false);
  drawButton(222,205,70,30,GRAY,WHITE,btn3,true,false);
}

// reseting the select variable to enable loop in menu navigation -> 0 -> 1 -> 2 -> 3 -> 0 ...
void resetSelect(){
  for(int i=0;i<4;i++){
    select[i]=0;
  }
}

// Menu Function 
String btnName1, btnName2, btnName3;

// Preparing the highlight boolean array
// telling wich button has to be highlitgh 
void nextButton(){
  buttonSelect += 1;
  resetSelect();
  if(buttonSelect >=4){
    buttonSelect = 0;
  }
  select[buttonSelect]=1;
}

// area calcul, all the digits to a number : [0 0 3 0] -> 30
void MAJarea() {
  area = digits[indexDigits[0]]*1000 + digits[indexDigits[1]]*100 + digits[indexDigits[2]]*10 + digits[indexDigits[3]];
}

// Lock the counter menu acces if you chose a area limited counter
// but without entering a area value
void popuparea(){
  M5.Lcd.setTextSize(2);
  drawButton(30,30,270,140,GRAY,RED,String(""),true,true);
  drawButton(40,85,250,30,GRAY,RED,String("! AREA INVALID !"),true,false);
  // option button section
  btnName1 = String("");
  btnName2 = String("Ok");
  btnName3 = String("");
  
  drawButtonSection( btnName1, btnName2, btnName3);
  while(not(M5.BtnB.wasReleased())){
    M5.update();  
  }
  return;
}

// First menu, Option Menu
void menuOption (){
  // action selection {none, btnA, btnB, btnC}
  switch(action){
    case 1: // btnA : Next button
      // Highlight the next button
      nextButton();
      break;
    case 2: // btnB : OK
      switch(buttonSelect){
        case 0: // activate the auto count of peoples
          aeraAutoCount = not(aeraAutoCount);
          break;
        case 1: // Go to area menu
          action = 0;
          menu = 2;
          menuarea();
          return;
          
        case 2: // Go to the counter
          action = 0;
          if (aeraAutoCount and area < 10){
            // if the area is invalid
            // we return to option screen
            popuparea();
            menu = 0;
            buttonSelect = 0;
            nextButton();
            break;
          }
          menu = 3;
          menuCounter();
          return;
        case 3: // Go to the distance menu
          menu = 4;
          action = 0;
          menuDistance();
          return;
        default:
          break;
      }
    default:
      break;
  }
  // Background 
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(100, 10);
  M5.Lcd.print("OPTION:");
  M5.Lcd.setTextSize(2);
  // drawing button section
  drawButton(20,40,220,30,GRAY,WHITE,String("Auto counter:"),false,select[0]==1);
    // display auto count bolean
  if (aeraAutoCount){
    drawButton(165,40,70,30,GRAY,GREEN,String("true "),false,false);
  }
  else {
    drawButton(165, 40,70,30,GRAY,RED,String("false"),false,false);
  }
  drawButton(20,80,220,30,GRAY,WHITE,String("area limit..."),false,select[1]==1);
  drawButton(20,120,220,30,GRAY,WHITE,String("Counter..."),false,select[2]==1); 
  drawButton(20,160,220,30,GRAY,WHITE,String("Distance..."),false,select[3]==1); 

  // option button section
  btnName1 = String("Next");
  btnName2 = String("Ok");
  btnName3 = String("");
  
  drawButtonSection( btnName1, btnName2, btnName3);

}

// tell wich digits is selected, highlighted and has to be modify
void digitSelection(){
  modifDigit += 1;
  for (int i=0;i<4;i++){
    selectDigits[i] = 0;
  }
  if (modifDigit>3){
    modifDigit=0;
  }
  selectDigits[modifDigit] = 1;
}

// area menu
void menuarea(){
  majDistance = true;
  // action selection {none, btnA, btnB, btnC}
  switch(action){
    case 0:
      break;
    case 1: // btnA : highlight next digit
      digitSelection();
      break;
    case 2: // btnB : add one to the selected digit
      indexDigits[modifDigit] +=1;
      if(indexDigits[modifDigit]>9){
        indexDigits[modifDigit]=0;
      }
      break;
    case 3: // Return to the option menu btnC
      menu = 0;
      action = 0;
      menuOption();
      return;
    default:
      break;
  }
  // Background 
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(100, 10);
  M5.Lcd.print("AREA:");
  // Writing poeples number
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.println("Shop area");
  MAJarea();
  M5.Lcd.setTextSize(5);
  for (int i=0;i<4;i++){    
    drawButton(30+int(i*40),75,35,50,BLACK,WHITE,String(digits[indexDigits[i]]),false,selectDigits[i]==1);
  }
  
  M5.Lcd.setCursor(200, 80);
  M5.Lcd.print("m");
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(230, 75);
  M5.Lcd.print("2");

  // option button section
  btnName1 = String("Next");
  btnName2 = String("+1");
  btnName3 = String("Back");
  
  drawButtonSection( btnName1, btnName2, btnName3);
}

// Counter Menu
void menuCounter(){
  // Activate the Distance display update
  majDistance = true;
  // action selection {none, btnA, btnB, btnC}
  switch(action){
    case 0:
      break;
    case 1: // btnA : reset
      peoplesNumber = 0;
      break;
    case 2: // btnB : add one people
      peoplesNumber += 1;
      break;
    case 3: // return to the option menu btnC
      menu = 0;
      action = 0;
      menuOption();
      return;
    default:
      break;
  }
  // Background 
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(90, 10);
  M5.Lcd.print("COUNTER:");
  // Writing poeples number
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.println("Poeples in the shop");

  // testing if a people limit is set
  if (aeraAutoCount and area > 10){
    displayCountValue();
    M5.Lcd.setCursor(180,100);
    M5.Lcd.print("/");
    M5.Lcd.print(int(area / 10));
    M5.Lcd.setTextColor(WHITE);
  }
  else {
    M5.Lcd.setTextColor(WHITE);
    displayCountValue();
  }
  // option button section
  btnName1 = String("Reset");
  btnName2 = String("+1");
  btnName3 = String("Back");
  
  drawButtonSection( btnName1, btnName2, btnName3);
}

// Updating the count value display
void displayCountValue(){
  compteurDetection();
  M5.Lcd.setTextSize(5);
  M5.Lcd.fillRect(10, 90, 150, 50, BLACK);
  M5.Lcd.setCursor(10,90);
  if (peoplesNumber > 999){
    peoplesNumber=0;
  }
  // write in red if we aproch or reach the limit
  if(peoplesNumber >= int(area / 10)-1) {
    M5.Lcd.setTextColor(RED);
  }
  M5.Lcd.print(peoplesNumber);
    M5.Lcd.setTextColor(WHITE);
}

// Updating the distance display
void displayDistValue(){
  M5.Lcd.setTextSize(5);
  M5.Lcd.fillRect(10, 75, 300, 50, BLACK);
  M5.Lcd.setCursor(10, 75);
  if(dist < 0){
    M5.Lcd.print("Erreur"); 
  }
  else{
    M5.Lcd.print(dist);
    M5.Lcd.print(" cm");
  }
  M5.Lcd.fillRect(10, 150, 300, 50, BLACK);
  M5.Lcd.setCursor(10,150);
  if(dist2 < 0){
    M5.Lcd.print("Erreur"); 
  }
  else{
    M5.Lcd.print(dist2);
    M5.Lcd.print(" cm");
  }
}

// Distance menu
void menuDistance(){
  majDistance = true;
  // action selection {none, btnA, btnB, btnC}
  switch(action){
    case 0:
      break;
    case 1: // btnA
      break;
    case 2: // btnB
      break;
    case 3: // retun to the option menu btnC
      menu = 0;
      action = 0;
      menuOption();
      return;
    default:
      break;
  }
  // Background 
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(90, 10);
  M5.Lcd.print("DISTANCE:");
  // Writing poeples numbe
    // text
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.print("Sensor 1 :");
  M5.Lcd.setCursor(5, 125);
  M5.Lcd.print("Sensor 2 :");
    // value
  displayDistValue();
  // option button section
  btnName1 = String("");
  btnName2 = String("");
  btnName3 = String("Back");
  
  drawButtonSection( btnName1, btnName2, btnName3);
}

// refresh dpisplay each 500ms
void distanceMajTimerLoop(){
  if (majDistance){ // if the maj distance is asked
    if (micros() - timerLoop > 500){ //and the timer is out the time loop
      switch(menu){
        case 3: // counter menu
          displayCountValue();// refresh poeple count value on the screen
          break;
        case 4: // Distance menu
          displayDistValue(); // refresh value on the screen
          break;
        default:
        break;
      }
      timerLoop = micros(); // reset the timer
    }
  }
 
}

// detect the peoples direction add tell if 
// they are entering or exiting
void compteurDetection(){
  if(oldDist-dist > 20){ // input detection
    while ( oldDist2-dist2 < 21 and oldDist-dist > 20){
      M5.Lcd.setTextSize(2);
      M5.Lcd.fillRect(90, 150, 100, 50, BLACK);
      takeDistance();
      if (oldDist2-dist2 > 20 ){
        peoplesNumber += 1;
        return;
      }
      delay(2);
    }
  }
  else if(oldDist2-dist2 > 20){ // output detection
      M5.Lcd.setTextSize(2);
    while ( oldDist-dist < 21 and oldDist2-dist2 > 20){
      M5.Lcd.fillRect(90, 150, 100, 50, BLACK);
      takeDistance();
      if (oldDist-dist > 20 ){
        peoplesNumber -= 1;
        return;
      }
      delay(2);
    }
  }
  return;
}


void setup() {
  M5.begin();
  // pinmod for ultrasonic sensors
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  // init to the first selection button
  select[0] = 1;
  menu = 0;
  // display the option menu
  menuOption();
}

void loop() {
  M5.update();
  oldDist = dist;
  oldDist2 = dist2;

  // updating distance
  takeDistance();
  
  if (refresh){
    switch(menu){
      case 0: // Option menu
        majDistance = false;
        menuOption();
        
        break;
      case 1: // area limite menu
        majDistance = false;
        break;
      case 2: // area modif menu
        majDistance = false;
        menuarea();
        break;
      case 3: // counter menu
        menuCounter();
        break;
      case 4: // Distance menu
        menuDistance();
        break;
      default:
        menu = 0;
        break;
    }
    refresh = false;
  }

  // action button section
  action = 0;
  if (M5.BtnA.wasReleased()) {
    action = 1;
    refresh = true;
  }
  if (M5.BtnB.wasReleased()) {
    action = 2;
    refresh = true;
  }
  if (M5.BtnC.wasReleased()) {
    action = 3;
    refresh = true;
     
  }
  distanceMajTimerLoop();
}
