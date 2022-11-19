#ifndef MINAMO_COUNT_LOG_HPP
#define MINAMO_COUNT_LOG_HPP

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::CountLog    )//
    struct CountLog{
        
        //+    Member Variable    +//
        uint64_t count[3] ={0, 0, 0};
        

        //+    Member Function    +//
        //_ Destructive Function
        void push_back (uint64_t) noexcept;
    };
}
#endif
