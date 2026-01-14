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
 * @file      driver_afs01.c
 * @brief     driver afs01 source file
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

#include "driver_afs01.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "ASAIR AFS01"        /**< chip name */
#define MANUFACTURER_NAME         "ASAIR"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        4.75f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.25f                /**< chip max supply voltage */
#define MAX_CURRENT               10.0f                /**< chip max current */
#define TEMPERATURE_MIN           25.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           50.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief chip address definition
 */
#define AFS01_ADDRESS        0x80        /**< iic device address */

/**
 * @brief chip command definition
 */
#define AFS01_COMMAND_READ_DATA        0x1000U        /**< read data command */
#define AFS01_COMMAND_READ_ID          0x31AEU        /**< read id command */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to an afs01 handle structure
 * @param[in]  reg register
 * @param[out] *data pointer to a data buffer
 * @param[in]  len length of data
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_afs01_read(afs01_handle_t *handle, uint16_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_address16(AFS01_ADDRESS, reg, data, len) != 0)        /* read the register */
    {
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     calculate the crc
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    crc
 * @note      none
 */
static uint8_t a_afs01_crc(uint8_t *data, uint16_t len)
{
    const uint8_t POLYNOMIAL = 0x31;
    uint8_t crc = 0x00;
    uint16_t i, j;
  
    for (j = len; j != 0; --j)                                              /* length-- */
    {
        crc ^= *data++;                                                     /* xor */
        for (i = 8; i != 0; --i)                                            /* 8 times */
        {
            crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);      /* calculate crc */
        }
    }
  
    return crc;                                                             /* return crc */
}

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
uint8_t afs01_init(afs01_handle_t *handle)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->debug_print == NULL)                                         /* check debug_print */
    {
        return 3;                                                            /* return error */
    }
    if (handle->iic_init == NULL)                                            /* check iic_init */
    {
        handle->debug_print("afs01: iic_init is null.\n");                   /* iic_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_deinit == NULL)                                          /* check iic_deinit */
    {
        handle->debug_print("afs01: iic_deinit is null.\n");                 /* iic_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_read_address16 == NULL)                                  /* check iic_read_address16 */
    {
        handle->debug_print("afs01: iic_read_address16 is null.\n");         /* iic_read_address16 is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->delay_ms == NULL)                                            /* check delay_ms */
    {
        handle->debug_print("afs01: delay_ms is null.\n");                   /* delay_ms is null */
       
        return 3;                                                            /* return error */
    }

    if (handle->iic_init() != 0)                                             /* iic init */
    {
        handle->debug_print("afs01: iic init failed.\n");                    /* iic init failed */
       
        return 1;                                                            /* return error */
    }
    handle->inited = 1;                                                      /* flag finish initialization */

    return 0;                                                                /* success return 0 */
}

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
uint8_t afs01_deinit(afs01_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                 /* iic deinit */
    {
        handle->debug_print("afs01: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                  /* return error */
    }   
    handle->inited = 0;                                            /* flag close */
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t afs01_read(afs01_handle_t *handle, uint16_t *raw, float *sccm)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_afs01_read(handle, AFS01_COMMAND_READ_DATA, buf, 3);        /* read data */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("afs01: read failed.\n");                   /* read failed */
       
        return 1;                                                       /* return error */
    }
    if (a_afs01_crc(buf, 2) != buf[2])                                  /* check crc */
    {
        handle->debug_print("afs01: crc error.\n");                     /* crc error */
       
        return 4;                                                       /* return error */
    }
    *raw = (uint16_t)(((uint16_t)buf[0]) << 8) | buf[1];                /* set raw data */
    *sccm = ((float)(*raw) - 32000.0f) / 140.0f;                        /* set sccm */
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t afs01_get_chip_id(afs01_handle_t *handle, uint8_t id[4])
{
    uint8_t res;
    uint8_t buf[6];
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_afs01_read(handle, AFS01_COMMAND_READ_ID, buf, 6);          /* read id */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("afs01: read id failed.\n");                /* read id failed */
       
        return 1;                                                       /* return error */
    }
    if (a_afs01_crc(buf, 2) != buf[2])                                  /* check crc */
    {
        handle->debug_print("afs01: crc error.\n");                     /* crc error */
       
        return 4;                                                       /* return error */
    }
    if (a_afs01_crc(buf + 3, 2) != buf[5])                              /* check crc */
    {
        handle->debug_print("afs01: crc error.\n");                     /* crc error */
       
        return 4;                                                       /* return error */
    }
    id[0] = buf[0];                                                     /* set id part 0 */
    id[1] = buf[1];                                                     /* set id part 1 */
    id[2] = buf[3];                                                     /* set id part 2 */
    id[3] = buf[4];                                                     /* set id part 3 */
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t si7021_get_reg(afs01_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    } 
    
    if (a_afs01_read(handle, reg, buf, len) != 0)        /* read data */
    {
        return 1;                                        /* return error */
    }
    
    return 0;                                            /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an afs01 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t afs01_info(afs01_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(afs01_info_t));                          /* initialize afs01 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
