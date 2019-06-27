// http://www.cplusplus.com/reference/istream/istream/read/
// read a file into memory
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
// https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
#include <chrono>
using namespace std::chrono;
using namespace std;
int main (int argc, char **argv) {
  //"/global/cscratch1/sd/cjh1/scan_0000000308/stem4d_0000000308_0000000108.dat"
  std::ifstream is (argv[1], std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    // read data as a block:
    is.read (buffer,length);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    if (is)
      std::cout << "all characters read successfully:micro_seconds:"<<duration<<endl;
    else
      std::cout << "error: only " << is.gcount() << " could be read";
    is.close();

    // ...buffer contains the entire file...

    delete[] buffer;
  }
  return 0;
}
