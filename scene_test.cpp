#include <minamo/system/scene.hpp>
#include <iostream>
#include <thread>

using namespace minamo;
using namespace std::chrono_literals;

int main(void){
    
    system::Scenes scenes;
    minamo::index_t head = scenes.append(3); 
    uint32_t count = 0;

    scenes.reset(head+0, system::Scenes::DRAW, [&](system::Scenes& sc_){
        
        std::cout<<"First Draw"<<std::endl;
        
        ++count;

        if(count==5){
            
            count=0;
            
            uint32_t val;
            std::cin>>val;
            
            if     (val==1){ sc_.jump(head+1); }
            else if(val==2){ sc_.jump(head+2); }
        }
        
        return 0;
    });

    
    scenes.reset(head+1, system::Scenes::DRAW, [&](system::Scenes& sc_){
        
        std::cout<<"Second Draw"<<std::endl;
        
        ++count;

        if(count==5){
            
            count=0;
            
            uint32_t val;
            std::cin>>val;
            
            if     (val==0){ sc_.jump(head+0); }
            else if(val==2){ sc_.jump(head+2); }
        }
        
        return 0;
    });


    scenes.reset(head+2, system::Scenes::DRAW, [&](system::Scenes& sc_){
        
        std::cout<<"Third Draw"<<std::endl;
        
        ++count;

        if(count==5){
            
            count=0;
            
            uint32_t val;
            std::cin>>val;
            
            if     (val==0){ sc_.jump(head+0); }
            else if(val==1){ sc_.jump(head+1); }
        }
        
        return 0;
    });



    scenes.reset(head+2, system::Scenes::JUMP, [&](system::Scenes& sc_){
        
        std::cout<<"Third Jump"<<std::endl;
        
        return 0;
    });


    scenes.reset(head+2, system::Scenes::INITIALIZE, [&](system::Scenes& sc_){
        
        std::cout<<"Third Initialize"<<std::endl;
        
        return 0;
    });
    

    scenes.jump(head);

    while(true){
        scenes.draw();
        std::this_thread::sleep_for(500ms);
    }

}
