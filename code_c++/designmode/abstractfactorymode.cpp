// Copyright (c) 2022, mazu Inc. All rights reserved.
//
// Any use, ReplatformFlashion, distribution, and/or transfer of this file is
// strictly prohibited without the express written permission of the current
// copyright owner.
//
// Any licensed derivative work must retain this notice.
//
// factorymode : [file description]
//

#include <stdio.h>

#include <iostream>
#include <string>

class PlatformFlash {
 public:
  virtual ~PlatformFlash() {}
  virtual std::string flash_isp() const = 0;
  virtual std::string flash_svc() const = 0;
  virtual std::string flash_imu() const = 0;
};

class MazuPlatformFlash : public PlatformFlash {
 public:
  std::string flash_isp() const override { return "mazu_isp_flash"; }
  std::string flash_svc() const override { return "mazu_svc_flash"; }
  std::string flash_imu() const override { return "mazu_imu_flash"; }
};

class CccPlatformFlash : public PlatformFlash {
 public:
  std::string flash_isp() const override { return "ccc_isp_flash"; }
  std::string flash_svc() const override { return "ccc_svc_flash"; }
  std::string flash_imu() const override { return "ccc_imu_flash"; }
};

class Nt3PlatformFlash : public PlatformFlash {
 public:
  std::string flash_isp() const override { return "nt3_isp_flash"; }
  std::string flash_svc() const override { return "nt3_svc_flash"; }
  std::string flash_imu() const override { return "nt3_imu_flash"; }
};

class Flashfactory {
 public:
  virtual ~Flashfactory(){};
  // chun xuhanshu biaodashi
  virtual PlatformFlash* FactoryMethod() const = 0;

  std::string DoFlashIsp() const {
    PlatformFlash* PlatformFlash = this->FactoryMethod();
    std::string result =
        "Flash: we have done, step: " + PlatformFlash->flash_isp();
    delete PlatformFlash;
    return result;
  }

  std::string DoFlashSvc() const {
    PlatformFlash* PlatformFlash = this->FactoryMethod();
    std::string result =
        "Flash: we have done, step: " + PlatformFlash->flash_svc();
    delete PlatformFlash;
    return result;
  }

  std::string DoFlashImu() const {
    PlatformFlash* PlatformFlash = this->FactoryMethod();
    std::string result =
        "Flash: we have done, step: " + PlatformFlash->flash_imu();
    delete PlatformFlash;
    return result;
  }
};
//

class CccFlashfactory : public Flashfactory {
 public:
  PlatformFlash* FactoryMethod() const override {
    return new CccPlatformFlash();
  }
};

class Nt3Flashfactory : public Flashfactory {
 public:
  PlatformFlash* FactoryMethod() const override {
    return new Nt3PlatformFlash();
  }
};

class MazuFlashfactory : public Flashfactory {
 public:
  PlatformFlash* FactoryMethod() const override {
    return new MazuPlatformFlash();
  }
};

//
//
//
//
// 用户接口
void AdcFlash(const Flashfactory& Flashfactory) {
  std::cout << "do flash, res:" << Flashfactory.DoFlashSvc() << std::endl;
  ;
  std::cout << "do flash, res:" << Flashfactory.DoFlashIsp() << std::endl;
  std::cout << "do flash, res:" << Flashfactory.DoFlashImu() << std::endl;
}
// 用户2接口
void AdcFlash2(const Flashfactory& Flashfactory) {
  std::cout << "do flash, res:" << Flashfactory.DoFlashSvc() << std::endl;
  std::cout << "do flash, res:" << Flashfactory.DoFlashIsp() << std::endl;
}

int main() {
  // 客户1
  std::cout << "this is custom Ccc::" << std::endl;
  Flashfactory* Flashfactory1 = new CccFlashfactory();
  AdcFlash(*Flashfactory1);
  std::cout << std::endl;

  // 客户2
  std::cout << "this is custom Nt3::" << std::endl;
  Flashfactory* Flashfactory2 = new Nt3Flashfactory();
  AdcFlash2(*Flashfactory2);
  std::cout << std::endl;
  // 客户3
  std::cout << "this is custom Mazu::" << std::endl;
  Flashfactory* Flashfactory3 = new MazuFlashfactory();
  AdcFlash2(*Flashfactory3);
  std::cout << std::endl;

  delete Flashfactory1;
  delete Flashfactory2;
  delete Flashfactory3;
  return 0;
}
