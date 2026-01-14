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
 * @file      driver_afs01_read_test.c
 * @brief     driver afs01 read test source file
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
 
#include "driver_afs01_read_test.h"

static afs01_handle_t gs_handle;        /**< afs01 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t afs01_read_test(uint32_t times)
{
    uint8_t res;
    uint8_t id[4];
    uint32_t i;
    afs01_info_t info;
    
    /* link interface function */
    DRIVER_AFS01_LINK_INIT(&gs_handle, afs01_handle_t);
    DRIVER_AFS01_LINK_IIC_INIT(&gs_handle, afs01_interface_iic_init);
    DRIVER_AFS01_LINK_IIC_DEINIT(&gs_handle, afs01_interface_iic_deinit);
    DRIVER_AFS01_LINK_IIC_READ_ADDRESS16(&gs_handle, afs01_interface_iic_read_address16);
    DRIVER_AFS01_LINK_DELAY_MS(&gs_handle, afs01_interface_delay_ms);
    DRIVER_AFS01_LINK_DEBUG_PRINT(&gs_handle, afs01_interface_debug_print);
    
    /* get information */
    res = afs01_info(&info);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        afs01_interface_debug_print("afs01: chip is %s.\n", info.chip_name);
        afs01_interface_debug_print("afs01: manufacturer is %s.\n", info.manufacturer_name);
        afs01_interface_debug_print("afs01: interface is %s.\n", info.interface);
        afs01_interface_debug_print("afs01: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        afs01_interface_debug_print("afs01: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        afs01_interface_debug_print("afs01: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        afs01_interface_debug_print("afs01: max current is %0.2fmA.\n", info.max_current_ma);
        afs01_interface_debug_print("afs01: max temperature is %0.1fC.\n", info.temperature_max);
        afs01_interface_debug_print("afs01: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    afs01_interface_debug_print("afs01: start read test.\n");
    
    /* afs01 init */
    res = afs01_init(&gs_handle);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: init failed.\n");
       
        return 1;
    }
    
    /* get chip id */
    res = afs01_get_chip_id(&gs_handle, id);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: get chip id failed.\n");
        (void)afs01_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    afs01_interface_debug_print("afs01: chip id is 0x%02X 0x%02X 0x%02X 0x%02X.\n", id[0], id[1], id[2], id[3]);
    
    for (i = 0; i < times; i++)
    {
        uint16_t raw;
        float sccm;
        
        /* delay 1000ms */
        afs01_interface_delay_ms(1000);
        
        /* read data */
        res = afs01_read(&gs_handle, &raw, &sccm);
        if (res != 0)
        {
            afs01_interface_debug_print("afs01: read data failed.\n");
            (void)afs01_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        afs01_interface_debug_print("afs01: gas flow is %0.1fsccm.\n", sccm);
    }
    
    /* finish read test */
    afs01_interface_debug_print("afs01: finish read test.\n");
    (void)afs01_deinit(&gs_handle);
    
    return 0;
}
