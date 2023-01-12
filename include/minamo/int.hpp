#ifndef MINAMO_INT_HPP
#define MINAMO_INT_HPP

#include <vector>

#include "forward.hpp"
#include "kernel.hpp"
#include "attribute.hpp"
#include "variable.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::IntAttrib<D> Structure Template    )//
    template <dim_t D>
    struct IntAttrib{
        
        //+    Member Variable     +//
        Kernel&        kernel;
        Variable       variable;
        LocationID     location_id;
        VertexOption   vertex_option;
    

        //+    Member Function    +//
        //_ Constructor
        IntAttrib (Kernel&, const Variable&) noexcept;
        IntAttrib (Kernel&, const std::string&) noexcept;
        
        //_ Destructor
        virtual ~IntAttrib (void) noexcept =default;
    
        //_ Destructive Function
        void set_vert_option (const VertexOption&) noexcept;
   
        //_ Constant Function
        void prefix (void) const noexcept;
        void suffix (void) const noexcept;
    };



    //(    minamo::IntData<D> Structure Template    )//
    template <dim_t D>
    struct IntData : public IntAttrib<D>{

        //+    Member Variable     +//
        CountLog           count_log;
        GLuint             enable_send;
        std::vector<GLint> data;


        //+    Static Member Variable    +//
        static const std::string data_name;
        static       index_t     data_count;


        //+    Member Function    +//
        //_ Constructor
        IntData (Kernel&) noexcept;

        //_ Destructor
        virtual ~IntData (void) noexcept override =default;
    
        //_ Destructive Function
        void attach (void) noexcept;
    };
}

#include "int.inl"

#endif
