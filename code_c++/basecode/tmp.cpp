// Copyright (c) 2021, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// tsp_service_file.cpp :
//
#include <chrono>
#include <mutex>
#include <string>
#include <thread>

#include "nio_traffic_mgr.h"
#include "nlog.h"
#include "syslog.h"
#include "tsp_database_common.h"
#include "tsp_database_file.h"
#include "tsp_file_topic.h"
#include "tsp_proto_common.h"
#include "tsp_service_file.h"

namespace tsp_client {

using namespace std::chrono_literals;
using std::this_thread::sleep_for;

static constexpr const char *kTspServiceFileNodeName =
    "tsp_client_service_file";
// Should be smaller than 10MB (we have extra headers)
static constexpr int kTspServiceFileResumeSizeByte = 9 * 1024 * 1024;
static constexpr int kTspServiceFileMaxTimeout = 50;
static constexpr int kMaxFiledownloadThreadNum = 3;
static constexpr int kRetryTimesMax = 10;
static constexpr int kRetryDelayMax = 3600;
static constexpr int kRetryDelayMin = 10;
static constexpr int kNetRetryDelay = 5;

TspServiceFile::TspServiceFile()
    : node_{nio::ad::Node::CreateNode(kTspServiceFileNodeName)},
      running_{false} {}

void TspServiceFile::DownloadFileTask() {
  std::string last_file_key = "";
  auto db = TspFileDatabase::Instance();

  auto requests = db->GetDownloadRequest(1);

  if (last_file_key != requests[0].file_key) {
    last_file_key = requests[0].file_key;
    retry_delay = kRetryDelayMin;
  }
  rc = downloader_->Download(requests[0].dest_path, requests[0].file_key,
                             requests[0].type, kTspServiceFileMaxTimeout);
  switch (rc) {
    case tsp_proto::State::ReturnCode::State_ReturnCode_SUCCESS: {
      if (db->UpdateDownloadRequest(requests[0].file_key, TaskState::kDone,
                                    "DONE") != 0) {
        syslog(LOG_WARNING, "Update download state failed!");
      }
      break;
    }
    case tsp_proto::State::ReturnCode::State_ReturnCode_FILE_KEY_INVALID: {
      if (db->UpdateDownloadRequest(requests[0].file_key, TaskState::kAbort,
                                    "ABORT") != 0) {
        syslog(LOG_WARNING, "Update download state failed!");
      }
      break;
    }
    case tsp_proto::State::ReturnCode::
        State_ReturnCode_INTERNAL_CERTS_INVALID: {
      syslog(LOG_WARNING, "NOT existed valid certs, sleep for %d s",
             kRetryDelayMax);
      sleep(kRetryDelayMax);
      break;
    }
    case tsp_proto::State::ReturnCode::State_ReturnCode_FILE_COMPRESS_FAILED:
    case tsp_proto::State::ReturnCode::State_ReturnCode_FILE_DOWNLOAD_FAILURE: {
      DownloadRequest request;
      auto rc_get = db->GetDownloadRequest(requests[0].file_key, request);
      if (rc_get == 0) {
        if (request.retry_times < kRetryTimesMax) {
          syslog(LOG_WARNING, "Download retry_times %d", request.retry_times);
        } else {
          db->UpdateDownloadRequest(request.file_key,
                                    TaskState::kRetryOverLimit,
                                    "Too much retry times");
        }
        db->UpdateDownloadRequestRetryTimes(request.file_key,
                                            request.retry_times + 1);
      }
      syslog(LOG_WARNING, "downloader_->Download failed:rc = %d", rc);
      syslog(LOG_INFO, "sleep %d seconds for file download retry", retry_delay);
      sleep(retry_delay);
      retry_delay = retry_delay * 2;
      if (retry_delay > kRetryDelayMax) {
        retry_delay = kRetryDelayMax;
      }
      break;
    }
    default:
      syslog(LOG_INFO, "downloader_->Download :rc = %d", rc);
      break;
  }
}

void TspServiceFile::DownloadThreadFunc() {
  syslog(LOG_INFO, "Download thread start");
  auto db = TspFileDatabase::Instance();
  SaNetState sa_net_state;
  tsp_proto::State::ReturnCode rc =
      tsp_proto::State::ReturnCode::State_ReturnCode_SUCCESS;
  download_semaphore_.Signal();
  int thread_count = kMaxFiledownloadThreadNum;

  // TODO: support multi thread download
  while (true) {
    download_semaphore_.Wait();
    // download_semaphore_.Clear();
    std::thread download_thread1(DownloadFileTask);
    std::thread download_thread2(DownloadFileTask);
    std::thread download_thread3(DownloadFileTask);

    download_thread1.join();
    download_thread2.join();
    download_thread3.join();
  }
  syslog(LOG_INFO, "Download thread stop");
}

}  // namespace tsp_client

