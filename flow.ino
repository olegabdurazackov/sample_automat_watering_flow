/*************
  Пример автомата полива комнатных цветов

  Полив производится в дневное время
  в течении 3 секунд (агумент функцмм poliw)

  Датчиком освещенности служит светодиод АЛ307.

  Датчик влажности выполнен из провода ПЭВ 
  длиной 2х100мм с залуженными рабочими поверхностями.
  Для исключения гальванического эффекта напряжение
  на датчик подается только на время измерения.

  Сигнальный светодиод led подает следующие сигналы:
      -первый:
          --длинный (день) : полив разрешен,
          --короткий (ночь): полив запрещен;
      -второй :
          --длинный (влажно): полив запрещен,
          --короткий (сухо): полив разрешен.
  При аварийной ситуации (нет воды в баке, обрыв шлангов и пр.)
  светодиод led подает сигнал Морзе SOS.

  Если не нужна экономия энергии библиотеку Narcoleptic 
  можно не использовать.

**************/

#include "Narcoleptic.h"
//#define debug true

// pins
#define d_swet A2
#define d_wlagn A3
const int u_pitanie_d_wlagn=7; // вкл.питания датчика влажн.
const int nasos=8;
const int led=13;

// consts
const int wlagn_porog=512;
const int swet_porog=150;

// bools
bool day=false;
bool suho=false;
bool err=false;

int test(int land=1000){
    Serial.println(F("Start test programm:"));
    digitalWrite(led,HIGH);
    Serial.print(F("swet = "));
    Serial.println(analogRead(d_swet));
    digitalWrite(u_pitanie_d_wlagn,HIGH);
    Serial.print(F("wlagn = "));
    delay(100);
    Serial.println(analogRead(d_wlagn));
    Serial.println(F("Start nasos "));
    digitalWrite(nasos,LOW);
    Serial.print(F("Delay, ms = "));
    Serial.println(land);
    delay(land);
    Serial.println(F("Reset"));
    digitalWrite(u_pitanie_d_wlagn,LOW);
    digitalWrite(nasos,HIGH);
    digitalWrite(led,LOW);
    return 1;
}


bool is_day(){
    if (analogRead(d_swet)>swet_porog){
        day=true;
    }else{
        day=false;
        err=false;
    }
    return day;
}

bool is_suho(){
    digitalWrite(u_pitanie_d_wlagn,HIGH);
    if (analogRead(d_wlagn)>wlagn_porog){
        suho=true;
    }else{
        suho=false;
        err=false;
    }
    digitalWrite(u_pitanie_d_wlagn,LOW);
    return suho;
}

int poliw(int land=3000){
    digitalWrite(nasos,LOW);
    #if debug
        Serial.print(F("Poliw start"));
    #endif
    delay(land);
    #if debug 
        Serial.println(F(" -- end"));
    #endif
    digitalWrite(nasos,HIGH);
    err=is_suho();
    return 1;
}

int beep(int land=200){
    delay(200);
    digitalWrite(led,HIGH);
    delay(land);
    digitalWrite(led,LOW);
    delay(200);
    return 1;
}

int s(int land=100){
    for (int i =0;i<3;i++){
        delay(150);
        digitalWrite(led,HIGH);
        delay(land);
        digitalWrite(led,LOW);
    }
    delay(150);
    return 1;
}
int o(int land=300){
    for (int i =0;i<3;i++){
        delay(150);
        digitalWrite(led,HIGH);
        delay(land);
        digitalWrite(led,LOW);
    }
    delay(150);
    return 1;
}
int sos(){
    s();o();s();
    return 1;
}
int signal(){
    if (day){
        beep();
    }else{
        beep(800);
    }

    if (suho){
        beep();
    }else{
        beep(800);
    }
    return 1;

}

void setup() {
    Serial.begin(9600);
    pinMode(u_pitanie_d_wlagn,OUTPUT);
    pinMode(led,OUTPUT);
    pinMode(nasos,OUTPUT);
    digitalWrite(u_pitanie_d_wlagn,LOW);
    digitalWrite(led,LOW);
    digitalWrite(nasos,HIGH);// насос отключить
    test();

}

void loop() {
    is_day();
    is_suho();
    if (err){
        sos();
    }else{
        signal();
    }

    if (suho && day && !err){
        poliw();
    }
    
    #if debug
        Serial.print(F("day = "));Serial.println(day);
        Serial.print(F("suho = "));Serial.println(suho);
        Serial.print(F("err = "));Serial.println(err);
    #endif

    Narcoleptic.delay(5000);

}
