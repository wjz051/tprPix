/*
 * =================== load_and_divide_png.h =================
 *                          -- tpr --
 *                                        创建 -- 2019.01.13
 *                                        修改 -- 2019.01.13
 * ----------------------------------------------------------
 *    加载 解析 “图元帧式的png文件” 
 * ----------------------------
 */
//-- 全局唯一 
#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h" //-- 加载图片数据用

//-------------------- CPP --------------------//
#include <vector>
#include <string>

//------------------- Engine --------------------//
#include "RGBA.h"
#include "PixVec.h"

/* ===========================================================
 *                load_and_divide_png
 * -----------------------------------------------------------
 * -- param: _path   -- png文件的 绝对path
 * -- param: _frames -- xy轴 图元帧 个数
 * -- param: _pixes_per_frame -- 每一图元帧 xy轴 像素个数
 * -- param: _frame_data_ary -- 将每一帧的图形数据，存入这组 帧容器中
 */
void load_and_divide_png( const std::string &_path,
                          const PixVec2 &_frames,
                          const PixVec2 &_pixes_per_frame,
        std::vector< std::vector<RGBA>> &_frame_data_ary ){

    //------------------------------//
    //   加载 png图片，获得其 原始数据
    //------------------------------//
    int width;
    int height;
    int nrChannels;
    unsigned char *data; //-- 临时，图片数据的指针。
                        //- 真实数据存储在 stbi 模块自己创建的 内存中。
                        //- 我们只获得一个 调用指针。

    stbi_set_flip_vertically_on_load( 1 ); //-- 防止 图片 y轴颠倒。
    data = stbi_load( _path.c_str(), &width, &height, &nrChannels, 0 );
    assert( data != nullptr );

    //------------------------------------//
    //   获得 每一帧的数据, 存入各自 帧容器中
    //------------------------------------// 
    int frames_total = _frames.x * _frames.y; //- 总帧数

    //-- 事先准备好 每一帧的容器 --
    _frame_data_ary.clear();
    for( int i=0; i<frames_total; i++ ){
        std::vector<RGBA> v {};
        _frame_data_ary.push_back( v );//- copy
    }

    auto fit = _frame_data_ary.begin(); //- 指向某个 帧容器

    int wf; //-- 以帧为单位，目标像素在横排中 的序号
    int hf; //-- 以帧为单位，目标像素的 纵向 序号 (左下坐标系)
    int antihf; //-- 以帧为单位，目标像素的 纵向 序号 (左上坐标系，我们要的)
    int nrf; //-- 像素 属于的 帧序号

    RGBA *pixhead = (RGBA*)data;
    RGBA *pixp; //- tmp

    //--- 遍历 png 中的 每一像素 ---
    for( int h=0; h<height; h++  ){
        for( int w=0; w<width; w++  ){

            //-- 计算 本像素 所属帧的容器 的迭代器 fit --
            wf = w/_pixes_per_frame.x;
            hf = h/_pixes_per_frame.y;
            hf = _frames.y - 1 - hf; 
                        //- 关键步骤！修正帧排序，(注意必须先减1，可画图验证)
                        //- 现在，帧排序从 左下 修正为 左上角坐标系
            nrf = hf*_frames.x + wf;
            fit = _frame_data_ary.begin() + nrf;
            assert( nrf < frames_total ); //- 避免迭代器越界

            //-- 获得 本像素 的数据 --
            pixp = pixhead + (h*width + w);

            //-- 将数据 压入 对应的 帧容器 中 --
            fit->push_back( *pixp ); //-copy
        }
    }
    //-- png图片 原始数据已经没用了，释放掉 ---
    stbi_image_free( data );
}

