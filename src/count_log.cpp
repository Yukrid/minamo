#include "minamo/count_log.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::CountLog    )//
    //+    Member Function    +//
    void CountLog::push_back (uint64_t cnt_) noexcept
    {
        count[0]=count[1];
        count[1]=count[2];
        count[2]=cnt_;

        return;
    }
}
