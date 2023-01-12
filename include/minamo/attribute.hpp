#ifndef MINAMO_ATTRIBUTE_HPP
#define MINAMO_ATTRIBUTE_HPP

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //+    Type Definition    +//
    //(    minamo::VertexOption Structure    )//
    struct VertexOption{
        
        //+    Member Variable     +//
        GLboolean normalized =GL_FALSE;
        GLsizei   stride     =0;
        void*     pointer    =nullptr;
    };
    

    //(    minamo::ProgAttribID Structure    )//
    struct ProgAttribID{

        //+    Member Variable     +//
        GLuint  program_id;
        index_t attribute_id;
    };
}
#endif
