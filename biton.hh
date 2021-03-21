#ifndef __BITON_H__
#define __BITON_H__

/* Standard io libraries */
#include <iostream>
#include <fstream>
/*****************************************/

/* std containers */
#include <string>
#include <vector>
/****************************************/

/* OpenCL library */
#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
/****************************************/

namespace BS
{
// TODO: здесь явно не всё -- разобраться
/**
 * @brief OpenCL driver class
 * 
 */
class BTS final
{
private:
  cl::Device device_{};
  
  std::string src_code{};

public:

  BTS(BTS const &) = delete;
  BTS &operator=(BTS const &) = delete;

  static BTS &driver( void )
  {
    static BTS SingleTone{};

    return SingleTone;
  }

  void sort( const std::vector<int> &vec )
  {
    cl::Context cont{device_};
    cl::CommandQueue{cont, device_};

  }
private:

  BTS(void)
  {
    std::vector<cl::Platform> pls;
    cl::Platform::get(&pls);

    for (auto &&pl_devs : pls)
    {
      std::vector<cl::Device> devs;
      pl_devs.getDevices(CL_DEVICE_TYPE_ALL, &devs);
      for (auto &&dev : devs)
        if (dev.getInfo<CL_DEVICE_COMPILER_AVAILABLE>())
        {
          device_ = dev;
          return;
        }
    }
  }

  bool load_src( const std::string &cl_fname )
  {
    std::ifstream src(cl_fname);

    if (!src.is_open())
      return false;

    src_code = {std::istreambuf_iterator<char>(src), std::istreambuf_iterator<char>()};

    return true;
  }
};
}

#endif // __BITON_H__