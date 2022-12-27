// Copyright (c) 2022, mazu Inc. All rights reserved.
//
// Any use, ReflashIspion, distribution, and/or transfer of this file is
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

// class FlashIsp {
//  public:
//   virtual ~FlashIsp() {}
//   virtual std::string deploy_bundle() const { return "mazu_isp_deploy"; }
//   virtual std::string trigger_flash() const { return "mazu_isp_flash"; }
//   virtual std::string check_result() const { return "mazu_isp_check"; }
// };

class FlashIsp {
 public:
  virtual ~FlashIsp() {}
  virtual std::string deploy_bundle() const = 0;
  virtual std::string trigger_flash() const = 0;
  virtual std::string check_result() const = 0;
};

class FlashIspMazu : public FlashIsp {
 public:
  std::string deploy_bundle() const override { return "mazu_isp_deploy"; }
  std::string trigger_flash() const override { return "mazu_isp_flash"; }
  std::string check_result() const override { return "mazu_isp_check"; }
};

class FlashIspCcc : public FlashIsp {
 public:
  std::string deploy_bundle() const override { return "ccc_isp_deploy"; }
  std::string trigger_flash() const override { return "ccc_isp_flash"; }
  std::string check_result() const override { return "ccc_isp_check"; }
};

class FlashIspNt3 : public FlashIsp {
 public:
  std::string deploy_bundle() const override { return "nt3_isp_deploy"; }
  std::string trigger_flash() const override { return "nt3_isp_flash"; }
  std::string check_result() const override { return "nt3_isp_check"; }
};

// class FlashSvc {
//  public:
//   virtual ~FlashSvc() {}
//   virtual std::string deploy_bundle() const { return "mazu_svc_deploy"; }
//   virtual std::string trigger_flash() const { return "mazu_svc_flash"; }
//   virtual std::string check_result() const { return "mazu_svc_check"; }
// };

// class FlashSvcBosch : public FlashSvc {
//  public:
//   std::string deploy_bundle() const override { return "bosch_svc_deploy"; }
//   std::string trigger_flash() const override { return "bosch_svc_flash"; }
//   std::string check_result() const override { return "bosch_svc_check"; }
// };

// class FlashSvcUaes : public FlashSvc {
//  public:
//   std::string deploy_bundle() const override { return "uaes_svc_deploy"; }
//   std::string trigger_flash() const override { return "uaes_svc_flash"; }
//   std::string check_result() const override { return "uaes_svc_check"; }
// };

class Flash {
 public:
  virtual ~Flash(){};
  // chun xuhanshu biaodashi
  virtual FlashIsp* FactoryMethod() const = 0;

  std::string Somedoflash() const {
    // 业务逻辑实现
    FlashIsp* FlashIsp = this->FactoryMethod();
    std::string result =
        "Flash: we have done, step1: " + FlashIsp->deploy_bundle() +
        " => step2: " + FlashIsp->trigger_flash() +
        " => step3: " + FlashIsp->check_result();
    delete FlashIsp;
    return result;
  }
};
//
//
//
//
//

class CccFlash : public Flash {
 public:
  FlashIsp* FactoryMethod() const override { return new FlashIspCcc(); }
};

class Nt3Flash : public Flash {
 public:
  FlashIsp* FactoryMethod() const override { return new FlashIspNt3(); }
};

class MazuFlash : public Flash {
 public:
  FlashIsp* FactoryMethod() const override { return new FlashIspMazu(); }
};

void AdcFlash(const Flash& Flash) {
  std::cout << "do flash, res:" << Flash.Somedoflash() << std::endl;
}

int main() {
  Flash* Flash1 = new CccFlash();
  // duotai
  AdcFlash(*Flash1);
  std::cout << std::endl;

  Flash* Flash2 = new Nt3Flash();
  AdcFlash(*Flash2);
  std::cout << std::endl;

  Flash* Flash3 = new MazuFlash();
  AdcFlash(*Flash3);
  std::cout << std::endl;

  delete Flash1;
  delete Flash2;
  delete Flash3;
  return 0;
}
