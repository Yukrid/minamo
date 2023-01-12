#include "minamo/draw_count.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::DrawCount    )//
    //+    Member Function    +//
    //_ Constant Function
    void DrawCount::increment (void) noexcept
    {
        ++draw_count;

        return;
    }


    auto DrawCount::calc_buf_type (const CountLog& cl_) noexcept -> GLuint
    {
        if(draw_count  -cl_.count[2]<2 and 
           cl_.count[2]-cl_.count[1]<2 and 
           cl_.count[1]-cl_.count[0]<2 )
        {
            return GL_DYNAMIC_DRAW;
        
        }else if(draw_count  -cl_.count[2]<5 and
                 cl_.count[2]-cl_.count[1]<5 and 
                 cl_.count[1]-cl_.count[0]<5 )
        {
            return GL_STREAM_DRAW;
        
        }else{
            
            return GL_STATIC_DRAW;
        } 
    }
}
