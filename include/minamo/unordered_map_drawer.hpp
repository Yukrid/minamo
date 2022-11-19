#ifndef MINAMO_UNORDERED_MAP_DRAWER_HPP
#define MINAMO_UNORDERED_MAP_DRAWER_HPP

#include <unordered_map>

#include "forward.hpp"
#include "drawer.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //(    minamo::Drawer    )//
    template <class A>
    struct UnorderedMapDrawer : public Drawer{

        //+    Member Variable    +//
        std::unordered_map<index_t, A> store;


        //+    Member Function    +//
        mutable index_t last_index =0;


        //+    Member Function    +//
        //_ Constructor
        UnorderedMapDrawer (void) noexcept =default;

        //_ Destructor
        virtual ~UnorderedMapDrawer (void) noexcept override =default;

        //_ Constant Function
        auto contains      (index_t) const noexcept -> bool;
        auto get_new_index (void)    const noexcept -> index_t;
    };
}

#include "unordered_map_drawer.inl"

#endif
