#ifndef MINAMO_COORD_METHOD_INL
#define MINAMO_COORD_METHOD_INL

#include "coord_method.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::CoordMethod<N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <size_t N> CoordMethod<N>::CoordMethod (void) noexcept
        : FloatKernel<N> { }
        , Usmat<mat_dim> {kernel_name+"_"+std::to_string(kernel_count), 1}
        , coords         { }
    {
                 this->vertex_shd.uniform +=this->get_code();
        if(N!=4) this->vertex_shd.main    +="gl_Position="+this->get_name()+"*"+glsl_float<N+1>()+"("+this->var_name+", 1.f);";
        else     this->vertex_shd.main    +="gl_Position="+this->get_name()+"*"+this->var_name+";";
    };



    //_ Destructive Function
    template <size_t N> void CoordMethod<N>::locate (UseProgramFlag flag_) noexcept
    {
        mat m{1.f};

        if(flag_) glUseProgram(this->program_id);
        Usmat<mat_dim>::locate(this->program_id);
        Usmat<mat_dim>::set(1, GL_FALSE, &m[0][0]);

        return;
    }


    template <size_t N> void CoordMethod<N>::attach_cb (void) noexcept
    {
        FloatKernel<N>::attach_cb(reinterpret_cast<GLfloat*>(coords.data()), coords.size()*N);
        
        return;
    }



    //_ Constant Function
    template <size_t N> void CoordMethod<N>::prefix (UseProgramFlag flag_) const noexcept
    {
        
        if(flag_) glUseProgram(this->program_id);

        FloatKernel<N>::prefix(REMAIN_PROGRAM);
        
        return;
    }


    template <size_t N> void CoordMethod<N>::suffix (void) const noexcept
    {
        FloatKernel<N>::suffix();
        
        return;
    }
}
#endif
