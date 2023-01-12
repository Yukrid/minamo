#ifndef MINAMO_DRAWER_LINES_INL
#define MINAMO_DRAWER_LINES_INL

#include "even_manifold.hpp"

//=================================//
//    Namespace: minamo::drawer    //
//=================================//
namespace minamo::drawer{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::drawer::EvenManifold<D1, D2>    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D1, dim_t D2> EvenManifold<D1, D2>::EvenManifold (void) noexcept
        : kernel      { }
        , basic_p1    {kernel}
        , fixed_color {kernel}
    {
        std::cerr<<kernel.compile_vertex_shader()<<std::endl;
        std::cerr<<kernel.compile_fragment_shader()<<std::endl;
        glLinkProgram(kernel.program_id);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[EvenManifold::EvenManifold]  glLinkProgram : "<<kernel.program_id<<std::endl;
#endif

        basic_p1.locate();
        fixed_color.locate();

        return;
    }
    

    template <dim_t D1, dim_t D2> EvenManifold<D1, D2>::~EvenManifold (void) noexcept
    {
        glDetachShader(kernel.program_id, kernel.vertex_shd.id);
        glDetachShader(kernel.program_id, kernel.fragment_shd.id);
        glDeleteShader(kernel.vertex_shd.id);
        glDeleteShader(kernel.fragment_shd.id);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[EvenManifold::~EvenManifold]  glDetachShader : "<<kernel.program_id<<' '<<kernel.vertex_shd.id<<std::endl;
        std::cout<<"[EvenManifold::~EvenManifold]  glDetachShader : "<<kernel.program_id<<' '<<kernel.fragment_shd.id<<std::endl;
        std::cout<<"[EvenManifold::~EvenManifold]  glDeleteShader : "<<kernel.vertex_shd.id<<std::endl;
        std::cout<<"[EvenManifold::~EvenManifold]  glDeleteShader : "<<kernel.fragment_shd.id<<std::endl;
#endif

        return;
    }
    

    //_ Destructive Function
    //void Drawer::attach (void* ptr_) noexcept
    //{
    //    attach_cb(ptr_);

    //    return;
    //}
   


    //_ Constant Function
    template <dim_t D1, dim_t D2> void EvenManifold<D1, D2>::draw (GLenum mf_, GLsizei sz_) noexcept
    {
        glBindVertexArray(kernel.vertex_array_id);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[EvenManifold::draw]  glBindVertexArray : "<<kernel.vertex_array_id<<std::endl;
#endif
        basic_p1.coord.prefix();  

        for(GLsizei a=0; a<basic_p1.coord.data.size()/D1; a+=sz_){
            glDrawArrays(mf_, a, sz_);
        }
        //glDrawArrays(GL_LINE_STRIP, 0, 3);
 #ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[EvenManifold::draw]  glDrawArrays"<<std::endl;
#endif
        basic_p1.coord.suffix();
        
        glBindVertexArray(0);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[EvenManifold::draw]  glBindVertexArray : "<<0<<std::endl;
#endif
       
        kernel.draw_count.increment();

        return;
    }
}
#endif
