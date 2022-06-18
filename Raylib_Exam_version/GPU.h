
#pragma once

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

class Buffer;
class Program;

class GPU {
	private:
		cl_device_id device;
		cl_context context;
		cl_command_queue queue;

	public:
		GPU();
		GPU(const GPU &other);
		void init();
		void destroy();
		operator cl_device_id() const;
		operator cl_context() const;
		operator cl_command_queue() const;
		Buffer createBuffer(size_t size);
		Program createProgram(const char* filename);
};

class Buffer {
	private:
		cl_mem buffer;
		size_t size;
		GPU gpu;

	public:
		Buffer(GPU &gpu, size_t size);
		Buffer(const Buffer &other);
		void destroy();
		operator cl_mem() const;
		void upload(void* data, size_t offset, size_t size);
		void upload(void* data);
		void download(void* data);
};

class Kernel;

class Program {
	private:
		char* source;
		size_t sourceSize;
		cl_program program;
		GPU gpu;

	public:
		Program(GPU &gpu, const char* filename);
		Program(const Program &other);
		void destroy();
		operator cl_program() const;
		Kernel getKernel(const char* kernelName);
};

class Kernel {
	private:
		cl_kernel kernel;
		GPU gpu;

	public:
		Kernel(GPU &gpu, Program &program, const char* kernelName);
		Kernel(const Kernel &other);
		void destroy();
		operator cl_kernel() const;
		void setArg(cl_uint argIndex, Buffer buffer);
		void execute(size_t globalSize, size_t localSize);
};


