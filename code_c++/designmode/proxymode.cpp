// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// proxymode.cpp : [file description]
//

#include <iostream>

class Subject {
 public:
  virtual void Request() const = 0;
};

// 核心的功能
class RealSubject : public Subject {
 public:
  void Request() const override {
    std::cout << "RealSubject: Handling request.\n";
  }
};

// 代理
class Proxy : public Subject {
 private:
  RealSubject *real_subject_;

  bool CheckAccess() const {
    std::cout << "Proxy: Checking access first.\n";
    return true;
  }
  void LogAccess() const { std::cout << "Proxy: Logging request time.\n"; }

 public:
  Proxy(): real_subject_(new RealSubject()) {}
  ~Proxy() { delete real_subject_; }

  void Request() const override {
    if (this->CheckAccess()) {
      this->real_subject_->Request();
      this->LogAccess();
    }
  }
};

//
void ClientCode(const Subject &subject) { subject.Request(); }

int main() {
  std::cout << "Client: Executing the client code with a real subject:\n";
  RealSubject *real_subject = new RealSubject;
  ClientCode(*real_subject);
  std::cout << "\n";

  std::cout << "Client: Executing the same client code with a proxy:\n";
  Proxy *proxy = new Proxy();
  ClientCode(*proxy);

  delete real_subject;
  delete proxy;
  return 0;
}