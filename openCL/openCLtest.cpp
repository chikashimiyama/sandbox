#include "cl.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace cl;
using namespace std;

float randomNums[10000];
std::string srcString;

void printArray(int *array){
    for(int i = 0; i < 16; i++){
    	cout << "index" << i  << ": "  << array[i] << endl; 
    }
}

void openFile(){
    std::ifstream srcFile("average.cl");
   // load entire file onto a string
    if (srcFile.is_open())
    {
        while ( srcFile.good() )
        {
            std::string str;
            getline(srcFile,str);
            srcString.append(str);
        }
        srcFile.close();
    }
}

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
	pl.getDevices(CL_DEVICE_TYPE_GPU, &devs);
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
		cout << "global mem size:" << dv.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()/1024/1024 << "mb"<<endl;

		it++;
		devId++;
	}

	openFile();

	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(plats[0])(), 0};
    Context context(CL_DEVICE_TYPE_GPU, properties); 
    std::vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

    Program::Sources source(1, std::make_pair(srcString.c_str(), srcString.size()));
    Program program = Program(context, source);
    program.build(devices);
    if(program.build(devices) != CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0])<< endl;
        exit(1);
    }

    Kernel kernelD1(program, "d1Count", &err);
    Kernel kernelD2(program, "d2Count", &err);
    Kernel kernelD3(program, "d3Count", &err);
    Kernel kernelSum(program, "sum", &err);
    Kernel kernelLocal(program, "locTest", &err);
    Event event;
    int array [16] = {1 ,3, 5, 2, 4, 9, 14, 33, 22, 1, 5, 23, 42, 33, 22, 11};
    int result[16];

	Buffer inputBufferCL(context,CL_MEM_READ_WRITE,sizeof(int)*16);
	Buffer outputBufferCL(context, CL_MEM_READ_WRITE, sizeof(int) * 16);
    CommandQueue queue(context, devices[0], 0, &err);

	queue.enqueueWriteBuffer(inputBufferCL, CL_TRUE, 0, sizeof(int) * 16, array, NULL, &event);

    kernelD1.setArg(0, inputBufferCL);
    kernelD1.setArg(1, outputBufferCL); 
    kernelD2.setArg(0, inputBufferCL);
    kernelD2.setArg(1, outputBufferCL); 
    kernelD3.setArg(0, inputBufferCL);
    kernelD3.setArg(1, outputBufferCL); 
    kernelSum.setArg(0, inputBufferCL);
    kernelSum.setArg(1, outputBufferCL); 
    kernelLocal.setArg(0, inputBufferCL);
    kernelLocal.setArg(1, outputBufferCL); 

    queue.enqueueNDRangeKernel(kernelD1, NullRange, NDRange(16),NullRange,NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result);

    queue.enqueueNDRangeKernel(kernelD2, NullRange, NDRange(4,4),NullRange,NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result);

    queue.enqueueNDRangeKernel(kernelD3, NullRange, NDRange(2,2,4),NullRange,NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result);

    queue.enqueueNDRangeKernel(kernelLocal, NullRange, NDRange(16),NDRange(4),NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result); 

    cl_int x = 0;
    queue.enqueueWriteBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int), &x, NULL, &event);
    queue.enqueueNDRangeKernel(kernelSum, NullRange, NDRange(16), NullRange, NULL, &event);
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int), result, NULL, &event);  
    event.wait();
    cout << "sum:" << result[0] << endl;

	return 0;
}