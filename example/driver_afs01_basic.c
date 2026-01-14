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
 * @file      driver_afs01_basic.c
 * @brief     driver afs01 basic source file
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

#include "driver_afs01_basic.h"

static afs01_handle_t gs_handle;        /**< afs01 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t afs01_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_AFS01_LINK_INIT(&gs_handle, afs01_handle_t);
    DRIVER_AFS01_LINK_IIC_INIT(&gs_handle, afs01_interface_iic_init);
    DRIVER_AFS01_LINK_IIC_DEINIT(&gs_handle, afs01_interface_iic_deinit);
    DRIVER_AFS01_LINK_IIC_READ_ADDRESS16(&gs_handle, afs01_interface_iic_read_address16);
    DRIVER_AFS01_LINK_DELAY_MS(&gs_handle, afs01_interface_delay_ms);
    DRIVER_AFS01_LINK_DEBUG_PRINT(&gs_handle, afs01_interface_debug_print);
    
    /* afs01 init */
    res = afs01_init(&gs_handle);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *sccm pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 * @note       none
 */
uint8_t afs01_basic_read(float *sccm)
{
    uint8_t res;
    uint16_t raw;
    
    /* read data */
    res = afs01_read(&gs_handle, &raw, sccm);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get chip id
 * @param[out] *id pointer to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get chip id failed
 * @note       none
 */
uint8_t afs01_basic_get_chip_id(uint8_t id[4])
{
    uint8_t res;
    
    /* get chip id */
    res = afs01_get_chip_id(&gs_handle, id);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t afs01_basic_deinit(void)
{
    /* afs01 deinit */
    if (afs01_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
