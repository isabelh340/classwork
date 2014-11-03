// Copyright 2014 raodm@miamiOH.edu

#include <stdexcept>
#include <string>
#include "ClCmdQueue.h"
#include "BitmapImage.h"
#define _USE_MATH_DEFINES
#include <math.h>

// A couple of forward declarations to keep compiler happy
int getDevType(const std::string& device) throw(std::runtime_error);
BitmapImage clRotate(ClCmdQueue& queue, cl::KernelFunctor& vflip,
                    BitmapImage& srcImg, float sinTheta, float cosTheta)
    throw(cl::Error);

// A simple tester for testing operation of toggling characters via OpenCL
int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Specify [CPU|GPU|ACC] <InputBMP> <OutputBMP> <Degrees>\n";
        return 1;
    }
    float radians = atof(argv[4]) * M_PI / 180;
    float sinTheta = std::sin(radians);
    float cosTheta = std::cos(radians);
    // Load source image from the given file
    BitmapImage srcImg;
    srcImg.load(argv[2]);
    // Create the OpenCL command queue for a given device
    ClCmdQueue queue(getDevType(argv[1]));
    // Create a kernel and functor using OpenCL kernel code from a file.
    cl::Kernel kernel = queue.loadKernel("haitzza_rotate.cl", "img_rotate");
    cl::NDRange globalRange(srcImg.getWidth(), srcImg.getHeight());
    cl::KernelFunctor rotate(kernel, queue.getQueue(), cl::NullRange,
                            globalRange, cl::NullRange);
    BitmapImage outImg = clRotate(queue, rotate, srcImg, sinTheta, cosTheta);
    outImg.write(argv[3]);
    return 0;
}

BitmapImage
clRotate(ClCmdQueue& queue, cl::KernelFunctor& rotate,
        BitmapImage& srcImg, float sinTheta, float cosTheta) throw (cl::Error) {
    BitmapImage outImg;
    outImg.resize(srcImg.getWidth(), srcImg.getHeight());
    // Create the input, output image, and filter buffers!
    cl::Image2D srcBuf = queue.makeImage(srcImg.getRow(0), srcImg.getWidth(),
                                         srcImg.getHeight(), queue.ROFlags);
    cl::Image2D outBuf = queue.makeImage(outImg.getRow(0), outImg.getWidth(),
                                         outImg.getHeight(), queue.WOFlags);
    // Setup sampler for source image to control sampler
    cl::Sampler sampler(queue.getContext(), CL_FALSE, CL_ADDRESS_CLAMP,
                        CL_FILTER_LINEAR);
    // Now use the OpenCl kernel to perform convolution
    rotate(srcBuf, outBuf, srcImg.getWidth(), srcImg.getHeight(), sampler,
          sinTheta, cosTheta);
    // Copy result image back from the device to host.
    queue.enqueueMapImage(outBuf);
    // Return the resulting image back to the caller.
    return outImg;
}

int getDevType(const std::string& device) throw(std::runtime_error) {
    const std::string DevTypes = "CPUGPUACC";
    switch (DevTypes.find(device)) {
    case 0: return CL_DEVICE_TYPE_CPU;
    case 3: return CL_DEVICE_TYPE_GPU;
    case 6: return CL_DEVICE_TYPE_ACCELERATOR;
    }
    throw std::runtime_error("Invalid device type specified");
}

// End of source code
