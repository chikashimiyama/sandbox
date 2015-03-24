#include <iostream>
#include <vector>

class MyClass{
    
public:
    MyClass(size_t size):resource(new double[size]){
    
        for(int i = 0; i < size; i++){
            resource.get()[i] = i;
        }
    };
    MyClass& operator=(const MyClass &other){
        this->resource.release();
        std::copy this->resource
        return *this;
    }
    

private:
    std::unique_ptr<double> resource;
    
    
};


int main(){
    
    MyClass mc(200), mc1(300), mc2(100);
    mc = mc1;
    
    
    std::vector<std::string> dv = {"chikashi", "rie", "setsuko"};
    auto dv2 = std::move(dv);
    for(auto i: dv){
        std::cout << "moved" <<  i << std::endl;
    }
    for(auto i: dv2){
        std::cout << "moved" << i << std::endl;
    }
}