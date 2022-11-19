#ifndef MINAMO_SIMPLE_COLOR_METHOD_INL
#define MINAMO_SIMPLE_COLOR_METHOD_INL

#include "simple_color_method.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::SimpleColorMethod<N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <size_t N> SimpleColorMethod<N>::SimpleColorMethod (void) noexcept
        : FloatKernel<N> { }
        , colors         { }
    {
        if(N==4){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
            
        this->vertex_shd.out  +=std::string("out ")+glsl_float<N>()+" "+this->var_name+"_vf;";
        this->vertex_shd.main +=this->var_name+"_vf="+this->var_name+";";

        this->fragment_shd.in  +=std::string("in ")+glsl_float<N>()+" "+this->var_name+"_vf;";
        this->fragment_shd.out +=std::string("out ")+glsl_float<N>()+" "+this->var_name+"_f;";
        this->fragment_shd.main +=this->var_name+"_f="+this->var_name+"_vf;";
    };


    template <size_t N> void SimpleColorMethod<N>::attach_cb (void) noexcept
    {
        FloatKernel<N>::attach_cb(reinterpret_cast<GLfloat*>(colors.data()), colors.size()*N);
        
        return;
    }



    //_ Constant Function
    template <size_t N> void SimpleColorMethod<N>::prefix (UseProgramFlag flag_) const noexcept
    {
 
        if(flag_) glUseProgram(this->program_id);

        FloatKernel<N>::prefix(REMAIN_PROGRAM);
        
        return;
    }


    template <size_t N> void SimpleColorMethod<N>::suffix (void) const noexcept
    {
        FloatKernel<N>::suffix();
        
        return;
    }
}
#endif
