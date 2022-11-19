#include "minamo/drawer.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Drawer<K>    )//
    //+    Member Function    +//
    //_ Constructor
    Drawer::Drawer (void) noexcept
    {
        std::cerr<<this->compile_vertex_shader()<<std::endl;
        std::cerr<<this->compile_fragment_shader()<<std::endl;
        glLinkProgram(this->program_id);

        return;
    }


    Drawer::~Drawer (void) noexcept
    {
        glDetachShader(this->program_id, this->vertex_shd.id);
        glDetachShader(this->program_id, this->fragment_shd.id);
        glDeleteShader(this->vertex_shd.id);
        glDeleteShader(this->fragment_shd.id);

        return;
    }
 

    //_ Destructive Function
    void Drawer::attach (void* ptr_) noexcept
    {
        attach_cb(ptr_);

        return;
    }
   


    //_ Constant Function
    void Drawer::draw (void* ptr_) const noexcept
    {
        glBindVertexArray(this->vertex_array_id);
        draw_cb(ptr_);
        glBindVertexArray(0);
        this->increment();

        return;
    }
}
