
#include "cl.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdio>

using namespace std;
using namespace cl;
float randomNums[10000];

int main(void){

	std::vector<Platform> plats; 
	Platform::get(&plats);

    cl_int err = CL_SUCCESS;

	cout << "number of platforms found " << plats.size() << endl;
	if(plats.size() == 0){
		cout << "no platform found... aborting" << endl;
		exit(1);
	}
	std::string srcString;
    ifstream srcFile("average.cl");
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

	for(int i = 0; i < 10000; i++){
		randomNums[i] = static_cast<float>(rand() /1000000.0);
	}
    float result = 0.0;



	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(plats[0])(), 0};
    Context context(CL_DEVICE_TYPE_GPU, properties); 
    std::vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    Device default_device = devices[0];
	Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(float)*10000);
    Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(float));


    Program::Sources source(1, std::make_pair(srcString.c_str(),srcString.size()));
    Program program = Program(context, source);
    if(program.build(devices) != CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }

    //opencl
    std::clock_t start;
    double duration;
    start = std::clock();

    CommandQueue queue(context,default_device);
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(float)*10000,randomNums);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(float),&result);

    Kernel kn = Kernel(program, "average");
    KernelFunctor average(kn , queue, NullRange, NDRange(10), NullRange);
    average(buffer_A, buffer_B);
    queue.enqueueReadBuffer(buffer_B,CL_TRUE,0,sizeof(float), &result);
    
    cout << "OpenCL average:" << result << endl;
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "elapsed time: " << duration << "secs." << endl;
    
    //cpu
    start = std::clock();
    float sum = 0.0;
    for (int i = 0; i < 10000; ++i)
    {
    	sum += randomNums[i];
    }
   	result = sum / 10000;
    cout << "CPU average:" << result << endl;
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "elapsed time: " << duration << "secs." << endl;
    return 0;
}