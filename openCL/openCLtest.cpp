#include "cl.hpp"
#include <iostream>

using namespace cl;
using namespace std;

float randomNums[10000];

const char * helloStr  = "__kernel void "
                            "hello(void) "
                           "{ "
                           "  "
                           "} ";
  

int main(void){
    cl_int err = CL_SUCCESS;

	std::vector<Platform> plats; 
	Platform::get(&plats);
	

	cout << "number of platforms found " << plats.size() << endl;
	if(plats.size() == 0){
		cout << "no platform found... aborting" << endl;
		exit(1);
	}

	Platform pl = plats[0]; // default platform
	cout << "using platform: "<< pl.getInfo<CL_PLATFORM_NAME>() << endl;
	cout << "profile: "<< pl.getInfo<CL_PLATFORM_PROFILE>() << endl;
	cout << "extension: "<< pl.getInfo<CL_PLATFORM_EXTENSIONS>() << endl;
	cout << "version: "<< pl.getInfo<CL_PLATFORM_VERSION>() << endl;
	cout << "vendor: "<< pl.getInfo<CL_PLATFORM_VENDOR>() << endl;

	std::vector<Device> devs;
	pl.getDevices(CL_DEVICE_TYPE_ALL, &devs);
	if(devs.size() == 0){
		cout << "no devices found... aborting" << endl;
		exit(1);
	}

	for(int i = 0; i < 10000; i++){
		randomNums[i] = static_cast<float>(rand());
	}

	std::vector<Device>::iterator it = devs.begin();
	int devId = 0;
	while(it != devs.end()){
		Device dv = *it;
		cout << "------- device " << devId << "------" << endl;
		cout << "device name:" << dv.getInfo<CL_DEVICE_NAME>() << endl;
		cout << "device type:" << dv.getInfo<CL_DEVICE_TYPE>() << endl;
		cout << "device vendor:" << dv.getInfo<CL_DEVICE_VENDOR>() << endl;
		cout << "max comp units:" << dv.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << endl;
		cout << "max clock freq.:" << dv.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << endl;
		cout << "max image width:" << dv.getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>() << endl;
		cout << "max image height:" << dv.getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>() << endl;
		cout << "global mem size:" << dv.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << endl;
		cout << "global cashline size:" << dv.getInfo<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>() << endl;

		it++;
		devId++;
	}



	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(plats[0])(), 0};
    Context context(CL_DEVICE_TYPE_GPU, properties); 
    std::vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

    Program::Sources source(1, std::make_pair(helloStr,strlen(helloStr)));
    Program program_ = Program(context, source);
    program_.build(devices);

    Kernel kernel(program_, "hello", &err);

    Event event;
    CommandQueue queue(context, devices[0], 0, &err);
    queue.enqueueNDRangeKernel(
        kernel, 
        NullRange, 
        NDRange(4,4),
        NullRange,
        NULL,
        &event); 
    event.wait();
	return 0;
}