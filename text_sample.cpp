#include "include/minamo/preset/text_store.hpp"

#include <iostream>
#include <iomanip>
#include <random>
#include <GLFW/glfw3.h>

int main(void){
 
    // GLFW Initialization
    if(!glfwInit()){
        std::cerr<<"Error: Cannot open GLFW"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW Create Window
    GLFWwindow* window;
    window=glfwCreateWindow(600, 600,"Tutorial 01",NULL,NULL);
    if(window==NULL){
        std::cerr<<"Error: Cannot open GLFW"<<std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  
    // GLEW Initialization
    glewExperimental=true;
    if(glewInit()!=GLEW_OK){
        std::cerr<<"Error: Cannot initialize GLEW"<<std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Set BackGround Color
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    
    // TextStore Initialization (4 means color dimension.)
    minamo::preset::TextStore<4> ts;

    // Load Font File "../font/migmix-2m-regular.ttf" (48pt) and Append Text
    minamo::index_t fi1=ts.add_font("../font/migmix-2m-regular.ttf", 48);
    minamo::index_t tx1=ts.append("AbΓβあ亜", glm::vec3(0.f, 0.f, 0.f), minamo::extension::CENTER, glm::vec4(1.f, 0.f, 0.f, 1.f));
    minamo::index_t tx2=ts.append("CdΔγい伊", glm::vec3(-300.f, -300.f, 0.f), minamo::extension::LEFT_BOTTOM, glm::vec4(0.f, 1.f, 0.f, 1.f));
   
    // Load Font File "../font/migmix-2m-regular.ttf" (32pt) and Append Text
    minamo::index_t fi2=ts.add_font("../font/migmix-2m-regular.ttf", 32);
    minamo::index_t tx3=ts.append("E\nf\nΛ\nδ\nう\n宇", glm::vec3(-300.f, 300.f, 0.f), minamo::extension::LEFT_TOP, glm::vec4(0.f, 0.f, 1.f, 1.f)); 
    
    // Duplicate TX1
    minamo::index_t tx4=ts.duplicate(tx1, glm::vec3(300.f, 300.f, 0.f), minamo::extension::RIGHT_TOP, glm::vec4(0.f, 0.f, 0.f, 1.f));

    // Modify Text Aspect for 600 x 600 Window Size and Use Texture Unit 0
    ts.set_window_size(600, 600);
    ts.set_texture_unit(0);
    
    const uint32_t period=150;
    uint32_t count=0;
    do{
        if(count==period){
            
            // Replace String of TX1
            ts.bind_font(fi2);        
            tx1=ts.replace(tx1, "GhΞεえ江");
            std::cout<<"tx1  : string replaced"<<std::endl;

        }else if(count==period*2){
            
            // Move Position of TX1
            tx1=ts.move(tx1, glm::vec3(300.f, -300.f, 0.f), minamo::extension::RIGHT_BOTTOM);
            std::cout<<"tx1  : moved"<<std::endl;

        }else if(count==period*3){
            
            // Change Color of TX1
            tx1=ts.recolorize(tx1, glm::vec4(0.5f, 0.5f, 0.f, 0.75f));
            std::cout<<"tx1  : color changed"<<std::endl;

        }else if(count==period*4){
  
            // Set 4x4 Tranform Matrix for All Text Coordinates (Scale Transformation)
            glm::mat4 mat{1.f};
            
            mat[0][0]*=0.75/300.;  // 1./(window_width*0.5) is suitable scale
            mat[1][1]*=0.75/300.;  // 1./(window_height*0.5) is suitable scale

            ts.set_coord_matrix(mat);
            
            std::cout<<"whole: coordinate scale changed by matrix"<<std::endl;
              
        }else if(period*5<=count and count<period*6){

            // Set 4x4 Tranform Matrix for All Text Coordinates (Affine Transformation)
            glm::mat4 mat{1.f};

            float val=0.25*(count-period*5)/(float)period;

            mat[0][0]*=(0.75-val)/300.;
            mat[1][1]*=(0.75-val)/300.;

            mat[3][0]=-val;
            
            ts.set_coord_matrix(mat);
            
            std::cout<<"whole: coordinate transformed by matrix"<<std::endl;
        
        }else if(count==period*6){

            // Erase TX1
            ts.erase(tx1);
            
            std::cout<<"tx1  : erased"<<std::endl;
        
        }else if(count==period*7){
 
            // Reset
            ts.set_window_size(600, 600);
                   
            ts.bind_font(fi1);
            tx1=ts.append("AbΓβあ亜", glm::vec3(0.f, 0.f, 0.f), minamo::extension::CENTER, glm::vec4(1.f, 0.f, 0.f, 1.f));
            
            std::cout<<"whole: reseted"<<std::endl;
            
            count=0;
        }
        count++;

        glClear(GL_COLOR_BUFFER_BIT);    
        
        // Draw Call of TextStore
        ts.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }while(glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS &&
           glfwWindowShouldClose(window)==0);

    // Appendix: You can see buffer of text texture.
    std::cout<<"(final texture buffer)"<<std::endl;
    for(uint32_t a=0; a<ts.buffer_objs.nof_pages; ++a){
        for(uint32_t b=0; b<ts.buffer_objs.height; ++b){
            std::cout<<std::setw(4)<<b<<"-"<<ts.buffer_objs.get_lock(a, b)<<": ";
            uint8_t* head=ts.buffer_objs(a, b);
            for(uint32_t c=0; c<ts.buffer_objs.width; ++c){
                std::cout<<(head[c] ? 1 : 0)<<" ";
            }
            std::cout<<std::endl;
        }
    }
}
