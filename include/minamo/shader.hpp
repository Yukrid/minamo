#ifndef MINAMO_SHADER_HPP
#define MINAMO_SHADER_HPP

#include <string>

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::Shader    )//
    struct Shader{
        
        //+    Member Variable     +//
                      GLuint      id;
                      std::string version;
                      std::string in;
                      std::string out;
                      std::string uniform;
                      std::string main_head;
                      std::string main;
                      std::string main_foot;
        mutable       std::string whole;
        mutable const char*       head;


        //+    Member Function    +//
        //_ Constant Function
        auto get_head_ptr (void) const noexcept -> const char**;
    };
}
#endif
