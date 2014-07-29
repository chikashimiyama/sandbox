#include "cl.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable

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
        cout << "address bits:" << static_cast<int>(dv.getInfo<CL_DEVICE_ADDRESS_BITS>()) << endl;
		cout << "device name:" << dv.getInfo<CL_DEVICE_NAME>() << endl;
		cout << "device type:" << dv.getInfo<CL_DEVICE_TYPE>() << endl;
		cout << "device vendor:" << dv.getInfo<CL_DEVICE_VENDOR>() << endl;
		cout << "max comp units:" << dv.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << endl;
		cout << "max clock freq.:" << dv.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << endl;
		cout << "max image width:" << dv.getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>() << endl;
		cout << "max image height:" << dv.getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>() << endl;
		cout << "global mem size:" << dv.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()/1024/1024 << "mb"<<endl;
        cout << "local mem size:" << dv.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>()/1024 << "kb"<<endl;
        cout << "max memory object size:" << dv.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>()/1024/1024 << "mb"<<endl;
        cout << "max work group size:" << dv.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()<< endl;
        int dimen = dv.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>();
        cout << "max work item dim:" << dimen << endl;
        std::vector<std::size_t> witems = dv.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
        for (int i = 0; i < dimen; ++i){
            std::cout << "max work item size dim:" << i << " " <<  witems[i] << endl;
        }
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
    Kernel kernelSize(program, "size", &err);
    Kernel kernelAtomic(program, "atomic", &err);
    Kernel kernelSFU(program, "sfu", &err);

    Event event;
    int array [16] = {0 ,3, 5, 2, 4, 9, 14, 33, 22, 1, 5, 23, 42, 33, 22, 11};
    int result[16];
    float sinResult[100000];

	Buffer inputBufferCL(context,CL_MEM_READ_WRITE,sizeof(int)*16);
	Buffer outputBufferCL(context, CL_MEM_READ_WRITE, sizeof(int) * 16);
    Buffer outputSinCL(context, CL_MEM_READ_WRITE, sizeof(float) * 100000);
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
    kernelSize.setArg(0, inputBufferCL);
    kernelSize.setArg(1, outputBufferCL);
    kernelLocal.setArg(0, inputBufferCL);
    kernelLocal.setArg(1, outputBufferCL);
    kernelAtomic.setArg(0, inputBufferCL);
    kernelAtomic.setArg(1, outputBufferCL);
    kernelSFU.setArg(0, outputSinCL);

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

    cout << "size" << endl;
    queue.enqueueNDRangeKernel(kernelSize, NullRange, NDRange(16), NullRange,NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result); 

    cout << "atomic" << endl;
    queue.enqueueNDRangeKernel(kernelAtomic, NullRange, NDRange(16), NullRange,NULL,&event); 
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int) * 16, result, NULL, &event);  
    event.wait();
    printArray(result); 

    clock_t t;
    cout << "sfu" << endl;
    t = clock();
    queue.enqueueNDRangeKernel(kernelSFU, NullRange, NDRange(100000), NullRange,NULL,&event); 
    event.wait();
    t = clock() - t;
    cout <<  "GPU:" << (float)t/(CLOCKS_PER_SEC) * 1000.0 << endl;;
    queue.enqueueReadBuffer(outputSinCL, CL_TRUE, 0, sizeof(int) * 100000, sinResult, NULL, &event);  
    event.wait();

    for(int i = 0; i < 100000; i++){
        cout << sinResult[i] << endl;
    }

    cl_int x = 0;
    queue.enqueueNDRangeKernel(kernelSum, NullRange, NDRange(16), NullRange, NULL, &event);
    queue.enqueueReadBuffer(outputBufferCL, CL_TRUE, 0, sizeof(int), result, NULL, &event);  
    event.wait();
    cout << "sum:" << result[0] << endl;

	return 0;
}