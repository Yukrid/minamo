#include "minamo/system/scene.hpp"
#include <iostream>

//=================================//
//    Namespace: minamo::system    //
//=================================//
namespace minamo::system{

    //(    minamo::system::Scenes Structure    )//
    //_ Constructor
    Scenes::Scenes (size_t ls_) noexcept
        : _scenes   {1}
        , _log      (ls_)
        , _data     {nullptr}
    {
        std::fill(_log.begin(), _log.end(), 0);
            
        return;
    }



    //_ Constant Function
    auto Scenes::get_scene_id (index_t id_) -> index_t
    {
        return _log.at(id_);
    }


    auto Scenes::get_log (void) noexcept -> const std::deque<index_t>&
    {
        return _log;
    }
 

    auto Scenes::is_initialized (index_t id_) -> bool
    {
        return not _scenes.at(id_).not_initialized;
    }
 


    //_ Variable Function
    auto Scenes::append (size_t sz_) -> index_t
    {
        size_t origin = _scenes.size();
        _scenes.resize(origin+sz_);

        return origin;
    }


    auto Scenes::append (const Scene::Func& df_, const Scene::Func& jf_, const Scene::Func& lf_, const Scene::Func& if_) -> index_t
    {
        _scenes.resize(_scenes.size()+1);
        
        Scene& scene=*(_scenes.end()-1);
        scene.draw       = df_;
        scene.jump       = jf_;
        scene.leave      = lf_;
        scene.initialize = if_;

        return _scenes.size()-1;
    }


    void Scenes::set (index_t id_, uint8_t pos_, const Scene::Func& f_)
    {
        Scene& scene=_scenes.at(id_);
        switch(pos_){
            
            case DRAW:
                scene.draw = f_;
                return;
            
            case JUMP:
                scene.jump = f_;
                return;
 
            case LEAVE:
                scene.leave = f_;
                return;
           
            case INITIALIZE:
                scene.initialize      = f_;
                scene.not_initialized = true;
                return;
            
            default:
                return;
        }
    }


    void Scenes::set (index_t id_, const Scene::Func& df_, const Scene::Func& jf_, const Scene::Func& lf_, const Scene::Func& if_)
    {
        Scene& scene=_scenes.at(id_);
 
        scene.draw       = df_;
        scene.jump       = jf_;
        scene.leave      = lf_;
        scene.initialize = if_;
       
        return;
    }


    auto Scenes::data (void) noexcept -> void*
    {
        return _data;
    }


    auto Scenes::data (index_t id_) -> void*
    {
        return _scenes.at(id_).data;
    }


    auto Scenes::draw (void) noexcept -> int32_t
    {
        Scene& scene = _scenes[_log[0]];

        if(scene.draw) return scene.draw(*this);
        else           return 0;
    }
    

    auto Scenes::jump (index_t id_) -> int32_t
    {
        Scene& scene = _scenes.at(id_);

        if(_scenes[_log[0]].leave){
            
            if(int32_t ret = _scenes[_log[0]].leave(*this)) return ret;    
        }

        if(scene.not_initialized and scene.initialize){

            scene.not_initialized = false;
            if(int32_t ret = scene.initialize(*this)) return ret;
        }
        
        if(scene.jump){

            if(int32_t ret = scene.jump(*this)) return ret;
        }

        _log.pop_back();
        _log.push_front(id_);

        return 0;
    }

    
    void Scenes::clear (void) noexcept
    {
        size_t log_size = _log.size();
        this->~Scenes();
        new(this) Scenes(log_size);

        return;
    }
}
