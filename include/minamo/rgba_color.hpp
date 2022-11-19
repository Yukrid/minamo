#ifndef MINAMO_RGBA_COLOR_HPP
#define MINAMO_RGBA_COLOR_HPP

#include <glm/glm.hpp>

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::RGBAColor    )//
    struct RGBAColor{
        
        //+    Member Variable     +//
        glm::vec4 base_color;
       
        //+    Member Function    +//
        void colorize (const glm::vec4&) noexcept;
    };
}
#endif
