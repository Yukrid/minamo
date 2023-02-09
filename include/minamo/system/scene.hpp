#ifndef MINAMO_SYSTEM_SCENE_HPP
#define MINAMO_SYSTEM_SCENE_HPP

#include "../forward.hpp"

#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

//=================================//
//    Namespace: minamo::system    //
//=================================//
namespace minamo::system{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::system::Scenes Structure    )//
    class Scenes{
     
        //+    Type Definiton    +//
        public:
        //(    minamo::system::Scenes::() Enumeration    )//
        enum : uint8_t{
            DRAW, JUMP, INITIALIZE
        };

        private:
        //(    minamo::system::Scenes::Scene Structure    )//
        struct Scene{
            
            //+    Alias    +//
            using Func = std::function<int32_t(Scenes&)>;

            //+    Member Variable    +//
            bool  not_initialized = true;
            Func  draw            = nullptr;
            Func  jump            = nullptr;
            Func  leave           = nullptr;
            Func  initialize      = nullptr;
            void* data            = nullptr;
        };

        
        private:
        //+   Member Variable   +//
        std::vector<Scene>  _scenes;
        std::deque<index_t> _log;
        void*               _data;
        

        public:
        //+    Membar Function    +//
        //_ Constructor
        Scenes (size_t =3)     noexcept;
        Scenes (const Scenes&) noexcept;
        Scenes (Scenes&&)      noexcept;
        
        //_ Constant Function
        auto get_scene_id    (size_t =0)           -> index_t;
        auto get_log        (void)       noexcept -> const std::deque<index_t>&;
        auto is_initialized (index_t)             -> bool;

        //_ Variable Function
        auto append (size_t)                                                              -> index_t;
        auto append (const Scene::Func&, const Scene::Func&, const Scene::Func&)          -> index_t;
        void set    (index_t, uint8_t, const Scene::Func&);
        void set    (index_t, const Scene::Func&, const Scene::Func&, const Scene::Func&);

        auto data  (void)    noexcept -> void*;
        auto data  (index_t)          -> void*;
        auto draw  (void)    noexcept -> int32_t;
        auto jump  (index_t)          -> int32_t;
        void clear (void)    noexcept;
    };
}
#endif
