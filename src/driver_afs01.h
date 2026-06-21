/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_afs01.h
 * @brief     driver afs01 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-01-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/01/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_AFS01_H
#define DRIVER_AFS01_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup afs01_driver afs01 driver function
 * @brief    afs01 driver modules
 * @{
 */

/**
 * @addtogroup afs01_base_driver
 * @{
 */

/**
 * @brief afs01 handle structure definition
 */
typedef struct afs01_handle_s
{
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint8_t inited;                                                                                /**< inited flag */
} afs01_handle_t;

/**
 * @brief afs01 information structure definition
 */
typedef struct afs01_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} afs01_info_t;

/**
 * @}
 */

/**
 * @defgroup afs01_link_driver afs01 link driver function
 * @brief    afs01 link driver modules
 * @ingroup  afs01_driver
 * @{
 */

/**
 * @brief     initialize afs01_handle_t structure
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] STRUCTURE afs01_handle_t
 * @note      none
 */
#define DRIVER_AFS01_LINK_INIT(HANDLE, STRUCTURE)                  memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_AFS01_LINK_IIC_INIT(HANDLE, FUC)                   (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_AFS01_LINK_IIC_DEINIT(HANDLE, FUC)                 (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] FUC pointer to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_AFS01_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)         (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_AFS01_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an afs01 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_AFS01_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup afs01_base_driver afs01 base driver function
 * @brief    afs01 base driver modules
 * @ingroup  afs01_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an afs01 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t afs01_info(afs01_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an afs01 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t afs01_init(afs01_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an afs01 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t afs01_deinit(afs01_handle_t *handle);

/**
 * @brief      read data
 * @param[in]  *handle pointer to an afs01 handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *sccm pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc error
 * @note       none
 */
uint8_t afs01_read(afs01_handle_t *handle, uint16_t *raw, float *sccm);

/**
 * @brief      get chip id
 * @param[in]  *handle pointer to an afs01 handle structure
 * @param[out] *id pointer to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get chip id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc error
 * @note       none
 */
uint8_t afs01_get_chip_id(afs01_handle_t *handle, uint8_t id[4]);

/**
 * @}
 */

/**
 * @defgroup afs01_extend_driver afs01 extend driver function
 * @brief    afs01 extend driver modules
 * @ingroup  afs01_driver
 * @{
 */

/**
 * @brief      get chip register
 * @param[in]  *handle pointer to an afs01 handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t afs01_get_reg(afs01_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
