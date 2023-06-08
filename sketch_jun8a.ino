 /*
  TFT_BLACK
 TFT_ORANGE
  TFT_DARKGREEN
 TFT_DARKCYAN
   TFT_MAROON
  TFT_PURPLE
  TFT_OLIVE
  TFT_DARKGREY
 TFT_ORANGE
TFT_BLUE
TFT_GREEN
TFT_CYAN
 TFT_RED
TFT_NAVY
TFT_YELLOW
TFT_WHITE
*/





#include <TFT_eSPI.h>
#include <SPI.h>       // this is needed for display

#include <Keypad.h>



#define buzzer 5
// تعيين الاطراف 
#define TFT_CS 15    
#define TFT_DC 2
#define TFT_MOSI 23
#define TFT_SCLK 18
// ///////////////////////////
#define c 261
#define d 294
#define f 349
#define c 523


TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height



unsigned long previousMillis = 0;  // will store last time LED was updated
volatile unsigned long currentMillis = millis();

volatile long interval = 50000;  // interval at which to blink (milliseconds)
volatile char key_press ;


uint16_t y =0;
uint16_t x = tft.width() / 2; // Position of centre of arc
uint16_t h = tft.height()/2;
uint16_t count  =0;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
uint8_t colPins[COLS] = { 26, 25, 33, 32 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 13, 12, 14, 27 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/////////////state variable   متغيرات الخطوة
volatile uint8_t page_count =0;    // الصفحة
volatile uint8_t welcome_steps = 0;  // الصفحة الترحيبية
volatile uint8_t level_steps = 0;   // تحديد المستوى
volatile uint8_t game_steps = 0;   // اللعبة
volatile uint8_t last_steps = 0;   // الصفحة النهائية للنتيجة


/////////////////////////

void welcome();
void level();
void game();
void last();
void buzr ();


void setup(void) {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
 welcome();
}






void loop()
{

 currentMillis = millis();
 key_press = keypad.getKey();

  // if (key_press != NO_KEY) {
  //   Serial.println(key_press);
  // }

/////////////// page scan
if( key_press == 65){
  buzr();
 key_press = NO_KEY;
page_count ++;
  if (page_count == 4){
page_count = 0;

  }
}



//////////////////// page print


if( page_count == 0){
welcome();

level_steps=0;
game_steps = 0;
last_steps = 0;

}
if(page_count == 1){
  level();

welcome_steps =0; 
game_steps = 0;
last_steps = 0;

}

if(page_count == 2){
game();

welcome_steps =0; 
level_steps=0;
last_steps = 0;

}

if(page_count == 3){
last();

welcome_steps =0; 
level_steps=0;
game_steps = 0;


}

//////////////////////////






}





void welcome(){

if(welcome_steps == 0){
 tft.fillScreen(TFT_BLACK);

 tft.setCursor(50, 10, 4);
tft.setTextColor(TFT_GREEN,TFT_BLACK);
tft.print("welcome");

tft.print("                                                               ");

tft.print("ADEL");
tft.print(" ");
tft.print("ALJOHANI");

tft.println(" ");

tft.print("ALAA");
tft.print(" ");
tft.print("HUOSH");

tft.println("");

tft.print("THE_MOVVING");
tft.print(" ");
tft.print("BALL");
 welcome_steps++;
}




}



volatile int t_x0 =140 ;
volatile int t_y0 =20 ;
volatile int t_x1 =180 ;
volatile int t_y1 =5 ;
volatile int t_x2 =180 ;
volatile int t_y2 =30 ;

volatile int inc_level =0 ;    ///للزيادة


void level(){

if(level_steps == 0){
 tft.fillScreen(TFT_BLACK);
 level_steps++;
}

if(level_steps == 1){

tft.setCursor(50, 10, 4);
tft.setTextColor(TFT_GREEN,TFT_BLACK);
tft.println("Hard");
tft.setCursor(50, 50, 4);
tft.println("Normal");
tft.setCursor(50, 90, 4);
tft.println("easy");

level_steps++;

}





if(level_steps == 2){

 ///               x ,y  , x1,y1, x2,y2
tft.fillTriangle(t_x0,(t_y0 + inc_level) ,t_x1,(t_y1+ inc_level),t_x2,(t_y2+ inc_level),TFT_RED);

 if( key_press == '8'){
   buzr();
   ///               x ,y  , x1,y1, x2,y2
tft.fillTriangle(t_x0,(t_y0 + inc_level) ,t_x1,(t_y1+ inc_level),t_x2,(t_y2+ inc_level),TFT_BLACK);
 inc_level = inc_level +40;
 interval = interval + 1000;
 }


 if( inc_level == 120  ){
inc_level = 0;
interval = 1000;
 }




}
}


volatile int c_x =85 ;   //موقع الدائرة
volatile int c_y =215 ;   // مقع الدائرة

volatile int inc_game_x =2 ;    ///للزيادة
volatile int inc_game_y =2 ;    ///للزيادة


// uint16_t rec_x = tft.width() / 2; // نقطة بداية الطباعة للمربع  
// uint16_t rec_y = tft.height()/2; //  نقطة بداية الطباعة للمربع

uint16_t rec1_x = +5;
uint16_t rec1_y = 275;

uint16_t rec2_x = +5;
uint16_t rec2_y = +120;

uint16_t rec3_x = +190;
uint16_t rec3_y = 275;

uint16_t rec4_x = +190;
uint16_t rec4_y = +120;


volatile int b_l = 20 ;    ///حجم قطر الدائرة
//////////////////////////// لجمع النقاط

//فوق
volatile int b_2 = 10 ;    ///حجم قطر الدائرة
volatile int p1_x = 80;    //مكان النقطة الاولى
volatile int p1_y = 160;   //مكان النقطة الاولى
volatile int p1_f = 0;    //متغير التقاط النقطة

volatile int b_3 = 10 ;    
volatile int p3_x = 120;    
volatile int p3_y = 160;  
volatile int p3_f = 0;    

volatile int b_4 = 10 ;  
volatile int p4_x = 160;
volatile int p4_y = 160;
volatile int p4_f = 0; 
//اليمين
volatile int b_5 = 10 ;  
volatile int p5_x = 100;
volatile int p5_y = 100;
volatile int p5_f = 0; 

volatile int b_6 = 10 ;  
volatile int p6_x = 100;
volatile int p6_y = 100;
volatile int p6_f = 0; 

volatile int b_7 = 10 ;  
volatile int p7_x = 100;
volatile int p7_y = 100;
volatile int p7_f = 0; 
//يسار
volatile int b_8 = 10 ;  
volatile int p8_x = 100;
volatile int p8_y = 100;
volatile int p8_f = 0; 

volatile int b_9 = 10 ;  
volatile int p9_x = 100;
volatile int p9_y = 100;
volatile int p9_f = 0; 

volatile int b_10 = 10 ;  
volatile int p10_x = 100;
volatile int p10_y = 100;
volatile int p10_f = 0; 
//تحت
volatile int b_11 = 10 ;  
volatile int p11_x = 100;
volatile int p11_y = 100;
volatile int p11_f = 0; 

volatile int b_12 = 10 ;  
volatile int p12_x = 100;
volatile int p12_y = 100;
volatile int p12_f = 0; 

volatile int b_13 = 10 ;  
volatile int p13_x = 100;
volatile int p13_y = 100;
volatile int p13_f = 0; 

volatile int score =0;  //// مجموع النقاط



void game(){

if(game_steps == 0){
tft.fillScreen(TFT_BLACK);

//  المربع   x y  العرض الطول

tft.fillRect(rec1_x, rec1_y,40,40, TFT_BLUE);
tft.fillRect(rec2_x, rec2_y,40,40, TFT_BLUE);
tft.fillRect(rec3_x, rec3_y,40,40, TFT_BLUE);
tft.fillRect(rec4_x, rec4_y,40,40, TFT_BLUE); 

//الناقط على فوق
tft.fillSmoothCircle(p1_x  , p1_y , b_2, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(120  , 160  , b_3, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(160  , 160  , b_4, TFT_YELLOW,TFT_YELLOW) ;
//النقاط على اليمين
tft.fillSmoothCircle(200  , 180 , b_5, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(200  , 220  , b_6, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(200  , 260 , b_7, TFT_YELLOW,TFT_YELLOW) ;
//النقاط على اليسار
tft.fillSmoothCircle(50  , 180 , b_8, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(50  , 220  , b_9, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(50  , 260 , b_10, TFT_YELLOW,TFT_YELLOW) ;
//النقاط على تحت
tft.fillSmoothCircle(80  , 290 , b_11, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(120  , 290  , b_12, TFT_YELLOW,TFT_YELLOW) ;
tft.fillSmoothCircle(160  , 290  , b_13, TFT_YELLOW,TFT_YELLOW) ;

 game_steps ++;

}

//////////////////////////////////////



if(game_steps == 1){
if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    page_count++;

    }



tft.fillSmoothCircle((c_x + inc_game_x), (c_y + inc_game_y), b_l, TFT_RED,TFT_RED) ;

if( ((c_y + inc_game_y) == p1_y) && ((c_x + inc_game_x) == p1_x) && (p1_f == 0)  ){
Serial.println("print me");
p1_f =1;
score ++;
}




if (key_press == '2' ){
  buzr();
  tft.fillSmoothCircle((c_x + inc_game_x), (c_y + inc_game_y), b_l, TFT_BLACK,TFT_BLACK) ;
  inc_game_y = inc_game_y -20 ;

if (   ((c_y + inc_game_y) <= (rec1_y +50) )
    && ((c_x + inc_game_x) >= ( rec1_x -20) )
    && ((c_x + inc_game_x) <=  (rec1_x +50) )      ){

      inc_game_y = inc_game_y + 20 ;



    }




Serial.println("X");
Serial.println((c_x + inc_game_x));
}

if (key_press == '5' ){
  buzr();
  tft.fillSmoothCircle((c_x + inc_game_x), (c_y + inc_game_y), b_l, TFT_BLACK,TFT_BLACK) ;

inc_game_y = inc_game_y +20 ;

if (   ((c_y + inc_game_y) >= (rec1_y -20) )
    && ((c_x + inc_game_x) >= ( rec1_x -20) )
    && ((c_x + inc_game_x) <=  (rec1_x +50) )      ){

      inc_game_y = inc_game_y - 20 ;



    }
Serial.println("y");
Serial.println((c_y + inc_game_y));


}
if (key_press == '4' ){
  buzr();
  tft.fillSmoothCircle((c_x + inc_game_x), (c_y + inc_game_y), b_l, TFT_BLACK,TFT_BLACK) ;

  inc_game_x = inc_game_x -20 ;

if (   ((c_x + inc_game_x) <= (rec1_x +50) )
    && ((c_y + inc_game_y) >= ( rec1_y +40) )  
    && ((c_y + inc_game_y) <=  (rec1_y -40) )      ){

      inc_game_x = inc_game_x + 20 ;



    }



}

if (key_press == '6' ){
  buzr();
  tft.fillSmoothCircle((c_x + inc_game_x), (c_y + inc_game_y), b_l, TFT_BLACK,TFT_BLACK) ;
inc_game_x = inc_game_x +20 ;

if (   ((c_x + inc_game_x) >= (rec1_x -20) )
    && ((c_y + inc_game_y) >= ( rec1_y -20) )
    && ((c_y + inc_game_y) <=  (rec1_y +40) )      ){

      inc_game_x = inc_game_x - 20 ;



    }

}





}






}
void last(){
  tft.setCursor(150, 150, 4);
tft.setTextColor(TFT_CYAN,TFT_BLACK);
 tft.drawString(String(score),20,230,7); // طباعة القيمة بالمتغير x  بالموقع 20 و 240 و حجم خط 7
  if(last_steps == 0){
 tft.fillScreen(TFT_BLACK);
tft.setCursor(50, 10, 4);
tft.setTextColor(TFT_YELLOW,TFT_BLACK);
tft.print("                   ");
tft.setCursor(50, 10, 4);
tft.setTextColor(TFT_RED,TFT_BLACK);
tft.print("GAME");
tft.print(" ");
tft.print("OVER");

tft.setCursor(100, 242, 4);
tft.setTextColor(TFT_NAVY,TFT_BLACK);
tone(buzzer,200);
  delay(500);
 tone(buzzer,400);
  delay(500);
 tone(buzzer,600);
  delay(500);
 tone(buzzer,800);
  delay(500);
 tone(buzzer,1000);
  delay(500);
tone(buzzer,0);


last_steps ++;
}




}

void buzr (){

  tone(buzzer,1915);
  delay(10);
  tone(buzzer,0);


}
