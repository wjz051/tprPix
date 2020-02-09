/*
 * ========================= CampfireChild.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.11.16
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#include "Script/gameObjs/majorGos/campfire/CampfireChild.h"

//-------------------- CPP --------------------//
#include <functional>
#include <string>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "Density.h"
#include "animSubspeciesId.h"
#include "dyParams.h"

#include "esrc_shader.h" 
#include "esrc_animFrameSet.h"

//-------------------- Script --------------------//


using namespace std::placeholders;

#include "tprDebug.h" 


namespace gameObjs {//------------- namespace gameObjs ----------------


struct CampfireChild_PvtBinary{
    int   tmp {};
};



void CampfireChild::init(GameObj &goRef_,const DyParam &dyParams_ ){


    //================ go.pvtBinary =================//
    auto *pvtBp = goRef_.init_pvtBinary<CampfireChild_PvtBinary>();

    // DyParam 中传入的 subid 暂时是无意义的，自行指定
    animSubspeciesId_t rootSubId = esrc::get_squareCollide_emptyPixId();
    

    //================ dyParams =================//
    size_t typeHash = dyParams_.get_typeHash();
    tprAssert( typeHash == typeid(DyParams_Blueprint).hash_code() );
    const DyParams_Blueprint *bpParamPtr = dyParams_.get_binaryPtr<DyParams_Blueprint>();
    const GoDataForCreate *goDataPtr = bpParamPtr->goDataPtr;
    tprAssert( !goDataPtr->isMultiGoMesh ); // must single gomesh
    const GoDataEntForCreate &goDataEntRef = *(*goDataPtr->goMeshDataUPtrs.cbegin()); // only one

    //----- must before creat_new_goMesh() !!! -----//
    goRef_.actionDirection.reset( goDataPtr->direction );

    if( auto retOpt = goDataPtr->get_brokenLvl(); retOpt.has_value() ){
        goRef_.brokenLvl.reset( retOpt.value() );
    }else{
        tprAssert(0);
    }

                        

    //================ animFrameSet／animFrameIdxHandle/ goMesh =================//
    //-- 制作唯一的 mesh 实例: "root" --
    goRef_.creat_new_goMesh("root", //- gmesh-name
                                rootSubId, // emptyPix 透明 afs
                                AnimActionEName::Idle,
                                RenderLayerType::MajorGoes, //- 不设置 固定zOff值
                                &esrc::get_shaderRef(ShaderType::UnifiedColor),  // pic shader
                                goDataEntRef.dposOff, //- pposoff
                                0.0,  //- zOff
                                true //- isVisible
                                );


            // 目前的 campfireChild 就是一个 占位go，实现碰撞检测
            // 在未来，要和 campfire 实例 形成关联，传递 函数对象
            // ...
        
    //================ bind callback funcs =================//
    //-- 故意将 首参数this 绑定到 保留类实例 dog_a 身上
    goRef_.RenderUpdate = std::bind( &CampfireChild::OnRenderUpdate,  _1 );   
    goRef_.LogicUpdate  = std::bind( &CampfireChild::OnLogicUpdate,   _1 );

    //-------- actionSwitch ---------//
    goRef_.actionSwitch.bind_func( std::bind( &CampfireChild::OnActionSwitch,  _1, _2 ) );
    goRef_.actionSwitch.signUp( ActionSwitchType::Idle );


    //================ go self vals =================//   

}



void CampfireChild::OnRenderUpdate( GameObj &goRef_ ){
    //=====================================//
    //            ptr rebind
    //-------------------------------------//
    //auto *pvtBp = goRef_.get_pvtBinaryPtr<CampfireChild_PvtBinary>();

    //=====================================//
    //  将 确认要渲染的 goMeshs，添加到 renderPool         
    //-------------------------------------//
    goRef_.render_all_goMesh();
}



void CampfireChild::bind( GameObj &goRef_ ){ /* do nothing... */ }
void CampfireChild::rebind( GameObj &goRef_ ){ /* do nothing... */ }
void CampfireChild::OnLogicUpdate( GameObj &goRef_ ){ /* do nothing... */ }
void CampfireChild::OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ ){ tprAssert(0); }







}//------------- namespace gameObjs: end ----------------
