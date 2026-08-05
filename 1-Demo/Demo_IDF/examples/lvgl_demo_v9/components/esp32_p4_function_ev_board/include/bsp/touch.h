/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief BSP Touchscreen
 *
 * This file offers API for basic touchscreen initialization.
 * It is useful for users who want to use the touchscreen without the default Graphical Library LVGL.
 *
 * For standard LCD initialization with LVGL graphical library, you can call all-in-one function bsp_display_start().
 */

#pragma once
#include "esp_lcd_touch.h"

/**
 * @brief Whether the selected display has a touch controller.
 *
 * The JC1060P470C 10.1-inch panel is display-only, and HDMI output has no touch
 * either. Without this guard bsp_display_start() would call bsp_touch_new(),
 * fail to find a GT911 and abort on its assert, leaving the board in a boot loop.
 */
#if CONFIG_BSP_LCD_TYPE_HDMI || CONFIG_BSP_LCD_TYPE_800_1280_JD9365
#define BSP_LCD_HAS_TOUCH   (0)
#else
#define BSP_LCD_HAS_TOUCH   (1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup g04_display
 *  @{
 */

/**
 * @brief BSP touch configuration structure
 *
 */
typedef struct {
    void *dummy;    /*!< Prepared for future use. */
} bsp_touch_config_t;

/**
 * @brief Create new touchscreen
 *
 * If you want to free resources allocated by this function, you can use API:
 *
 * \code{.c}
 * bsp_touch_delete();
 * \endcode
 *
 * @param[in]  config    touch configuration
 * @param[out] ret_touch esp_lcd_touch touchscreen handle
 * @return
 *      - ESP_OK         On success
 *      - Else           esp_lcd_touch failure
 */
esp_err_t bsp_touch_new(const bsp_touch_config_t *config, esp_lcd_touch_handle_t *ret_touch);

/**
 * @brief Deinitialize touch
 */
void bsp_touch_delete(void);

/** @} */ // end of display
#ifdef __cplusplus
}
#endif
