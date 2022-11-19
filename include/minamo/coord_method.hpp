#ifndef MINAMO_COORD_METHOD_HPP
#define MINAMO_COORD_METHOD_HPP

#include "forward.hpp"
#include "float_kernel.hpp"
#include "glm_type.hpp"
#include "uniform.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //(    minamo::CoordMethod<N> Structure Template    )//
    template <size_t N>
    struct CoordMethod : public FloatKernel<N>, public Usmat<(N+1>4 ? N : N+1)>{

        //+    Constant Expression Value    +//
        static constexpr uint16_t mat_dim=(N+1>4 ? N : N+1);

        
        //+    Alias    +//
        using vec = vecn<N>;
        using mat = matnxm<mat_dim, mat_dim>;
 
        //+    Static Member Variable    +//
        inline static const std::string kernel_name  =typeid(CoordMethod<N>).name();
        inline static       index_t     kernel_count =0;
        
        //+    Member Variable     +//
        std::vector<vec> coords;

        //+    Member Function    +//
        //_ Constructor
        CoordMethod (void)               noexcept;
        CoordMethod (const CoordMethod&) noexcept =delete;
        CoordMethod (CoordMethod&&)      noexcept =delete;

        //_ Destructor
        virtual ~CoordMethod (void) noexcept override =default;

        //_ Destructive Function
        void locate    (UseProgramFlag) noexcept;            
        void attach_cb (void)           noexcept;

        //_ Constant Function
        void prefix (UseProgramFlag) const noexcept;
        void suffix (void)           const noexcept;

        //_ Constant Binary Operator
        auto operator= (const CoordMethod&) noexcept -> CoordMethod& =delete;
        auto operator= (CoordMethod&&)      noexcept -> CoordMethod& =delete;
    };
}

#include "coord_method.inl"

#endif
