#ifndef MINAMO_INT_KERNEL_INL
#define MINAMO_INT_KERNEL_INL

#include "int_kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    template <uint16_t D> const std::string IntKernel<D>::kernel_name =typeid(IntKernel<D>).name();
    template <uint16_t D>       index_t     IntKernel<D>::kernel_count=0;



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::IntKernel<D> Structure Template    )//
    template <uint16_t D>
    IntKernel<D>::IntKernel (void) noexcept
        : Kernel              { }
        , count_log           { }
        , enable_send         {false}
        , vertex_option       { }
        , var_name            {this->name_code+"_"+std::string(typeid(IntKernel<D>).name())+"_"+std::to_string(kernel_count++)} 
        , attribute_id        {this->nof_locations++}
        , shared_prog_attribs { }
    {
        this->vertex_shd.in     +="layout(location="+std::to_string(attribute_id)+") in "+glsl_int<D>()+" "+var_name+";";
    
        glGenBuffers(1, &buffer_id);
    }



    //_ Destructor
    template <uint16_t D>
    IntKernel<D>::~IntKernel (void) noexcept
    {
        glDeleteBuffers(1, &buffer_id);
        
        return;
    }



    //_ Destructive Function
    template <uint16_t D>
    void IntKernel<D>::set_vert_option (const VertexOption& vo_) noexcept
    {
        vertex_option=vo_;
        
        return;
    }
 

    template <uint16_t D>
    void IntKernel<D>::attach_cb (GLint* ptr_, size_t sz_) noexcept
    {
        if(enable_send){

            glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
            glBufferData(GL_ARRAY_BUFFER, sz_*sizeof(GLint), ptr_, this->calc_buf_type(count_log));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            enable_send=false;
        }
        
        return;
    }



    //_ Destructive Function
    template <uint16_t D>
    void IntKernel<D>::prefix (UseProgramFlag enable_use_prog_) const noexcept
    {
        if(enable_use_prog_) glUseProgram(this->program_id);

        glEnableVertexAttribArray(attribute_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glVertexAttribIPointer(attribute_id, D, GL_INT, vertex_option.stride, vertex_option.pointer);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        return;
    }


    template <uint16_t D>
    void IntKernel<D>::prefix_shared (index_t id_, UseProgramFlag enable_use_prog_) const noexcept
    {
        const ProgAttribID& paid=shared_prog_attribs[id_];

        if(enable_use_prog_) glUseProgram(paid.program_id);

        glEnableVertexAttribArray(paid.attribute_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glVertexAttribIPointer(paid.attribute_id, D, GL_INT, vertex_option.stride, vertex_option.pointer);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        return;
    }


    template <uint16_t D>
    void IntKernel<D>::suffix (void) const noexcept
    {
        glDisableVertexAttribArray(attribute_id);
        
        return;
    }


    template <uint16_t D>
    void IntKernel<D>::suffix_shared (index_t id_) const noexcept
    {
        const ProgAttribID& paid=shared_prog_attribs[id_];
        glDisableVertexAttribArray(paid.attribute_id);
        
        return;
    }


    template <uint16_t D>
    auto IntKernel<D>::share (Kernel& ker_) const noexcept -> index_t
    {
        shared_prog_attribs.resize(shared_prog_attribs.size()+1);
        
        ProgAttribID& paid=*(shared_prog_attribs.end()-1);
        paid.program_id  =ker_.program_id;
        paid.attribute_id=ker_.nof_locations++;

        ker_.vertex_shd.in +="layout(location="+std::to_string(paid.attribute_id)+") in "+glsl_int<D>()+" "+var_name+";";
        
        return shared_prog_attribs.size()-1;
    }
}
#endif
