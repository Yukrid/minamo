#include <iostream>
#include "vert_buffer_2d_array.hpp"

int main(void){
    
    minamo::extension::VertBuffer2DArray<uint8_t> vb;
    
    std::cout<<vb.width<<" "<<vb.height<<std::endl;
    
    std::cout<<vb.resize(16, 16)<<std::endl;

    for(uint32_t c=0; c<vb.nof_pages; ++c){
        for(uint32_t a=0; a<vb.height; ++a){
            vb.add_lock(c, a);
            std::cout<<+vb.get_lock(c, a)<<": ";
        
            for(uint32_t b=0; b<vb.width; ++b){
                vb(c, a, b)=b%10;
                std::cout<<+vb(c, a, b)<<" ";
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"========================================================"<<std::endl;
    std::cout<<"========================================================"<<std::endl;
    std::cout<<"========================================================"<<std::endl;
    std::cout<<vb.resize(250, 250)<<std::endl;
//    vb.add_page();
    
    for(uint32_t c=0; c<vb.nof_pages; ++c){
        for(uint32_t a=0; a<vb.height; ++a){
            vb.subtract_lock(c, a);
            std::cout<<+vb.get_lock(c, a)<<": ";
            
            for(uint32_t b=0; b<vb.width; ++b){
                if(c==1) vb(c, a, b)=(b+5)%10;
                std::cout<<+vb(c, a, b)<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"-------------"<<std::endl;
    }
    std::cout<<"========================================================"<<std::endl;
    std::cout<<"========================================================"<<std::endl;
    std::cout<<"========================================================"<<std::endl;
    std::cout<<vb.width<<" "<<vb.height<<std::endl;

}
