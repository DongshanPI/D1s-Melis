/*
********************************************************************************
*                                    eMOD
*                   the Easy Portable/Player Develop Kits
*                               mod_lotus sub-system
*
*          (c) Copyright 2009-2010, Allwinner Microelectronic Co., Ltd.
*                              All Rights Reserved
*
* File   : mod_video_play.h
* Version: V1.0
* By     : Eric_wang
* Date   : 2009-12-21
********************************************************************************
*/
#ifndef _MOD_VIDEO_PLAY_H_
#define _MOD_VIDEO_PLAY_H_

/*******************************************************************************
* type name: __video_play_cmd_set_t
* Description:
*    ��Ƶ(csi/tvin)��ʾý��(IOCtrol), ���ƺ���ԭ��:
*    __s32 esMODS_MIoctrl(__mp *mp, __u32 cmd, __s32 aux, void *pbuffer)
*    mp: video_play�м��ģ����
*    cmd: __video_play_cmd_set_t�����������
*    aux:
*    pbuffer: �������������/�������, ��ͬ���������벻ͬ��
*             һ����˵������ǽṹ����Ҫ����ָ�룬ö��ֱֵ�Ӵ������ֵ
*    ret = EPDK_OK/EPDK_FAIL
*******************************************************************************/
typedef enum __VIDEO_PLAY_CMD_SET
{
    VIDEO_PLAY_START      ,             //����cvbs��ʾ
    VIDEO_PLAY_STOP      ,              //ֹͣcvbs��ʾ
 	VIDEO_PLAY_SET_ROTATE_ANGLE      , 	//������Ƶ��ת�Ƕ� aux = dir: __video_play_rotate_t Ĭ�ϲ���ת
 	VIDEO_PLAY_GET_ROTATE_ANGLE,		//��ȡ��ǰ��Ƶ��ת�Ƕ� return = dir
 	VIDEO_PLAY_SET_CHANNEL,				//����cvbs����ͨ�� aux= channel select��Ĭ�� channel 0
 	VIDEO_PLAY_GET_CHANNEL,				//��ȡ��ǰcvbs����ͨ��
 	VIDEO_PLAY_GET_SYSTEM,				//��ȡ��ʽ return = 0: NTSC      return = 1 PAL
 	VIDEO_PLAY_GET_SIGNALE_DECT,		//��ȡ��ǰcvbs�����ź� return = 1���ź� return = 0���ź�
	VIDEO_PLAY_SET_SCREEN_RECT, 		//������ʾ����			pbuffer:  __disp_rect_t Ĭ��ȫ����ʾ
 	VIDEO_PLAY_GET_SCREEN_RECT,			//��ȡ��ǰ��ʾ����			return __disp_rect_t*
  	VIDEO_PLAY_SET_SOURCE_RECT,  		//����������Ƶ�������ü��� pbuffer: __disp_rect_t,Ĭ�ϲ��ü�
	VIDEO_PLAY_GET_SOURCE_RECT, 		//��ȡ��ǰ������Ƶ����			   return  __disp_rect_t*
  	VIDEO_PLAY_SET_CONTRAST,            //���öԱȶ� aux = contrast: 0 <= aux <= 255 Ĭ��128
	VIDEO_PLAY_GET_CONTRAST,			//��ȡ�Աȶ� return = contrast
  	VIDEO_PLAY_SET_BRIGHTNESS,				//�������� aux =     bright 0 <= aux <= 255 Ĭ��32
	VIDEO_PLAY_GET_BRIGHTNESS,				//��ȡ���� return =	 bright
  	VIDEO_PLAY_SET_SATURATION,			//���ñ��Ͷ� aux = saturation       0 <= aux <= 255 Ĭ��128
	VIDEO_PLAY_GET_SATURATION,			//��ȡ���Ͷ� return = saturation
	VIDEO_PLAY_SET_SHARPNESS,           //�������
	VIDEO_PLAY_GET_SHARPNESS,           //��ȡ���
	VIDEO_PLAY_SET_HUE,                 //����ɫ��  0 <= aux <= 255
	VIDEO_PLAY_GET_HUE,                 //��ȡɫ��
   	VIDEO_PLAY_CMD_UNKNOWN                     = 0xFFFF,
} __video_play_cmd_set_t;


typedef enum
{
	VIDEO_PLAY_ROTATE_0         = 0x0,//rotate clockwise 0 ROTgree
	VIDEO_PLAY_ROTATE_90        = 0x1,//rotate clockwise 90 ROTgree
	VIDEO_PLAY_ROTATE_180       = 0x2,//rotate clockwise 180 ROTgree
	VIDEO_PLAY_ROTATE_270       = 0x3,//rotate clockwise 270 ROTgree
	VIDEO_PLAY_ROTATE_HFLIP     = 0x4,//horizontal flip
	VIDEO_PLAY_HFLIP_ROT_90 	= 0x5,//first rotate clockwise 90 ROTgree then horizontal flip
	VIDEO_PLAY_ROTATE_VFLIP     = 0x6,//vertical flip
	VIDEO_PLAY_VFLIP_ROT_90 	= 0x7,//first rotate clockwise 90 ROTgree then vertical flip
} __video_play_rotate_t;

#endif


