
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
    download_semaphore_.Clear();
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

tsp_proto::State::ReturnCode TspServiceFile::DbStateToProto(
    const TaskState &state) {
  tsp_proto::State::ReturnCode rc = tsp_proto::State::DATABASE_ERROR;

  switch (state) {
    case TaskState::kDone:
      rc = tsp_proto::State::SUCCESS;
      break;
    case TaskState::kPending:
      rc = tsp_proto::State::PENDING;
      break;
    case TaskState::kRuning:
      rc = tsp_proto::State::RUNNING;
      break;
    case TaskState::kFailed:
      rc = tsp_proto::State::PENDING;
      break;
    case TaskState::kAbort:
      rc = tsp_proto::State::DATABASE_ERROR;
      break;
    case TaskState::kFileNotExist:
      rc = tsp_proto::State::FILE_NOT_EXIST;
      break;
    case TaskState::kRetryOverLimit:
      rc = tsp_proto::State::RETRY_OVER_LIMIT;
      break;
  }
  return rc;
}
}  // namespace tsp_client
