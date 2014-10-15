#define __CL_ENABLE_EXCEPTIONS
#include "CL/cl.hpp"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <functional>
#include <string>
#include <iostream>

const std::string kernelStr =
    "__kernel void \n"
    "toggle(__global char* currChar) { \n"
    "    currChar = 'a'; \n"
    "}";

cl::Kernel
getKernel(std::vector<cl::Device>& deviceList, cl::Context& context,
          const std::string& sourceCode, const std::string& entryFunc) {
    // Create the program from source for given device
    cl::Program::Sources sources(1, std::make_pair(sourceCode.c_str(), 0));
    cl::Program program(context, sources);
    // Build Open CL program for a given device
    try {
        program.build(deviceList);
    } catch (cl::Error error) {
        std::cout << "Build log:" << std::endl
                  << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(deviceList[0])
                  << std::endl;
        throw error;
    }
    // Create and return a kernel
    cl::Kernel kernel(program, entryFunc.c_str());
    return kernel;
}

std::string
toggleViaOpenCL(cl::Context& context, cl::CommandQueue& queue,
                cl::Kernel& kernel,
                cl::KernelFunctor& toggle, const std::string& str) {
    const int ROFlags  = CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR;
    const int RWFlags  = CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR;
    const int byteSize = str.size() * sizeof(char);
    // Create buffer for vec1 and vec2 and copy host contents
    cl::Buffer strBuffer = cl::Buffer(context, ROFlags, byteSize,
                                       const_cast<char*>(&str[0]));
    // Create buffer for result vector
    std::string result(str);
    cl::Buffer resBuffer = cl::Buffer(context, RWFlags, byteSize, &result[0]);
    // Run the OpenCL kernel via the functor
    toggle(strBuffer);
    // Sync the OpenCL buffer with the host buffers
    queue.enqueueMapBuffer(strBuffer, CL_TRUE, CL_MAP_READ, 0, byteSize);
    return str;
}

std::string
toggleCL(std::string& str, char goal) {
    // Discover OpenCl platforms available on host
    std::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    // Pick the first platform and query its GPU devices
    std::vector<cl::Device> deviceList;
    platformList[0].getDevices(CL_DEVICE_TYPE_GPU, &deviceList);
    
    // Create a context for the devices and use the first device to create
    // a command-queue.
    cl::Context context       = cl::Context(deviceList);
    cl::CommandQueue queue    = cl::CommandQueue(context, deviceList[0]);
    // Build and get kernel for the devices
    cl::Kernel kernel = getKernel(deviceList, context,
                                  kernelStr, "toggle");
    // Build a kernel functor
    cl::KernelFunctor toggle(kernel, queue, cl::NullRange,
                             cl::NDRange(str.size()), cl::NullRange);
    //kernel.setArg(0, 1, &goal);
    // Run the kernel and obtain results
    return toggleViaOpenCL(context, queue, kernel, toggle, str);
}

int main(int argc, char* argv[]) {
    std::string str = "asdfasdasdfasdfaf";
    str = toggleCL(str, 'a');
    std::cout << str << std::endl;
    return 0;
}
