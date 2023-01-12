#ifndef MINAMO_METHOD_UNIFORM_MOLD_C0U1_INL
#define MINAMO_METHOD_UNIFORM_MOLD_C0U1_INL

#include "uniform_mold_c0u1.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::method::UniformMoldC0U1<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D1, dim_t D2, TexEnum T> UniformMoldC0U1<D1, D2, T>::UniformMoldC0U1 (Kernel& ker_) noexcept
        : kernel {ker_}
        , uv     {ker_}
        , usmat  {1}
        , ucolor {1}
        , utex   {1}
    {

        kernel.vertex_shd.out +=std::string("out ")+glsl_float<D2>()+" "+uv.variable.name+"_vf;";
        
        kernel.vertex_shd.uniform +=usmat.get_code();
        
        switch(D2){
            case 1: kernel.vertex_shd.main +=uv.variable.name+"_vf=("+usmat.get_name()+"*"+glsl_float<D2+1>()+"("+uv.variable.name+", 1.f)).x;"; break;
            case 2: kernel.vertex_shd.main +=uv.variable.name+"_vf=("+usmat.get_name()+"*"+glsl_float<D2+1>()+"("+uv.variable.name+", 1.f)).xy;"; break;
            case 3: kernel.vertex_shd.main +=uv.variable.name+"_vf=("+usmat.get_name()+"*"+glsl_float<D2+1>()+"("+uv.variable.name+", 1.f)).xyz;"; break;
            case 4: kernel.vertex_shd.main +=uv.variable.name+"_vf="+usmat.get_name()+"*"+uv.variable.name+";"; break;
        }

        if(D1==4 or D1==2){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[BasicC1::BasicC1]  glEnable : "<<GL_BLEND<<"(GL_BLEND)"<<std::endl;
            std::cout<<"[BasicC1::BasicC1]  glBlendFunc : "<<GL_SRC_ALPHA<<"(GL_SRC_ALPHA)"<<" "<<GL_ONE_MINUS_SRC_ALPHA<<"(GL_ONE_MINUS_SRC_ALPHA)"<<std::endl;
#endif    
        }
        
        kernel.fragment_shd.in +=std::string("in ")+glsl_float<D2>()+" "+uv.variable.name+"_vf;";
        
        kernel.fragment_shd.uniform +=ucolor.get_code();
        kernel.fragment_shd.uniform +=utex.get_code();

        kernel.fragment_shd.main +=std::string("float uniform_mold_c0u1_1=texture(")+utex.get_name()+", "+uv.variable.name+"_vf).x;";

        kernel.assign_color<D1>(std::string("uniform_mold_c0u1_1*")+ucolor.get_name());

        return;
    }



    //_ Destructive Function
    template <dim_t D1, dim_t D2, TexEnum T> void UniformMoldC0U1<D1, D2, T>::locate (void) noexcept
    {
        mat m{1.f};

        usmat.locate(kernel.program_id);
        usmat.set(1, GL_FALSE, &m[0][0]);
        
        ucolor.locate(kernel.program_id);
        ucolor.set({1.f, 1.f, 1.f, 1.f});

        utex.locate(kernel.program_id);
        utex.set(GL_TEXTURE0);
        
        return;
    }


    template <dim_t D1, dim_t D2, TexEnum T> void UniformMoldC0U1<D1, D2, T>::prefix (void) noexcept
    {
        uv.prefix();

        return;
    }


    template <dim_t D1, dim_t D2, TexEnum T> void UniformMoldC0U1<D1, D2, T>::suffix (void) noexcept
    {
        uv.suffix();

        return;
    }
}
#endif
