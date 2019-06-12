/*
 * ========================= uiSpecIds.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2018.12.23
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   将 具象ui species 注册到 
 *    ssrc::ui_specId_names 
 *    ssrc::ui_name_specIds 中去
 * ----------------------------
 */
//-------------------- CPP --------------------//
#include <string>

//-------------------- Engine --------------------//
#include "UIObjType.h"

//-------------------- Script --------------------//
#include "Script/resource/ssrc.h" 
#include "Script/UIs/allUIs.h"

using namespace std::placeholders;

using std::string;

//#include "tprDebug.h" //- tmp


namespace {//------------------- namespace ---------------------
    void uiSpec_alloc( uiObjSpecId_t _id, const string &_name );
}//------------------------- namespace: end -------------------


/* ===========================================================
 *                   onUISpecIds_SignUp   
 * -----------------------------------------------------------
 * 
 */
void onUISpecIds_SignUp(){

    uiObjSpecId_t   id;

    
    ssrc::clear_uiInit_funcs();
    ssrc::clear_ui_specId_names();
    ssrc::clear_ui_name_specIds();

    //uiSpecIds.insert(0); //--- 0号id 保留。
    //==================================//

    id = 1;   //- 
        uiSpec_alloc( id, "button_sceneBegin_archive" ); 
        uis::Button_SceneBegin_Archive::specId = id;
        ssrc::insert_2_uiInit_funcs( id, std::bind( &uis::Button_SceneBegin_Archive::init_in_autoMod, &uis::button_sceneBegin_archive, _1, _2 ) );

    id = 2;   //- 
        uiSpec_alloc( id, "button_sceneBegin_pointer" ); 
        uis::Button_SceneBegin_Pointer::specId = id;
        ssrc::insert_2_uiInit_funcs( id, std::bind( &uis::Button_SceneBegin_Pointer::init_in_autoMod, &uis::button_sceneBegin_pointer, _1, _2 ) );


    //cout << "--- onGoSpecIds_SignUp(). DONE. ---" << endl; 
}



namespace {//------------------- namespace ---------------------



/* ===========================================================
 *                   uiSpec_alloc      
 * -----------------------------------------------------------
 * -- 拼装 正反表
 */
void uiSpec_alloc( uiObjSpecId_t _id, const string &_name ){
    ssrc::insert_2_ui_specId_names_containers( _id, _name );
}

}//------------------------- namespace: end -------------------





