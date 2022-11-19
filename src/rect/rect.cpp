#include "minamo/rect/rect.hpp"

//===============================//
//    Namespace: minamo::rect    //
//========------=================//
namespace minamo::rect{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::rect::Rect    )//
    //+    Member Function    +//
    void Rect::calc (void) noexcept
    {
        glm::vec4 base_coord(region.base_coord, 1.f);

        switch(region.anchor){
    
            case Region::CENTER:
            case Region::DEFAULT:
            {
                coords[0]=glm::vec4(-region.scale[0]*0.5f, -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0]*0.5f, -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0]*0.5f,  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0]*0.5f,  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                break;
            }
            case Region::LEFT_TOP:
            {
                coords[0]=glm::vec4(             0.f, -region.scale[1], 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0], -region.scale[1], 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(             0.f,              0.f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0],              0.f, 0.f, 0.f)+base_coord;
                break;
            }
        
            case Region::LEFT_CENTER:
            {
                coords[0]=glm::vec4(             0.f, -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0], -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(             0.f,  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0],  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                break;
            }
            case Region::LEFT_BOTTOM:
            {
                coords[0]=glm::vec4(             0.f,              0.f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0],              0.f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(             0.f,  region.scale[1], 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0],  region.scale[1], 0.f, 0.f)+base_coord;
                break;
            }
            case Region::CENTER_BOTTOM:
            {
                coords[0]=glm::vec4(-region.scale[0]*0.5f,             0.f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0]*0.5f,             0.f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0]*0.5f, region.scale[1], 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0]*0.5f, region.scale[1], 0.f, 0.f)+base_coord;
                break;
            }
            case Region::RIGHT_BOTTOM:
            {
                coords[0]=glm::vec4(-region.scale[0],              0.f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4(             0.f,              0.f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0],  region.scale[1], 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4(             0.f,  region.scale[1], 0.f, 0.f)+base_coord;
                break;
            }
            case Region::RIGHT_CENTER:
            {
                coords[0]=glm::vec4(-region.scale[0], -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4(             0.f, -region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0],  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4(             0.f,  region.scale[1]*0.5f, 0.f, 0.f)+base_coord;
                break;
            }
            case Region::RIGHT_TOP:
            {
                coords[0]=glm::vec4(-region.scale[0], -region.scale[1], 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4(             0.f, -region.scale[1], 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0],              0.f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4(             0.f,              0.f, 0.f, 0.f)+base_coord;
                break;
            }
            case Region::CENTER_TOP:
            {
                coords[0]=glm::vec4(-region.scale[0]*0.5f, -region.scale[1], 0.f, 0.f)+base_coord;
                coords[1]=glm::vec4( region.scale[0]*0.5f, -region.scale[1], 0.f, 0.f)+base_coord;
                coords[2]=glm::vec4(-region.scale[0]*0.5f,              0.f, 0.f, 0.f)+base_coord;
                coords[3]=glm::vec4( region.scale[0]*0.5f,              0.f, 0.f, 0.f)+base_coord;
                break;
            }
        }

        return;
    }

        
    void Rect::resize (GLfloat scale_[2]) noexcept
    {
        if(scale_[0]>=0.f) region.scale[0]=scale_[0];
        if(scale_[1]>=0.f) region.scale[1]=scale_[1];
        
        calc();
        
        return;
    }


    void Rect::move (const glm::vec3& v3_, Region::Anchor anc_) noexcept
    {
                                  region.base_coord=v3_;
        if(anc_!=Region::DEFAULT) region.anchor=anc_;
    
        calc();

        return;
    }

 
    void Rect::move (Region::Anchor anc_) noexcept
    {
        if(anc_!=Region::DEFAULT) region.anchor=anc_;
    
        calc();

        return;
    }
}
