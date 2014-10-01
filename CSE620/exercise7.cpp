// Compiler command-line:
//     make SRC=exercise7.cpp LIBS=-lOpenCL
//
// Alternative (not preferred):
//     g++ -g -Wall -std=c++11 exercise7.cpp -o execise7 -lOpenCL

// Enable OpenCL C++ exceptions
#define __CL_ENABLE_EXCEPTIONS
#include "CL/cl.hpp"

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>

const std::string kernelSrc =
     "#pragma OPENCL EXTENSION cl_khr_fp64 : enable \n"
      "__kernel void \n"
      "vadd (__global float * a, __global float * b,"
      "__global float * c) { \n"
      "size_t i = get_global_id(0);\n"
      "c[i] = a[i] + b[i];\n}";

cl::Kernel createOpenCL(cl::Context context, cl::Device device) {
    cl::Program::Sources sources(1, std::make_pair(kernelSrc.c_str(), 0));
    cl::Program program(context, sources);
    try {
        program.build({ device });
    } catch (cl::Error error) {
        std::cout << "Build log:" << std::endl
                  << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device)
                  << std::endl;
        throw error;
    }
    return (cl::Kernel(program, "vadd"));
}

// Implement the following add method (add suitable helper methods as
// you see fit) to use an OpenCL kernel to add each entry in the the
// two vectors, that is: result[i] = vec1[i] + vec2[i]
std::vector<double>
add(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    std::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    cl_device_type devType = CL_DEVICE_TYPE_GPU;
    std::vector<cl::Device> deviceList;
    platformList[0].getDevices(devType, &deviceList);
    cl::Context context    = cl::Context(deviceList);
    cl::Device device      = deviceList[0];
    cl::CommandQueue queue = cl::CommandQueue(context, device);
    cl::Kernel kernel = createOpenCL(context, device);
    std::vector<double> result(vec1.size());
    const int byteSize = vec1.size() * sizeof(double);
    cl::Buffer devBuf1 = cl::Buffer(context,
                                   CL_MEM_READ_ONLY |
                                   CL_MEM_USE_HOST_PTR,
                                   byteSize,
                                   const_cast<double*>(&vec1[0]));
    cl::Buffer devBuf2 = cl::Buffer(context,
                                   CL_MEM_READ_ONLY |
                                   CL_MEM_USE_HOST_PTR,
                                   byteSize,
                                   const_cast<double*>(&vec2[0]));
    cl::Buffer devBuf3 = cl::Buffer(context,
                                   CL_MEM_READ_WRITE |
                                   CL_MEM_USE_HOST_PTR,
                                   byteSize,
                                   &result[0]);
    kernel.setArg(0, devBuf1);
    kernel.setArg(1, devBuf2);
    kernel.setArg(2, devBuf3);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange,
                               cl::NDRange(vec1.size()*3), cl::NullRange);
    queue.enqueueMapBuffer(devBuf1, CL_TRUE, CL_MAP_READ, 0, byteSize);
    queue.enqueueMapBuffer(devBuf2, CL_TRUE, CL_MAP_READ, 0, byteSize);
    queue.enqueueMapBuffer(devBuf3, CL_TRUE, CL_MAP_READ, 0, byteSize);
    return result;
}

//-----------------------------------------------------------------------
//           DO  NOT   MODIFY   CODE  BELOW  THIS  LINE
//-----------------------------------------------------------------------

std::vector<double> generate(const int size) {
    int i = 0;
    auto producer = [&i](){ return i++; };
    std::vector<double> list(size);
    std::generate_n(list.begin(), size, producer);
    return list;
}

int
main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage  : " << argv[0] << " <vector_size>\n"
                  << "Example: " << argv[0] << " 20\n";
        return 2;
    }
    // Create the vectors for use.
    const int count = std::stoi(argv[1]);
    const std::vector<double> vec1 = generate(count), vec2 = generate(count);
    // Get the result by doing the addition via OpenCL calls
    const std::vector<double> result = add(vec1, vec2);
    // Print the results
    std::copy(result.begin(), result.end(),
              std::ostream_iterator<double>(std::cout, "\n"));
    // All done.
    return 0;
}

// End of source code
