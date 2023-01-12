#ifndef MINAMO_FLOAT_HPP
#define MINAMO_FLOAT_HPP

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
    //(    minamo::FloatAttrib<D> Structure Template    )//
    template <dim_t D>
    struct FloatAttrib{
        
        //+    Member Variable     +//
        Kernel&        kernel;
        Variable       variable;
        LocationID     location_id;
        VertexOption   vertex_option;
    

        //+    Member Function    +//
        //_ Constructor
        FloatAttrib (Kernel&, const Variable&) noexcept;
        FloatAttrib (Kernel&, const std::string&) noexcept;
        
        //_ Destructor
        virtual ~FloatAttrib (void) noexcept =default;
    
        //_ Destructive Function
        void set_vert_option (const VertexOption&) noexcept;
   
        //_ Constant Function
        void prefix (void) const noexcept;
        void suffix (void) const noexcept;
    };



    //(    minamo::FloatData<D> Structure Template    )//
    template <dim_t D>
    struct FloatData : public FloatAttrib<D>{

        //+    Member Variable     +//
        CountLog             count_log;
        GLuint               enable_send;
        std::vector<GLfloat> data;


        //+    Static Member Variable    +//
        static const std::string data_name;
        static       index_t     data_count;


        //+    Member Function    +//
        //_ Constructor
        FloatData (Kernel&) noexcept;

        //_ Destructor
        virtual ~FloatData (void) noexcept override =default;
    
        //_ Destructive Function
        void attach (void) noexcept;

       //_ Constant Function
//    auto variable (void) const noexcept -> const Variable&;
    };
}

#include "float.inl"

#endif
