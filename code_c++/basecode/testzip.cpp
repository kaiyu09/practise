// #include <Poco/DeflatingStream.h>


#include <iostream>
#include <sstream>

#include "Poco/DeflatingStream.h"
#include "Poco/InflatingStream.h"
#include "Poco/StreamCopier.h"

int main() {
  std::ostringstream stream1;

  Poco::DeflatingOutputStream gzipper(stream1,
                                      Poco::DeflatingStreamBuf::STREAM_GZIP);
  gzipper << "Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!";

  gzipper.close();
  std::string zipped_string = stream1.str();
  std::cout << "zipped_string: [" << zipped_string << "]\n";
  std::cout << "zipped_string size: [" << zipped_string.size() << "]\n";

  //
  std::ostringstream stream2;
  Poco::InflatingOutputStream gunzipper(stream2,
                                        Poco::InflatingStreamBuf::STREAM_GZIP);
  gunzipper << zipped_string;
  gunzipper.close();
  std::string unzipped_string = stream2.str();
  std::cout << "unzipped_string back: [" << unzipped_string << "]\n";
  std::cout << "unzipped_string back size: [" << unzipped_string.size() << "]\n";

  return 0;
}