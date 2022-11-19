#include "minamo/rect/color_drawer.hpp"

#include <GLFW/glfw3.h>

int main(void){
 
    //(GLFW)初期化
    if(!glfwInit()){
        std::cerr<<"Error: Cannot open GLFW"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_SAMPLES,4); //4x アンチエイリアス
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Open a window and create its openGL context
    GLFWwindow* window;
    window=glfwCreateWindow(500,1000,"Tutorial 01",NULL,NULL);
    if(window==NULL){
        std::cerr<<"Error: Cannot open GLFW"<<std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);   //GLFWを初期化
    
    //Initialize GLEW
    glewExperimental=true;
    if(glewInit()!=GLEW_OK){
        std::cerr<<"Error: Cannot initialize GLEW"<<std::endl;
        std::exit(EXIT_FAILURE);
    }

    //キー入力保証
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Dark blue background
    glClearColor(0.0f,0.0f,0.4f,0.0f);


    minamo::rect::ColorDrawer cd;
    cd.print_vertex_shader(std::cout);
    std::cout<<"-------------"<<std::endl;
    cd.print_fragment_shader(std::cout);
    std::cout<<"============="<<std::endl;
    
    minamo::rect::Region reg;
    reg.base_coord =glm::vec3{-0.5, -0.5, 1.};
    reg.anchor     =minamo::rect::Region::CENTER;
    reg.scale[0]   =0.3f;
    reg.scale[1]   =0.1f;
    std::cout<<cd.append(reg, glm::vec4{1, 1, 1, 1})<<std::endl;
    
    reg.base_coord =glm::vec3{+0.5, -0.5, 1.};
    std::cout<<cd.append(reg, glm::vec4{0., 0., 0., 1})<<std::endl;

    reg.base_coord =glm::vec3{-0.5, +0.5, 1.};
    std::cout<<cd.append(reg, glm::vec4{1, 1, 1, 1})<<std::endl;

    reg.base_coord =glm::vec3{+0.5, +0.5, 1.};
    std::cout<<cd.append(reg, glm::vec4{1, 1, 1, 0.5})<<std::endl;

    cd.attach();

    do{
        
        double curr_x, curr_y;
        glfwGetCursorPos(window, &curr_x, &curr_y);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        //Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        cd.draw();

        //スワップ
        glfwSwapBuffers(window);
        glfwPollEvents();

    }while(glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS &&
           glfwWindowShouldClose(window)==0);

    glfwTerminate();
}
