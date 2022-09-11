/**
 ******************************************************************************
 * @file    lv_100ask_demo_course_2_2_5.c
 * @author  ���ʿƼ�
 * @version V1.0
 * @date    2021-12-30
 * @brief	2_2_5 �εĿ��ô���
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2021-12-30     zhouyuebiao     First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2021 ���ڰ������Ƽ����޹�˾<https://www.100ask.net/>
 * All rights reserved
 *
 ******************************************************************************
 */


/*********************
 *      INCLUDES
 *********************/
//#include "../../lv_100ask_teach_demos.h"

#if 1

#include "lv_100ask_demo_course_2_2_5.h"
//#include "tim.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *  STATIC VARIABLES
 **********************/


 static void my_event_cb(lv_event_t * e)
{
//    lv_obj_t * obj = lv_event_get_target(e);        // ��ȡ�����¼��Ĳ���(����)
//    lv_event_code_t code = lv_event_get_code(e);    // ��ȡ��ǰ����(����)�������¼�����
    lv_obj_t * label = lv_event_get_user_data(e);   // ��ȡ����¼�ʱ���ݵ��û�����
    lv_obj_t * slider = lv_event_get_target(e);

    lv_label_set_text_fmt(label, "%d",(int)lv_slider_get_value(slider));
//		TIM14->CCR1=(int)lv_slider_get_value(slider);
//    printf("slider=%d\r\n",(int)lv_slider_get_value(slider));
//    switch(code){
//        case LV_EVENT_PRESSED:
//            lv_label_set_text(label, "LV_EVENT_PRESSED");
//            lv_obj_set_style_bg_color(obj, lv_color_hex(0xc43e1c), 0);  // ͨ��������ʽ(˽����ʽ)���ñ���ɫ
//            printf("LV_EVENT_PRESSED\n");
//            break;
//        case LV_EVENT_LONG_PRESSED:
//            lv_label_set_text(label, "LV_EVENT_LONG_PRESSED");
//            lv_obj_set_style_bg_color(obj, lv_color_hex(0x4cbe37), 0);  // ͨ��������ʽ(˽����ʽ)���ñ���ɫ
//            printf("LV_EVENT_LONG_PRESSED\n");
//            break;
//        default:
//            //printf("NONE\n");
//            break;
//    }
}

/**
 * Show how to style a slider.
 */
static void lv_example_slider_2(void)
{
    /*Create a transition*/
    static const lv_style_prop_t props[] = {LV_STYLE_BG_COLOR, 0};
    static lv_style_transition_dsc_t transition_dsc;
    lv_style_transition_dsc_init(&transition_dsc, props, lv_anim_path_linear, 300, 0, NULL);
//    lv_style_set_line_width(&transition_dsc,100);

    static lv_style_t style_main;           // ���α�������
    static lv_style_t style_indicator;      // ָ�벿��
    static lv_style_t style_knob;           // ��ť����
    static lv_style_t style_pressed_color;  // ����ĳ���ֱ�����ʱ���ò�����ʽӦ�õ���ɫ

    // ���α�������
    lv_style_init(&style_main);
    lv_style_set_bg_opa(&style_main, LV_OPA_COVER);
    lv_style_set_bg_color(&style_main, lv_color_hex3(0xbbb));
    lv_style_set_border_width(&style_main, 1);              //��ɫ���֣����ڲ�һ������
    lv_style_set_radius(&style_main, LV_RADIUS_CIRCLE);
    lv_style_set_pad_ver(&style_main, -2);                  //*Makes the indicator larger*/
    lv_style_set_size(&style_main,30);                      //���Ϳ�һ������
    lv_style_set_width(&style_main,80);                     //������ʽ���

    // ָ�벿��
    lv_style_init(&style_indicator);
    lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indicator, lv_palette_main(LV_PALETTE_CYAN));
    lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);
    lv_style_set_transition(&style_indicator, &transition_dsc);

    // ��ť����
    lv_style_init(&style_knob);
    lv_style_set_bg_opa(&style_knob, LV_OPA_COVER);
    lv_style_set_bg_color(&style_knob, lv_palette_main(LV_PALETTE_CYAN));
    lv_style_set_border_color(&style_knob, lv_palette_darken(LV_PALETTE_CYAN, 3));
    lv_style_set_border_width(&style_knob, 2);
    lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);
    lv_style_set_pad_all(&style_knob, 6); /*Makes the knob larger*/
    lv_style_set_transition(&style_knob, &transition_dsc);

    // ����ĳ���ֱ�����ʱ���ò�����ʽӦ�õ���ɫ
    lv_style_init(&style_pressed_color);
    lv_style_set_bg_color(&style_pressed_color, lv_palette_darken(LV_PALETTE_CYAN, 2));

    /*Create a slider and add the style*/

    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj,240, 320);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_slider_set_value(slider, 0,LV_ANIM_OFF);     //���û����ʼֵ
    lv_slider_set_range(slider, 0, 1000);            //���û��������Сֵ

    lv_obj_set_width(slider,50);                    //���ÿ��
    lv_obj_set_height(slider, 320);                 //���ø߶�
    lv_obj_set_size(slider,120, 20);                //���ô�С��������ߣ�
    lv_obj_align(slider,LV_ALIGN_CENTER,0,0);      //���ö��뷽ʽ

    lv_obj_t *label =lv_label_create(obj);
    lv_obj_align_to(label,slider,LV_ALIGN_OUT_TOP_MID,0,40);//�����һ���������ö��뷽ʽ


    lv_obj_add_event_cb(slider, my_event_cb, LV_EVENT_ALL, label);


