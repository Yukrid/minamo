#ifndef MINAMO_DRAW_COUNT_HPP
#define MINAMO_DRAW_COUNT_HPP

#include "forward.hpp"
#include "count_log.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //(    minamo::DrawCount    )//
    struct DrawCount{
        
        //+    Member Variable     +//
        uint64_t draw_count =0;    
        

        //+    Member Function    +//
        //_ Destructive Function
        void increment (void) noexcept;
        
        //_ Counstant Function
        auto calc_buf_type (const CountLog&) noexcept -> GLuint;
    };
}
#endif
