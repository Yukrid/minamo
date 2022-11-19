#ifndef MINAMO_UNORDERED_MAP_DRAWER_INL
#define MINAMO_UNORDERED_MAP_DRAWER_INL

#include "unordered_map_drawer.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Drawer<K>    )//
    //+    Member Function    +//
    //_ Constant Function
    template <class A> auto UnorderedMapDrawer<A>::contains (index_t id_) const noexcept -> bool
    {
        return store.find(id_)!=store.end();
    }


    template <class A> auto UnorderedMapDrawer<A>::get_new_index (void) const noexcept -> index_t
    {
        index_t search_id=last_index+1;

        while(search_id!=last_index){
            
            if(contains(search_id)){
                ++search_id;
            }else{
                last_index=search_id;
                return search_id;
            }
        }
        
        std::cerr<<"valid ID not found."<<std::endl;
        std::exit(EXIT_FAILURE);
    }
}
#endif
