
#include "cl.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdio>

#define NUM_ELEMENT 10000
using namespace std;
using namespace cl;
int ascending[NUM_ELEMENT];
int result[NUM_ELEMENT];

int main(void){

	std::vector<Platform> plats; 
	Platform::get(&plats);
   //opencl
    std::clock_t start;
    double duration;

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

	for(int i = 0; i < NUM_ELEMENT; i++){
		ascending[i] = i;
	}

	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(plats[0])(), 0};
    Context context(CL_DEVICE_TYPE_GPU, properties); 
    std::vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    Device default_device = devices[0];
	Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*NUM_ELEMENT);
    Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*NUM_ELEMENT);

    Program::Sources source(1, std::make_pair(srcString.c_str(),srcString.size()));
    Program program = Program(context, source);
    if(program.build(devices) != CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<< endl;
        exit(1);
    }

 

    CommandQueue queue(context,default_device);
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*NUM_ELEMENT,ascending);

    start = std::clock();
    Kernel kn = Kernel(program, "average");
    KernelFunctor average(kn , queue, NullRange, NDRange(NUM_ELEMENT), NullRange);
    average(buffer_A, buffer_B);
    queue.enqueueReadBuffer(buffer_B,CL_TRUE,0,sizeof(int)*NUM_ELEMENT, &result);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "OpenCL result:" << endl;
    for(int i = 0; i < NUM_ELEMENT; i++){
    	cout << "index:" << i << " value:" << result[i] << endl;
    }

    cout << "elapsed time: " << duration << "secs." << endl;
    
   
    return 0;
}