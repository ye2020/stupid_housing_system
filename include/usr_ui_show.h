/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_ui_show.c/h
  * @brief      用于存放ui绘制相关的数据和方法
  * @note       none
  * 
  * @author     Y.Z.T
  * @history    2023.9.26
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#ifndef _USR_UI_SHOW_H
#define _USR_UI_SHOW_H

#include <Arduino.h>
#include <vector>
#include <U8g2lib.h>
#include "usr_buletooth.h"



// ACE图标 width: 50, height: 50
const unsigned char ACE[] U8X8_PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x0c,0x00,0x00,0x00,0x00,0x00,0xc0,0x0c,0x00,0x00,0x00,0x00,0x00,0xc0,
                                           0x1c,0x00,0x00,0x00,0x00,0x00,0xe0,0x1c,0x00,0x00,0x00,0x00,0x00,0xf0,0x3c,0x00,0x00,0x00,0x00,0x00,0xf0,0x3c,0x00,0x00,
                                           0x00,0x00,0x00,0xf8,0x7c,0x00,0x00,0x00,0x00,0x00,0xf8,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,
                                           0xfc,0xfc,0x01,0x00,0x00,0x00,0x00,0xfe,0xfc,0x01,0x00,0x00,0x00,0x00,0xff,0xfc,0x03,0x00,0x00,0x00,0x00,0xff,0xfc,0x03,
                                           0x00,0x00,0x00,0x80,0xff,0xfc,0x07,0x00,0x00,0x00,0x80,0xff,0xfc,0x0f,0x00,0x00,0x00,0xc0,0x7f,0xf8,0x0f,0x00,0x00,0x00,
                                           0xc0,0x7f,0xf8,0x1f,0x00,0x00,0x00,0xe0,0x3f,0xf0,0x1f,0x00,0x00,0x00,0xf0,0x3f,0xe0,0x3f,0x00,0x00,0x00,0xf0,0x1f,0xe0,
                                           0x3f,0x00,0x00,0x00,0xf8,0x0f,0xc0,0x7f,0x00,0x00,0x00,0xf8,0x0f,0xc0,0xff,0x00,0x00,0x00,0xfc,0x07,0x80,0xff,0x00,0x00,
                                           0x00,0xfc,0x07,0x00,0xff,0x01,0x00,0x00,0xfe,0x03,0x03,0xff,0x01,0x00,0x00,0xff,0x03,0x07,0xfe,0x03,0x00,0x00,0xff,0x81,
                                           0x07,0xfe,0x03,0x00,0x00,0xfe,0xc0,0x0f,0xfc,0x01,0x00,0x00,0xfe,0xc0,0x0f,0xfc,0x01,0x00,0x00,0x7c,0xe0,0x1f,0xf8,0x00,
                                           0x00,0x00,0x78,0xe0,0x3f,0xf0,0x00,0x00,0x00,0x38,0xf0,0x3f,0x70,0x00,0x00,0x00,0x30,0xf0,0x38,0x60,0x00,0x00,0x00,0x10,
                                           0x70,0x38,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x80,0xc1,0xcd,0x3f,0x00,0x00,0x00,
                                           0x80,0xe1,0x08,0x00,0x00,0x00,0x00,0x00,0x63,0x00,0x00,0x00,0x00,0x00,0x40,0x23,0xc0,0x3e,0x00,0x00,0x00,0x60,0x26,0x80,
                                           0x3e,0x00,0x00,0x00,0x60,0x67,0x00,0x00,0x00,0x00,0x00,0xb0,0xcf,0x9c,0x1f,0x00,0x00,0x00,0x30,0xcc,0xcd,0x3f,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


// width: 13, height: 10
const unsigned char wifi_13_10[] U8X8_PROGMEM = { 0xf0,0x01,0x1c,0x07,0x07,0x1c,0xf1,0x11,0x1c,0x07,0x44,0x04,0xf0,0x01,0x10,0x01,0x40,0x00,0x40,0x00 };

// wifi断
const unsigned char dis_wifi_13_11[] U8X8_PROGMEM = { 0x00,0x08,0x00,0x0c,0xf8,0x07,0xfe,0x0f,0xbf,0x1f,0xde,0x0f,0xac,0x07,0xd0,0x03,0xe8,0x01,0xe4,0x00,0x02,0x00 };


// 
const unsigned char battery_16_9[] U8X8_PROGMEM =  { 0xfc,0x7f,0x02,0x80,0x9a,0xbb,0x9b,0xb3,0x9b,0xb3,0x9b,0xb3,0x9a,0xb3,0x02,0x80,0xfc,0x7f };

/* 位置与位置期望 */
typedef struct 
{
    int16_t cur_position;       // 当前位置
    int16_t position_trg;       // 期望位置

}position_expect_t;


/* 存放ui绘制相关的数据的方法 */
class ui_show_t{
    public:

    position_expect_t menu_x_position = {0, 0};                                      // 菜单x位置与期望    
    position_expect_t menu_y_position = {28, 28};                                    // 菜单y位置与期望
    position_expect_t frame_len = {32, 32};                                          // 选择框的宽度
    position_expect_t frame_y = {17, 17};                                            // 选择框的高度
    position_expect_t progress_position {16, 16};                                    // 进度条的位置

    uint8_t max_bar;                                                        // 进度条最底部的位置
    uint8_t y_offset = 16;                                                  // y偏移值 , 为了不在最上面的黄色部分显示
    uint8_t select_index;                                                     // 菜单索引, 表示实际指向的表单


    int16_t line_len;                                                       // 选择页面的数量
    uint8_t single_line_length;                                             // 进度条单元格长度
    uint8_t total_line_length;                                              // 进度条长竖线的长度

    uint8_t screen_length = 128;                                            // 屏幕长度
    uint8_t screen_height = 64 ;                                            // 屏幕高度

    
    /* 菜单相关属性 */
    typedef struct                                                          
    {                               
        String str;                                                          // 选项名字符串
        int len;                                                             // 该选项的长度用于设置选择框的长度(一般设置为字符个数 + 2)
    }Ui_list_t;                             


    std::vector<Ui_list_t> list;                                             // 菜单项数组 

    ui_show_t();                                                            // 构造函数

    int  ui_run(int16_t *res, int16_t *res_trg, int16_t step);              // 实现动画效果(渐进)
    void select_ui_show(int16_t speed_x, int16_t speed_y);                  // 选择框绘制函数
    void ui_init(void);                                                     // ui初始化函数
    void progress_ui_show(void);                                            // 进度条绘制函数
    void menu_ui_show(void);                                                // 菜单绘制函数
    bool ui_disapper(void);                                                 // 消失函数

    private:







};


extern ui_show_t ui_show;

void ui_test(button_status_e keybt0, button_status_e keybt1);
void top_ui_show(void);


#endif