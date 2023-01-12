#ifndef MINAMO_VARIABLE_HPP
#define MINAMO_VARIABLE_HPP

#include "forward.hpp"

#include <string>
#include <iostream>

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::Variable    )//
    struct Variable{
    
        //+    Member Variable    +//
        std::string name;
        BufferID    buffer_id;


        //+    Member Function     +//
        Variable (const std::string& str_) noexcept
            : name {str_}
        {
            glGenBuffers(1, &buffer_id);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Variable::Variable]  glGenBuffers : "<<buffer_id<<std::endl;
#endif
            return;
        }


        ~Variable (void) noexcept
        {
            glDeleteBuffers(1, &buffer_id);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Variable::~Variable]  glDeleteBuffers : "<<buffer_id<<std::endl;
#endif
            return;
        }

    };
}
#endif
