#ifndef MINAMO_RECT_REGION_HPP
#define MINAMO_RECT_REGION_HPP

#include <initializer_list>

#include <glm/glm.hpp>

#include "../forward.hpp"

//===============================//
//    Namespace: minamo::rect    //
//===============================//
namespace minamo::rect{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::rect::Region    )//
    struct Region{
        
        //+    Type Declaration    +//
        //(    minamo::rect::Region::Anchor    )//
        enum Anchor : uint32_t{
            DEFAULT, CENTER, LEFT_TOP, LEFT_CENTER, LEFT_BOTTOM, CENTER_BOTTOM, RIGHT_BOTTOM,
            RIGHT_CENTER, RIGHT_TOP, CENTER_TOP
        };
        

        //+    Member Variable     +//
        glm::vec3 base_coord;
        Anchor    anchor;
        GLfloat   scale[2];
    
    
        //+    Member Function    +//
        //_ Constructor
             Region    (void)                                                     noexcept;
             Region    (const glm::vec3&, Anchor, std::initializer_list<GLfloat>) noexcept;
        auto construct (const glm::vec3&, Anchor, std::initializer_list<GLfloat>) noexcept -> Region&;

        //_ Destuctor
        auto destruct (void) noexcept -> Region&;
    };
}
#endif
