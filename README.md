[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AFS01

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/afs01/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AFS01 is a gas microflow sensor that boasts high measurement accuracy, excellent repeatability, long-term stability, and complete calibration. Utilizing our company's proprietary flow chip, AFS01 employs the heat transfer principle to measure gas flow. Internally, the sensor incorporates a thermal flow chip and a high-performance integrated 24-bit AD-sampling CMOS microprocessor. This product offers advantages such as high integration and excellent cost-performance ratio.

LibDriver AFS01 is a full-featured driver for AFS01, launched by LibDriver.It provides gas flow reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AFS01 source files.

/interface includes LibDriver AFS01 IIC platform independent template.

/test includes LibDriver AFS01 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AFS01 sample code.

/doc includes LibDriver AFS01 offline document.

/datasheet includes AFS01 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_afs01_basic.h"

uint8_t res;
uint32_t i;

/* basic init */
res = afs01_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* read data */
for (i = 0; i < 3; i++)
{
    float sccm;

    /* delay 1000ms */
    afs01_interface_delay_ms(1000);

    /* read data */
    res = afs01_basic_read(&sccm);
    if (res != 0)
    {
        afs01_interface_debug_print("afs01: read data failed.\n");

        return 1;
    }

    /* output */
    afs01_interface_debug_print("afs01: gas flow is %0.1fsccm.\n", sccm);
    
    ...
}

...
    
/* deinit */
(void)afs01_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/afs01/index.html](https://www.libdriver.com/docs/afs01/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.