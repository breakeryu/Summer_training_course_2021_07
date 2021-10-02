#include <Arduino.h>

/*
Author: magix
Version1 BeginDate:   2021/8/16
Base Board: Arduino Uno
*/

//!实际上，并没有使用定时器，而是采用了软件模拟任务触发。换句话说，单片机不断的在判断软件定时间隔是否达到，达到了就进行任务。
#include <arduino-timer.h>

auto timer = timer_create_default(); // create a timer with default settings
Timer<> default_timer; // save as above

// create a timer that can hold 1 concurrent task, with microsecond resolution
// and a custom handler type of 'const char *
Timer<1, micros, const char *> u_timer;


// create a timer that holds 16 tasks, with millisecond resolution,
// and a custom handler type of 'const char *
Timer<16, millis, const char *> t_timer;

bool toggle_led(void *) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // repeat? true
}

bool toggle_led1(const char *m) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // repeat? true
}

bool print_message(const char *m) {
  Serial.print("print_message: ");
  Serial.println(m);
  return true; // repeat? true
}

size_t repeat_count = 1;
bool repeat_x_times(void *opaque) {
  size_t limit = (size_t)opaque;

  Serial.print("repeat_x_times: ");
  Serial.print(repeat_count);
  Serial.print("/");
  Serial.println(limit);

  return ++repeat_count <= limit; // remove this task after limit reached
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // set LED pin to OUTPUT

  // call the toggle_led function every 500 millis (half second)
  //timer.every(500, toggle_led);
  t_timer.every(500, toggle_led1);//?调用该函数进行取消
  // call the repeat_x_times function every 1000 millis (1 second)
  timer.every(1000, repeat_x_times, (void *)10);//!只执行10次

  // call the print_message function every 1000 millis (1 second),
  // passing it an argument string
  t_timer.every(1000, print_message, "called every second");

  // call the print_message function in five seconds
  t_timer.in(5000, print_message, "delayed five seconds");//执行一次，从计时开始计算，5S之后执行该动作

  // call the print_message function at time + 10 seconds
  t_timer.at(millis() + 10000, print_message, "call at millis() + 10 seconds");

  auto task1 = t_timer.every(500, toggle_led1);
  Serial.println(task1);
  // call the toggle_led function every 500 millis (half second)
  //auto task = t_timer.every(500, toggle_led1);;
  t_timer.cancel(task1); // this task is now cancelled, and will not run //!检验错误，取消该定时器后，闪烁灯任务仍存在，环境为UNO。
                                                                        //!检验错误，使用其他定时器句柄取消该定时器后，闪烁灯任务仍存在。
  // call print_message in 2 seconds, but with microsecond resolution
  u_timer.in(2000000, print_message, "delayed two seconds using microseconds");

  if (!u_timer.in(5000, print_message, "never printed")) {
  /* this fails because we created u_timer with only 1 concurrent task slot */
    Serial.println("Failed to add microsecond event - timer full");
  }
}

void loop() {
  timer.tick(); // tick the timer
  t_timer.tick();
  u_timer.tick();
}
