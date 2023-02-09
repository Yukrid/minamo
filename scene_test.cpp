#include <minamo/system/scene.hpp>
#include <iostream>
#include <thread>

using namespace minamo;
using namespace std::chrono_literals;

int main(void){
    
    // Scenesクラスの宣言
    // (引数に数字を入れるとシーンのログの長さを変更できる．デフォルトは3)
    system::Scenes scenes;
    
    // 3つのシーンを同時追加
    // (IDはそれぞれ，head, head+1, head+2である)
    minamo::index_t head = scenes.append(3); 

    // (キャプチャする変数)
    uint32_t count = 0;

    // 1つ目のシーンにDraw関数をセット
    // (キャプチャで関数外の変数を使うことができる)
    scenes.set(head+0, system::Scenes::DRAW, [&](system::Scenes& sc_){
        
        // get_scene_id関数で現在・過去のシーンIDを取得できる
        // (get_scene_id(0)は現在のシーンID，get_scene_id(1)は1つ前のシーンID...，シーンのログの長さはScenesのコンストラクタの引数で設定可)
        std::cout<<"First Draw "<<sc_.get_scene_id(0)<<" "<<sc_.get_scene_id(1)<<" "<<sc_.get_scene_id(2)<<std::endl;
       
        ++count;
        if(count==5){
            count=0;
            uint32_t val;
            std::cout<<"Which scene you jump(1-3)?"<<std::endl;
            std::cin>>val;
    
            // 条件に応じてジャンプ
            // （ジャンプ時，ジャンプするシーンにJump関数がセットされている場合は，毎回実行される) 
            // （Initailize関数は，そのシーンへの最初の一回目のジャンプの時のみ実行される) 
            if     (val==2) sc_.jump(head+1);
            else if(val==3) sc_.jump(head+2);
        }
        
        return 0;
    });

    
    // 2つ目のシーンにDraw・Jump関数をまとめてセット
    scenes.set(head+1, [&](system::Scenes& sc_){
   
        // Draw Function
        std::cout<<"Second Draw "<<sc_.get_scene_id(0)<<" "<<sc_.get_scene_id(1)<<" "<<sc_.get_scene_id(2)<<std::endl;
        
        ++count;
        if(count==5){
            count=0;
            uint32_t val;
            std::cout<<"Which scene you jump(1-3)?"<<std::endl;
            std::cin>>val;
            
            if     (val==1) sc_.jump(head+0);
            else if(val==3) sc_.jump(head+2);
        }
        
        return 0;
    
    }, [](system::Scenes& sc_){
        
        // Jump Function
        std::cout<<"Second Jump"<<std::endl;
        
        return 0;

    // nullptrを入れて関数をセットしないこともできる（何もしない関数をわざわざセットする必要はない）．
    }, nullptr);


    // 3つ目のシーンにDraw・Jump・Initialize関数をまとめてセット
    scenes.set(head+2, [&](system::Scenes& sc_){

        // Draw Function
        
        std::cout<<"Third Draw "<<sc_.get_scene_id(0)<<" "<<sc_.get_scene_id(1)<<" "<<sc_.get_scene_id(2)<<std::endl;

        ++count;
        if(count==5){
            count=0;
            uint32_t val;
            std::cout<<"Which scene you jump(1-3)?"<<std::endl;
            std::cin>>val;
            
            if     (val==1) sc_.jump(head+0);
            else if(val==2) sc_.jump(head+1);
        }
        
        return 0;

    }, [](system::Scenes& sc_){
        
        // Jump Function
        std::cout<<"Third Jump"<<std::endl;
        
        return 0;
    
    }, [](system::Scenes& sc_){

        // Initialize Function
        std::cout<<"Third Initialize"<<std::endl;
        
        return 0;
    });
    

    // シーン1にジャンプ
    // (Scenes初期化時にシーン0が生成・設定される．シーン0はデフォルトで何も関数がセットされていないシーンである．)
    scenes.jump(head);

    while(true){
        
        // 今のシーンを描画
        // (今のシーンにセットされた Draw Function がコールされる)
        scenes.draw();
        
        std::this_thread::sleep_for(500ms);
    }

}
