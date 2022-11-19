#ifndef MINAMO_RECT_RECT_HPP
#define MINAMO_RECT_RECT_HPP

#include "../forward.hpp"
#include "../rgba_color.hpp"

#include "region.hpp"

//===============================//
//    Namespace: minamo::rect    //
//===============================//
namespace minamo::rect{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::rect::Rect    )//
    struct Rect{
        
        //+    Member Variable     +//
        Region    region;
        glm::vec4 coords[4];

        
        //+    Member Function    +//
        void calc   (void)                                              noexcept;
        void resize (GLfloat[2])                                        noexcept;
        void move   (const glm::vec3&, Region::Anchor =Region::DEFAULT) noexcept;
        void move   (Region::Anchor)                                    noexcept;
    };


    //(    minamo::rect::ColorRect    )//
    struct ColorRect : Rect, RGBAColor{
        
    };
}
#endif
