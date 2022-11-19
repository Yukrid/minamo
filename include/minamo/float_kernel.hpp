#ifndef MINAMO_FLOAT_KERNEL_HPP
#define MINAMO_FLOAT_KERNEL_HPP

#include <vector>

#include "forward.hpp"
#include "kernel.hpp"
#include "inheritance.hpp"
#include "derived_kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::FloatKernel<D> Structure Template    )//
    template <uint16_t D>
    struct FloatKernel : public virtual Kernel{

        //+    Member Variable     +//
                CountLog                  count_log;
                GLuint                    enable_send;
                VertexOption              vertex_option;
                std::string               var_name;
                GLuint                    attribute_id;
        mutable std::vector<ProgAttribID> shared_prog_attribs;
                GLuint                    buffer_id;


        //+    Static Member Variable    +//
        static const std::string kernel_name;
        static       index_t     kernel_count;


        //+    Member Function    +//
        //_ Constructor
        FloatKernel (void)               noexcept;
        FloatKernel (const FloatKernel&) noexcept =delete;
        FloatKernel (FloatKernel&&)      noexcept =delete;
        
        //_ Destructor
        virtual ~FloatKernel (void) noexcept override;
    
        //_ Destructive Function
        void set_vert_option (const VertexOption&) noexcept;
        void attach_cb       (GLfloat*, size_t)    noexcept;

        //_ Constant Function
        void prefix        (UseProgramFlag)          const noexcept;
        void prefix_shared (index_t, UseProgramFlag) const noexcept;
        void suffix        (void)                    const noexcept;
        void suffix_shared (index_t)                 const noexcept;
        auto share         (Kernel&)                 const noexcept -> index_t;

        //_ Constant Binary Operator
        auto operator= (const FloatKernel&) noexcept -> FloatKernel& =delete;
        auto operator= (FloatKernel&&)      noexcept -> FloatKernel& =delete;
    };

    

    //-------------//
    //    Alias    //
    //-------------//
    template <uint16_t D, size_t N> using FloatKernels =InheritanceArray<FloatKernel<D>, N>;
}

#include "float_kernel.inl"

#endif
