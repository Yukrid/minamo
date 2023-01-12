#ifndef MINAMO_UINT_HPP
#define MINAMO_UINT_HPP

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
    //(    minamo::UintAttrib<D> Structure Template    )//
    template <dim_t D>
    struct UintAttrib{
        
        //+    Member Variable     +//
        Kernel&        kernel;
        Variable       variable;
        LocationID     location_id;
        VertexOption   vertex_option;
    

        //+    Member Function    +//
        //_ Constructor
        UintAttrib (Kernel&, const Variable&) noexcept;
        UintAttrib (Kernel&, const std::string&) noexcept;
        
        //_ Destructor
        virtual ~UintAttrib (void) noexcept =default;
    
        //_ Destructive Function
        void set_vert_option (const VertexOption&) noexcept;
   
        //_ Constant Function
        void prefix (void) const noexcept;
        void suffix (void) const noexcept;
    };



    //(    minamo::UintData<D> Structure Template    )//
    template <dim_t D>
    struct UintData : public UintAttrib<D>{

        //+    Member Variable     +//
        CountLog            count_log;
        GLuint              enable_send;
        std::vector<GLuint> data;


        //+    Static Member Variable    +//
        static const std::string data_name;
        static       index_t     data_count;


        //+    Member Function    +//
        //_ Constructor
        UintData (Kernel&) noexcept;

        //_ Destructor
        virtual ~UintData (void) noexcept override =default;
    
        //_ Destructive Function
        void attach (void) noexcept;
    };
}

#include "uint.inl"

#endif
