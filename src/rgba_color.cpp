#include "minamo/rgba_color.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::RGBAColor    )//
    //+    Member Function    +//
    void RGBAColor::colorize (const glm::vec4& v4_) noexcept
    {
        base_color=v4_;
    
        return;
    }
}
