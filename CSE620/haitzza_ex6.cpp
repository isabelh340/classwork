// copyright Zach Haitz 2014
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

void printDeviceInfo(cl::Device device) {
    const std::vector<std::string> deviceHeaders =
        {"\tDevice name\t: ", "\tFrequency\t: ", "\tCompute Units\t: ",
         "\tGlobal memory\t: ", "\tLocal memory\t: "};
    std::cout << deviceHeaders[0] << device.getInfo<CL_DEVICE_NAME>()
              << std::endl
              << deviceHeaders[1]
              << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>()
              << std::endl
              << deviceHeaders[2]
              << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
              << std::endl
              << deviceHeaders[3] << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()
              << std::endl
              << deviceHeaders[4] << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>()
              << std::endl;
}

void printPlatformInfo(cl::Platform plat) {
    const std::vector<std::string> platHeaders =
        {"Vendor\t: ", "Name\t: ", "Version\t: ", "Devices\t: "};
    std::cout << platHeaders[0]
              << plat.getInfo<CL_PLATFORM_VENDOR>()
              << std::endl;
    std::cout << platHeaders[1]
              << plat.getInfo<CL_PLATFORM_NAME>()
              << std::endl;
    std::cout << platHeaders[2]
              << plat.getInfo<CL_PLATFORM_VERSION>()
              << std::endl;
    std::vector<cl::Device> devices;
    plat.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    std::cout << platHeaders[3]
              << devices.size() << std::endl;
    std::for_each(devices.begin(), devices.end(), printDeviceInfo);
}

int main() {
    std::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    std::for_each(platformList.begin(), platformList.end(), printPlatformInfo);
    return 0;
}
