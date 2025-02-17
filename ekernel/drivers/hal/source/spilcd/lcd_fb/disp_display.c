/*
 * Allwinner SoCs display driver.
 *
 * Copyright (c) 2007-2017 Allwinnertech Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "disp_display.h"
#include "disp_lcd.h"
#include "dev_lcd_fb.h"

struct disp_dev_t gdisp;

s32 bsp_disp_get_screen_physical_width(u32 disp)
{
	s32 width = 0;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return -1;

	lcd->get_dimensions(lcd, &width, NULL);

	return width;
}

s32 bsp_disp_get_screen_physical_height(u32 disp)
{
	s32 height = 0;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return -1;

	lcd->get_dimensions(lcd, NULL, &height);

	return height;
}

s32 bsp_disp_lcd_set_layer(unsigned int disp, struct fb_info *p_info)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL) {
		lcd_fb_wrn("Get lcd device fail!\n");
		return -1;
	}

	return  lcd->set_layer(lcd, p_info);
}

s32 bsp_disp_lcd_wait_for_vsync(unsigned int disp)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL) {
		lcd_fb_wrn("Get lcd device fail!\n");
		return -1;
	}

	return  lcd->wait_for_vsync(lcd);
}

s32 bsp_disp_lcd_set_var(unsigned int disp, struct fb_info *p_info)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL) {
		lcd_fb_wrn("Get lcd device fail!\n");
		return -1;
	}

	return  lcd->set_var(lcd, p_info);
}

s32 bsp_disp_lcd_blank(unsigned int disp, unsigned int en)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL) {
		lcd_fb_wrn("Get lcd device fail!\n");
		return -1;
	}

	return  lcd->blank(lcd, en);
}

s32 bsp_disp_get_screen_width(u32 disp)
{
	s32 width = 0;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return -1;

	lcd->get_resolution(lcd, &width, NULL);

	return width;
}

s32 bsp_disp_get_screen_height(u32 disp)
{
	s32 height = 0;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return -2;

	lcd->get_resolution(lcd, NULL, &height);

	return height;
}


s32 bsp_disp_lcd_set_panel_funs(char *name, struct disp_lcd_panel_fun *lcd_cfg)
{
	struct lcd_fb_device *lcd;
	u32 num_screens;
	u32 screen_id;
	u32 registered_cnt = 0;

	num_screens = 2;
	for (screen_id = 0; screen_id < num_screens; screen_id++) {
		lcd = disp_get_lcd(screen_id);
		if (lcd && (lcd->set_panel_func)) {
			if (!lcd->set_panel_func(lcd, name, lcd_cfg)) {
				gdisp.lcd_registered[screen_id] = 1;
				registered_cnt++;
				lcd_fb_inf("panel driver %s register\n", name);
			}
		}
	}

	return 0;
}

void LCD_OPEN_FUNC(u32 disp, LCD_FUNC func, u32 delay)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);

	if (lcd && lcd->set_open_func)
		lcd->set_open_func(lcd, func, delay);
}

void LCD_CLOSE_FUNC(u32 disp, LCD_FUNC func, u32 delay)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);

	if (lcd && lcd->set_close_func)
		lcd->set_close_func(lcd, func, delay);
}

s32 bsp_disp_get_lcd_registered(u32 disp)
{
	return gdisp.lcd_registered[disp];
}

s32 bsp_disp_lcd_backlight_enable(u32 disp)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd->backlight_enable)
		ret = lcd->backlight_enable(lcd);

	return ret;
}

s32 bsp_disp_lcd_backlight_disable(u32 disp)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->backlight_disable)
		ret = lcd->backlight_disable(lcd);

	return ret;
}

s32 bsp_disp_lcd_pwm_enable(u32 disp)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->pwm_enable)
		ret = lcd->pwm_enable(lcd);

	return ret;
}

s32 bsp_disp_lcd_pwm_disable(u32 disp)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->pwm_disable)
		ret = lcd->pwm_disable(lcd);

	return ret;
}

s32 bsp_disp_lcd_power_enable(u32 disp, u32 power_id)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->power_enable)
		ret = lcd->power_enable(lcd, power_id);

	return ret;
}

s32 bsp_disp_lcd_power_disable(u32 disp, u32 power_id)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->power_disable)
		ret = lcd->power_disable(lcd, power_id);

	return ret;
}

s32 bsp_disp_lcd_set_bright(u32 disp, u32 bright)
{
	s32 ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd == NULL)
		return ret;

	if (lcd && lcd->set_bright)
		ret = lcd->set_bright(lcd, bright);

	return ret;
}

s32 bsp_disp_lcd_get_bright(u32 disp)
{
	u32 bright = 0;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd && lcd->get_bright)
		bright = lcd->get_bright(lcd);

	return bright;
}


s32 bsp_disp_lcd_pin_cfg(u32 disp, u32 en)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd && lcd->pin_cfg)
		ret = lcd->pin_cfg(lcd, en);

	return ret;
}

s32 bsp_disp_lcd_gpio_set_value(u32 disp, u32 io_index, u32 value)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd && lcd->gpio_set_value)
		ret = lcd->gpio_set_value(lcd, io_index, value);

	return ret;
}

s32 bsp_disp_lcd_gpio_set_direction(u32 disp, unsigned int io_index,
				    u32 direction)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (lcd && lcd->gpio_set_direction)
		ret = lcd->gpio_set_direction(lcd, io_index, direction);

	return ret;
}

s32 bsp_disp_get_panel_info(u32 disp, struct disp_panel_para *info)
{
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(disp);
	if (!lcd)
		lcd_fb_wrn("get lcd%d fail\n", disp);

	if (lcd && lcd->get_panel_info)
		return lcd->get_panel_info(lcd, info);

	return -1;
}

int bsp_disp_get_display_size(u32 disp, unsigned int *width,
			      unsigned int *height)
{
	return 0;
}

static LIST_HEAD(device_list);

s32 lcd_fb_device_register(struct lcd_fb_device *dispdev)
{
	list_add_tail(&dispdev->list, &device_list);
	return 0;
}

s32 lcd_fb_device_unregister(struct lcd_fb_device *dispdev)
{
	list_del(&dispdev->list);
	return 0;
}

struct lcd_fb_device *lcd_fb_device_get(int disp)
{
	struct lcd_fb_device *dispdev = NULL;

	list_for_each_entry(dispdev, &device_list, list) {
		if (dispdev->disp == disp) {
			return dispdev;
		}
	}

	return NULL;
}


void *lcd_fb_dma_malloc(u32 num_bytes)
{
	void *address = NULL;

	if (num_bytes != 0) {
		address = dma_alloc_coherent(num_bytes);
		if (address) {
			lcd_fb_inf(
			    "dma_alloc_coherent ok, address=0x%x, size=0x%x\n",
			    address, num_bytes);
			return address;
		} else {
			lcd_fb_wrn("dma_alloc_coherent fail, size=0x%x\n",
				num_bytes);
			return NULL;
		}
	} else {
		lcd_fb_wrn("%s size is zero\n", __func__);
	}

	return NULL;
}

void lcd_fb_dma_free(void *addr)
{
	if (addr)
		dma_free_coherent(addr);
}


s32 bsp_disp_lcd_cmd_write(unsigned int screen_id,
					 unsigned char cmd)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(screen_id);
	if (lcd && lcd->cmd_write)
		ret = lcd->cmd_write(lcd, cmd);

	return ret;
}

s32 bsp_disp_lcd_para_write(unsigned int screen_id,
					 unsigned char para)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(screen_id);
	if (lcd && lcd->para_write)
		ret = lcd->para_write(lcd, para);

	return ret;
}

s32 bsp_disp_lcd_cmd_read(unsigned int screen_id, unsigned char cmd,
			  unsigned char *rx_buf, unsigned char len)
{
	int ret = -1;
	struct lcd_fb_device *lcd;

	lcd = disp_get_lcd(screen_id);
	if (lcd && lcd->para_write)
		ret = lcd->cmd_read(lcd, cmd, rx_buf, len);

	return ret;
}
