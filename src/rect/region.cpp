#include <new>

#include "minamo/rect/region.hpp"

//===============================//
//    Namespace: minamo::rect    //
//===============================//
namespace minamo::rect{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::rect::Region    )//
    //+    Member Function    +//
    //_ Constructor
    Region::Region (void) noexcept
        : base_coord { }
        , anchor     {Anchor::DEFAULT}
        , scale      {1.f, 1.f}
    {
        return;
    }


    Region::Region (const glm::vec3& v3_, Anchor anc_, std::initializer_list<GLfloat> scale_) noexcept
        : base_coord {v3_}
        , anchor     {anc_}
        , scale      {scale_.begin()[0], scale_.begin()[1]}
    {
        return;
    }
 

    auto Region::construct (const glm::vec3& v3_, Anchor anc_, std::initializer_list<GLfloat> scale_) noexcept -> Region&
    {
        new(this) Region(v3_, anc_, scale_);

        return *this;
    }
   
    
    //_ Destuctor
    auto Region::destruct (void) noexcept -> Region&
    {
        this->~Region();

        return *this;
    }
}