int retry_delay = kRetryDelayMin;

static constexpr int kMaxFiledownloadThreadNum = 3;

void TspServiceFile::DownloadThreadFunc() {
  syslog(LOG_INFO, "Download thread start");
  auto db = TspFileDatabase::Instance();
  SaNetState sa_net_state;
  tsp_proto::State::ReturnCode rc =
      tsp_proto::State::ReturnCode::State_ReturnCode_SUCCESS;
  download_semaphore_.Signal();
  // TODO: support multi thread download
  while (true) {
    download_semaphore_.Wait();
    pthread_t tids[NUM_THREADS];
    for (int i = 0; i < kMaxFiledownloadThreadNum; ++i) {
      int ret = pthread_create(&tids[i], NULL, DownloadFileTask, NULL);
      if (ret != 0) {
        cout << "pthread_create error: error_code=" << ret << endl;
      }
    }
    pthread_exit(NULL);

    std::string last_file_key = "";
    int retry_delay = kRetryDelayMin;
    while (true) {
      auto requests = db->GetDownloadRequest(1);
      if (requests.empty()) {
        syslog(LOG_DEBUG, "Empty download requests!\n");
        break;
      }
      while (!sa_net_state.IsNetAccessible()) {
        std::this_thread::sleep_for(std::chrono::seconds(kNetRetryDelay));
      }
      if (last_file_key != requests[0].file_key) {
        last_file_key = requests[0].file_key;
        retry_delay = kRetryDelayMin;
      }
      rc = downloader_->Download(requests[0].dest_path, requests[0].file_key,
                                 requests[0].type, kTspServiceFileMaxTimeout);
      switch (rc) {
        case tsp_proto::State::ReturnCode::State_ReturnCode_SUCCESS: {
          if (db->UpdateDownloadRequest(requests[0].file_key, TaskState::kDone,
                                        "DONE") != 0) {
            syslog(LOG_WARNING, "Update download state failed!");
          }
          break;
        }
        case tsp_proto::State::ReturnCode::State_ReturnCode_FILE_KEY_INVALID: {
          if (db->UpdateDownloadRequest(requests[0].file_key, TaskState::kAbort,
                                        "ABORT") != 0) {
            syslog(LOG_WARNING, "Update download state failed!");
          }
          break;
        }
        case tsp_proto::State::ReturnCode::
            State_ReturnCode_INTERNAL_CERTS_INVALID: {
          syslog(LOG_WARNING, "NOT existed valid certs, sleep for %d s",
                 kRetryDelayMax);
          sleep(kRetryDelayMax);
          break;
        }
        case tsp_proto::State::ReturnCode::
            State_ReturnCode_FILE_COMPRESS_FAILED:
        case tsp_proto::State::ReturnCode::
            State_ReturnCode_FILE_DOWNLOAD_FAILURE: {
          DownloadRequest request;
          auto rc_get = db->GetDownloadRequest(requests[0].file_key, request);
          if (rc_get == 0) {
            if (request.retry_times < kRetryTimesMax) {
              syslog(LOG_WARNING, "Download retry_times %d",
                     request.retry_times);
            } else {
              db->UpdateDownloadRequest(request.file_key,
                                        TaskState::kRetryOverLimit,
                                        "Too much retry times");
            }
            db->UpdateDownloadRequestRetryTimes(request.file_key,
                                                request.retry_times + 1);
          }
          syslog(LOG_INFO, "downloader_->Download failed:rc = %d", rc);
          syslog(LOG_WARNING, "sleep %d seconds for file download retry",
                 retry_delay);
          sleep(retry_delay);
          retry_delay = retry_delay * 2;
          if (retry_delay > kRetryDelayMax) {
            retry_delay = kRetryDelayMax;
          }
          break;
        }
        default:
          syslog(LOG_INFO, "downloader_->Download :rc = %d", rc);
          break;
      }
    }
  }
  syslog(LOG_INFO, "Download thread stop");
}
