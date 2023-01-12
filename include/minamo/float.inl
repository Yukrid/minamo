#ifndef MINAMO_FLOAT_INL
#define MINAMO_FLOAT_INL

#include <iostream>//

#include "float.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::FloatData<D> Structure Template    )//
    template <dim_t D> const std::string FloatData<D>::data_name =typeid(FloatData<D>).name();
    template <dim_t D>       index_t     FloatData<D>::data_count=0;



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::FloatAttrib<D> Structure Template    )//
    //_ Constructor
    template <dim_t D>
    FloatAttrib<D>::FloatAttrib (Kernel& ker_, const Variable& var_) noexcept
        : kernel        {ker_}
        , variable      {var_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_float<D>()+" "+variable.name+";";
    
        return;
    }


    template <dim_t D>
    FloatAttrib<D>::FloatAttrib (Kernel& ker_, const std::string& name_) noexcept
        : kernel        {ker_}
        , variable      {name_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_float<D>()+" "+variable.name+";";
    
        return;
    }



    //_ Destructive Function
    template <dim_t D>
    void FloatAttrib<D>::set_vert_option (const VertexOption& vo_) noexcept
    {
        vertex_option=vo_;
        
        return;
    }



    //_ Constant Function
    template <dim_t D>
    void FloatAttrib<D>::prefix (void) const noexcept
    {
        glUseProgram(kernel.program_id);
        glEnableVertexAttribArray(location_id);
        glBindBuffer(GL_ARRAY_BUFFER, variable.buffer_id);
        glVertexAttribPointer(location_id, D, GL_FLOAT, vertex_option.normalized, vertex_option.stride, vertex_option.pointer);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[FloatAttrib::prefix]  glUseProgram : "<<kernel.program_id<<std::endl;
        std::cout<<"[FloatAttrib::prefix]  glEnableVertexAttribArray : "<<location_id<<std::endl;
        std::cout<<"[FloatAttrib::prefix]  glBindBuffer : "<<variable.buffer_id<<std::endl;
        std::cout<<"[FloatAttrib::prefix]  glVertexAttribPointer : "<<location_id<<std::endl;
#endif    
        return;
    }
    

    template <dim_t D>
    void FloatAttrib<D>::suffix (void) const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(location_id);
        
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[FloatAttrib::suffix]  glBindBuffer : "<<0<<std::endl;
        std::cout<<"[FloatAttrib::suffix]  glDisableVertexAttribArray : "<<location_id<<std::endl;
#endif

        return;
    }
    



    //(    minamo::FloatData<D> Structure Template    )//
    template <dim_t D>
    FloatData<D>::FloatData (Kernel& ker_) noexcept
        : FloatAttrib<D> {ker_, data_name+"_"+std::to_string(data_count++)}
        , count_log      { }
        , enable_send    {false}
        , data           { }
    {
        return;
    }

     

    //_ Destructive Function
    template <dim_t D>
    void FloatData<D>::attach (void) noexcept
    {
        if(enable_send){
            glBindBuffer(GL_ARRAY_BUFFER, FloatAttrib<D>::variable.buffer_id);
            glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLfloat), data.data(), FloatAttrib<D>::kernel.draw_count.calc_buf_type(count_log));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            enable_send=false;

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[FloatAttrib::attach]  glBindBuffer : "<<FloatAttrib<D>::variable.buffer_id<<std::endl;
            std::cout<<"[FloatAttrib::attach]  glBufferData : "<<data.size()*sizeof(GLfloat)<<std::endl;
            std::cout<<"[FloatAttrib::attach]  glBindBuffer : "<<0<<std::endl;
#endif
        }

        return;
    }

}
#endif
