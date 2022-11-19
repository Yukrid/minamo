#ifndef MINAMO_DRAWER_HPP
#define MINAMO_DRAWER_HPP

#include <iostream>

#include "forward.hpp"
#include "kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //(    minamo::Drawer    )//
    struct Drawer : public virtual Kernel{
        
        //+    Member Function    +//
        //_ Constructor
        Drawer (void) noexcept;

        //_ Destructor
        virtual ~Drawer (void) noexcept override;

        //_ Destructive Function
        virtual void attach_cb (void*)          noexcept       =0;    
        virtual void attach    (void* =nullptr) noexcept final;

        //_ Constant Function
        virtual void draw_cb (void*)          const noexcept       =0;    
        virtual void draw    (void* =nullptr) const noexcept final;
    };
}

#endif
