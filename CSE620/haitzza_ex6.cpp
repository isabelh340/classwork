#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include <vector>
#include <iostream>

int main() {
    const std::vector<std::string> platHeaders =
        {"Vendor", "Name", "Version", "Devices"};
    std::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    std::string a;
    for (uint i = 0; i < platformList.size(); i++) {
        std::cout << platHeaders[0] << "\t:"
                  << platformList[i].getInfo<CL_PLATFORM_VENDOR>()
                  << std::endl;
        std::cout << platHeaders[1] << "\t:"
                  << platformList[i].getInfo<CL_PLATFORM_NAME>()
                  << std::endl;
        std::cout << platHeaders[2] << "\t:"
                  << platformList[i].getInfo<CL_PLATFORM_VERSION>()
                  << std::endl;

        std::vector<cl::Device> deviceList;
        platformList[i].getDevices(CL_DEVICE_TYPE_ALL, &deviceList);
        std::cout << platHeaders[3] << "\t:" << deviceList.size() << std::endl;
    }
    
    return 0;
}
