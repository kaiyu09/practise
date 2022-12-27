
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using namespace std;

int counter = 3;

// 使用锁保护

std::mutex filed_ownload_mutex;
void shared_print(string msg, int id) {
  filed_ownload_mutex.lock();  // 上锁
  // printf(msg);
  cout << msg << id << endl;
  filed_ownload_mutex.unlock();  // 解锁
}

void shared_time_print(std::string inputstr) {
  filed_ownload_mutex.lock();  // 上锁
  time_t t = time(0);
  char ch[30];
  strftime(ch, sizeof(ch), "%Y-%m-%d-%h-%m-%s", localtime(&t));
  std::cout << (std::string)ch << std::endl;
  cout << inputstr << endl;
  filed_ownload_mutex.unlock();  // 解锁
}

void function_1() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  for (int i = 0; i > -1; i--) {
    shared_print(string("From t1: "), i);
    shared_time_print("a");
  }
}

void function_2() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  for (int i = -11; i > -12; i--) {
    shared_print(string("From t2: "), i);
    shared_time_print("b");
  }
}
void function_3() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  for (int i = -11; i > -12; i--) {
    shared_print(string("From t3: "), i);
    shared_time_print("c");
  }
}

int main() {
  // while (true) {
  std::thread t1(function_1);
  // std::thread t2(function_2);
  // std::thread t3(function_3);
  cout << "msgid" << endl;
  cout << t1.joinable() << endl;
  cout << t1.get_id() << endl;
  // cout << t1.native_handle() << endl;
  t1.detach();
  cout << "msgid" << endl;
  cout << t1.joinable() << endl;
  cout << t1.get_id() << endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  // t2.join();
  // t3.join();
  cout << "msgid" << endl;
  cout << t1.joinable() << endl;
  cout << t1.get_id() << endl;
  // cout << t1.get_id() << endl;
  // cout << t1.native_handle() << endl;

  std::this_thread::sleep_for(std::chrono::seconds(5));
  // }
  return 0;
}