//    lv_obj_set_pos();

    // �������̣������� lv_obj_add_style ����ע��ʱ��Ч����Ȼ��һ����ȥ��ע��
//    lv_obj_remove_style_all(slider);                                                        // ɾ�������������ʽ��Ȼ����������������Զ������ʽ
//    lv_obj_add_style(slider, &style_main, LV_PART_MAIN);                                    // ���α�������
//    lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);                          // ָ�벿��
//    lv_obj_add_style(slider, &style_pressed_color, LV_PART_INDICATOR | LV_STATE_PRESSED);   // ��ָ�벿�ֱ����µ�ʱ��ָ�벿��Ӧ�ø���ʽ
//    lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);                                    // ��ť���֣���ťһ������ץȡ����ֵ
//    lv_obj_add_style(slider, &style_pressed_color, LV_PART_KNOB | LV_STATE_PRESSED);        // ����ť���ֱ����µ�ʱ����ť����Ӧ�ø���ʽ
//
//    lv_obj_center(slider);
}




void lv_100ask_demo_course_2_2_5(void)
{
#if 0
    // ������ʽ
    static lv_style_t style_obj;

	lv_style_init(&style_obj);
    lv_style_set_bg_color(&style_obj, lv_color_hex(0x000000));      // ���ñ���ɫ
    lv_style_set_text_color(&style_obj, lv_color_hex(0xc43e1c));    // ����������ɫ
    lv_style_set_bg_color(&style_obj, lv_color_hex(0xc43e1c));    // ���ñ���ɫ
    lv_style_set_bg_opa(&style_obj, 30);                          // ������ɫ͸����

    static lv_style_t style_obj1;

	lv_style_init(&style_obj1);
    lv_style_set_bg_color(&style_obj1, lv_color_hex(0x000000));      // ���ñ���ɫ
    lv_style_set_text_color(&style_obj1, lv_color_hex(0xc43e1c));    // ����������ɫ
//    lv_style_set_bg_color(&style_obj1, lv_color_hex(0xc43e1c));    // ���ñ���ɫ
    lv_style_set_bg_opa(&style_obj1, 100);                          // ������ɫ͸����

    // ��������
    lv_obj_t * obj = lv_obj_create(lv_scr_act());

    lv_obj_t * obj2 = lv_obj_create(lv_scr_act());
    lv_obj_align(obj2, LV_ALIGN_CENTER, 0 ,0);

    // ������ʽ
//    lv_obj_set_style_bg_color(obj,  lv_color_hex(0xc43e1c), LV_STATE_PRESSED);    // ���ñ���ɫ
//    lv_obj_set_style_bg_color(obj2,  lv_color_hex(0xc43e1c), LV_STATE_PRESSED);   // ���ñ���ɫ
//    lv_obj_set_style_bg_opa(obj, LV_OPA_50, 0);	                                // ���ñ���͸����

    // �����ʽ������
    lv_obj_add_style(obj, &style_obj, 0);                   // Ĭ��״̬: LV_STATE_DEFAULT
    lv_obj_add_style(obj2, &style_obj, 0);                  // Ĭ��״̬: LV_STATE_DEFAULT
//    lv_obj_add_style(obj, &style_obj, LV_STATE_PRESSED);  // ����״̬�������󱻰��µ�ʱ��Ӧ�ø���ʽ
//    lv_obj_add_style(obj2, &style_obj1, LV_STATE_PRESSED); // ����״̬�������󱻰��µ�ʱ��Ӧ�ø���ʽ
#endif

    // ����ʾ��(����Ҫ�����о�����Ჿ����ʽ�Ĳ��ֺ�״̬����)���������ע�ͣ���������
    lv_example_slider_2();
}


#endif /* LV_USE_100ASK_DEMO_COURSE_2_2_5 */
