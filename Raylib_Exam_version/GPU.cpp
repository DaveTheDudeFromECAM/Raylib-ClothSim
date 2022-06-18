#include "GPU.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

Buffer::Buffer(GPU &gpu, size_t size) {
    cl_int ret;
    this->gpu = gpu;
    this->size = size;
    buffer = clCreateBuffer(gpu, CL_MEM_READ_ONLY, size, NULL, &ret);
}

Buffer::Buffer(const Buffer &other) {
    buffer = other.buffer;
    size = other.size;
    gpu = other.gpu;
}

void Buffer::destroy() {
    cl_int ret;
    ret = clReleaseMemObject(buffer);
}

Buffer::operator cl_mem() const {
    return buffer;
}

void Buffer::upload(void *data, size_t offset, size_t size) {
    cl_int ret;
    ret = clEnqueueWriteBuffer(gpu, buffer, CL_TRUE, offset, size, data, 0, NULL, NULL);
}

void Buffer::upload(void *data) {
    upload(data, 0, size);
}

void Buffer::download(void *data) {
    cl_int ret;
    ret = clEnqueueReadBuffer(gpu, buffer, CL_TRUE, 0, size, data, 0, NULL, NULL);
}

Program::Program(GPU &gpu, const char* filename) {
    this->gpu = gpu;
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load program.\n");
        exit(1);
    }
    source = new char[MAX_SOURCE_SIZE];
    sourceSize = fread(source, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    cl_int ret;
    program = clCreateProgramWithSource(gpu, 1, (const char **)&source, (const size_t *)&sourceSize, &ret);
    cl_device_id device = gpu;
    ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
}

Program::Program(const Program &other) {
    source = other.source;
    sourceSize = other.sourceSize;
    program = other.program;
    gpu = other.gpu;
}

void Program::destroy() {
    cl_int ret;
    ret = clReleaseProgram(program);
    delete[] source;
}

Program::operator cl_program() const {
    return program;
}

Kernel Program::getKernel(const char* kernelName) {
    return Kernel(gpu, *this, kernelName);
}

Kernel::Kernel(GPU &gpu, Program &program, const char* kernelName) {
    cl_int ret;
    this->gpu = gpu;
    kernel = clCreateKernel(program, kernelName, &ret);
}

Kernel::Kernel(const Kernel &other) {
    kernel = other.kernel;
    gpu = other.gpu;
}

void Kernel::destroy() {
    cl_int ret;
    ret = clReleaseKernel(kernel);
}

Kernel::operator cl_kernel() const {
    return kernel;
}

void Kernel::setArg(cl_uint argIndex, Buffer buffer) {
    cl_int ret;
    cl_mem buf = buffer;
    ret = clSetKernelArg(kernel, argIndex, sizeof(cl_mem), (void *)&buf);
}

void Kernel::execute(size_t globalSize, size_t localSize) {
    cl_int ret;
    ret = clEnqueueNDRangeKernel(gpu, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
}

GPU::GPU() {
    device = NULL;   
    context = NULL;
    queue = NULL;
}

GPU::GPU(const GPU &other) {
    device = other.device;
    context = other.context;
    queue = other.queue;
}

void GPU::init() {
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device, &ret_num_devices);
    char* extensions = new char[MAX_SOURCE_SIZE];
    size_t extensionsSize;
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, MAX_SOURCE_SIZE, extensions, &extensionsSize);
    printf("extensions: %s\n", extensions);
    context = clCreateContext( NULL, 1, &device, NULL, NULL, &ret);
    queue = clCreateCommandQueue(context, device, 0, &ret);
}

void GPU::destroy() {
    cl_int ret;
    ret = clFlush(queue);
    ret = clFinish(queue);
    ret = clReleaseCommandQueue(queue);
    ret = clReleaseContext(context);
}

GPU::operator cl_device_id() const {
    return device;
}

GPU::operator cl_context() const {
    return context;
}

GPU::operator cl_command_queue() const {
    return queue;
}

Buffer GPU::createBuffer(size_t size) {
    return Buffer(*this, size);
}

Program GPU::createProgram(const char* filename) {
    return Program(*this, filename);
}
