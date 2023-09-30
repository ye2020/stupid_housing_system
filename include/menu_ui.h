/**
  ****************************** Y.Z.T.****************************************
  * @file       menu_ui.c/h
  * @brief      �ṩ�˵������UI�Ĵ���
  * @note
  * @history    2022.7.8
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#ifndef __MENU_UI_H
#define __MENU_UI_H

#include "menu.h"
#include <Arduino.h>


void Menu_Main_Init(void);

void Enter_Page(menu_i32 index, button_status_e Key5Value, button_status_e Key0Value);

void main_page_ui_process(void);
void wifi_page_ui_process(void);
void select_page_ui_process(void);


#endif