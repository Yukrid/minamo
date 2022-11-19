#ifndef MINAMO_SIMPLE_COLOR_METHOD_HPP
#define MINAMO_SIMPLE_COLOR_METHOD_HPP

#include "forward.hpp"
#include "glm_type.hpp"
#include "float_kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //(    minamo::SimpleColorMethod<N> Structure Template    )//
    template <size_t N>
    struct SimpleColorMethod : public FloatKernel<N>{

        //+    Alias    +//
        using vec = vecn<N>;
 
        //+    Static Member Variable    +//
        inline static const std::string kernel_name  =typeid(SimpleColorMethod<N>).name();
        inline static       index_t     kernel_count =0;
        
        //+    Member Variable     +//
        std::vector<vec> colors;

        //+    Member Function    +//
        //_ Constructor
        SimpleColorMethod (void)                     noexcept;
        SimpleColorMethod (const SimpleColorMethod&) noexcept =delete;
        SimpleColorMethod (SimpleColorMethod&&)      noexcept =delete;

        //_ Destructor
        virtual ~SimpleColorMethod (void) noexcept override =default;

        //_ Destructive Function
        void attach_cb (void) noexcept;

        //_ Constant Function
        void prefix (UseProgramFlag) const noexcept;
        void suffix (void)           const noexcept;

        //_ Constant Binary Operator
        auto operator= (const SimpleColorMethod&) noexcept -> SimpleColorMethod& =delete;
        auto operator= (SimpleColorMethod&&)      noexcept -> SimpleColorMethod& =delete;
    };
}

#include "simple_color_method.inl"

#endif
