/*
 * ========================= foreach.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.04
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   所有的 foreach_ 系列函数
 * ----------------------------
 */
#include "srcs_engine.h"

//#include "debug.h" //- tmp

namespace esrc{ //------------------ namespace: esrc -------------------------//


/* ===========================================================
 *                     foreach_memGameObjs
 * -----------------------------------------------------------
 * -- 
 */
void foreach_memGameObjs( F_GOID_GOPTR _fp ){

    auto ipair = esrc::memGameObjs.begin();
    for( ; ipair!=esrc::memGameObjs.end(); ipair++ ){
        _fp( ipair->first, &(ipair->second) );
    }
}


/* ===========================================================
 *                 foreach_goids_active
 * -----------------------------------------------------------
 * -- 
 */
void foreach_goids_active( F_GOID_GOPTR _fp ){

    GameObj *goPtr;
    auto it = esrc::goids_active.begin();
    for( ; it!=esrc::goids_active.end(); it++ ){

        goPtr = (GameObj*)&(esrc::memGameObjs.at(*it));
        _fp( *it, goPtr );
    }
}



/* ===========================================================
 *                 foreach_goids_inactive
 * -----------------------------------------------------------
 * -- 
 */
void foreach_goids_inactive( F_GOID_GOPTR _fp ){

    GameObj *goPtr;
    auto it = esrc::goids_inactive.begin();
    for( ; it!=esrc::goids_inactive.end(); it++ ){

        goPtr = (GameObj*)&(esrc::memGameObjs.at(*it));
        _fp( *it, goPtr );
    }
}


/* ===========================================================
 *                draw_renderPool_goMeshs_pic
 * -----------------------------------------------------------
 * -- 
 */
void draw_renderPool_goMeshs_pic(){

    auto ipair = esrc::renderPool_goMeshs_pic.begin();
    for( ; ipair!=esrc::renderPool_goMeshs_pic.end(); ipair++ ){
        //-- 渲染持续，pos.z值小的 先渲染 --
        ipair->second->draw();
    }
}

/* ===========================================================
 *                draw_renderPool_goMeshs_shaodw
 * -----------------------------------------------------------
 * -- 
 */
void draw_renderPool_goMeshs_shadow(){
    
    for( auto &ptr : esrc::renderPool_goMeshs_shadow ){
        ptr->draw();
    }
}


/* ===========================================================
 *                draw_renderPool_meshs
 * -----------------------------------------------------------
 * -- 
 */
void draw_renderPool_meshs(){

    auto ipair = esrc::renderPool_meshs.begin();
    for( ; ipair!=esrc::renderPool_meshs.end(); ipair++ ){
        ipair->second->draw();
    }
}








}//---------------------- namespace: esrc -------------------------//
