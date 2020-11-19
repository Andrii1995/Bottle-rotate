/*
  Created 2016
  by AlexGyver
  AlexGyver Home Labs Inc.
*/
int base = 195; // відстань до площини
int side1 = 53; // вужча сторона
int side2 = 67; // ширша сторона
int times1 = 1000; // затриска до запуску
int times2 = 500; // час роботи двигуна
int ungle = 90; // кут нахилу
float a = (side1+side2)/2;
#include <Servo.h>   //используем библиотеку для работы с сервоприводом
Servo servo;     //объявляем переменную servo типа Servo
int trigPin = 3;    //Триггер
int echoPin = 2;    //Эхо
float duration, dist, average;   //переменные
long aver[3];   //массив для расчёта среднего арифметического

void setup() {
  Serial.begin(9600);
  servo.attach(5);  //серво на 5 порту
  pinMode(trigPin, OUTPUT);  //пин триггера в режиме выхода
  pinMode(echoPin, INPUT);  //пин эхо в режиме входа
  servo.write(0);         //при подключении питания поставить крышку открытой

}

void measure() {  //блок, измеряющий расстояние
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 275* 100;  //получаем расстояние с датчика
  Serial.println(dist);
}

void loop() {
    for (int i = 0; i <= 2; i++) { //заполняем массив тремя измерениями
      measure();               //измерить расстояние, получаем dist
      aver[i] = dist;          //присваиваем значение dist элементу массива с номером i
      delay(25);              //рекомендуемая задержка между измерениями
    }
    dist = (aver[0] + aver[1] + aver[2]) / 3; //расчёт среднего арифметического с 3-х измерений

  if (dist > base- 10 - side2 && dist < base - a) { //если рука от 10 до 30 см, кнопка не нажата
    servo.write(0);  //открыть крышку
    delay(times1);       //подождать 10  секунд
    servo.write(ungle);    //закрыть крышку
    delay(times2);      //подождать секунду
  }

}
