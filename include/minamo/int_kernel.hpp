#ifndef MINAMO_INT_KERNEL_HPP
#define MINAMO_INT_KERNEL_HPP

#include <vector>

#include "forward.hpp"
#include "inheritance.hpp"
#include "kernel.hpp"
#include "derived_kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::IntKernel<D> Structure Template    )//
    template <uint16_t D>
    struct IntKernel : public virtual Kernel{

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
        IntKernel (void)             noexcept;
        IntKernel (const IntKernel&) noexcept =delete;
        IntKernel (IntKernel&&)      noexcept =delete;
        
        //_ Destructor
        virtual ~IntKernel (void) noexcept override;
    
        //_ Destructive Function
        void set_vert_option (const VertexOption&) noexcept;
        void attach_cb       (GLint*, size_t)      noexcept;
    
        //_ Constant Function
        void prefix        (UseProgramFlag)          const noexcept;
        void prefix_shared (index_t, UseProgramFlag) const noexcept;
        void suffix        (void)                    const noexcept;
        void suffix_shared (index_t)                 const noexcept;
        auto share         (Kernel&)                 const noexcept -> index_t;

        //_ Constant Binary Operator
        auto operator= (const IntKernel&) noexcept -> IntKernel& =delete;
        auto operator= (IntKernel&&)      noexcept -> IntKernel& =delete;
    };

    

    //-------------//
    //    Alias    //
    //-------------//
    template <uint16_t D, size_t N> using IntKernels =InheritanceArray<IntKernel<D>, N>;
}

#include "int_kernel.inl"

#endif
