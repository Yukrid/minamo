#include "minamo/shader.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Shader    )//
    //+    Member Function    +//
    //_ Destructive Function
    auto Shader::get_head_ptr (void) const noexcept -> const char**
    {
        whole.resize(0);

        whole+=version;
        whole+=in;
        whole+=out;
        whole+=uniform;
        whole+=func_dif;
        whole+=main_head;
        whole+=main;
        whole+=main_foot;
     
        head=whole.data();

        return &head;
    }
}
