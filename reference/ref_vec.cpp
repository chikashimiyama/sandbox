#include <iostream>
#include <vector>

using namespace std;


void withReference(std::vector<int> &ref){
	ref.clear();
	for(int i = 0; i < 10000000; i++){
		ref.push_back(i);
	}
}

std::vector<int> directReturn(void){
	std::vector<int> vec;
	for(int i = 0; i < 10000000; i++){
		vec.push_back(i);
	}
	return vec;
}


int main(void){

	clock_t start = clock();
    std::vector<int> ref;
    withReference(ref);
    clock_t end = clock();
    std::cout << "with reference" << endl;
    std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

	start = clock();
    std::vector<int> normal = directReturn();
    end = clock();
    std::cout << "direct return" << endl;
    std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

    return 0;
}

// clang++ -03 
// with reference
// duration = 0.066131sec.
// direct return
// duration = 0.043405sec.
