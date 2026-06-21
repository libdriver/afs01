### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AFS01

#### 3.1 Command Instruction

1. Show afs01 chip and driver information.

   ```shell
   afs01 (-i | --information)
   ```

2. Show afs01 help.

   ```shell
   afs01 (-h | --help)
   ```

3. Show afs01 pin connections of the current board.

   ```shell
   afs01 (-p | --port)
   ```

4. Run afs01 read test, num is the read times.

   ```shell
   afs01 (-t read | --test=read) [--times=<num>]
   ```

5. Run afs01 read function, num is the read times.

   ```shell
   afs01 (-e read | --example=read) [--times=<num>]
   ```

6. Run afs01 read id function.

   ```shell
   afs01 (-e id | --example=id)
   ```

#### 3.2 Command Example

```shell
afs01 -i

afs01: chip is ASAIR AFS01.
afs01: manufacturer is ASAIR.
afs01: interface is IIC.
afs01: driver version is 1.0.
afs01: min supply voltage is 4.8V.
afs01: max supply voltage is 5.2V.
afs01: max current is 10.00mA.
afs01: max temperature is 50.0C.
afs01: min temperature is -10.0C.
```

```shell
afs01 -p

afs01: SCL connected to GPIOB PIN8.
afs01: SDA connected to GPIOB PIN9.
```

```shell
afs01 -t read --times=3

afs01: chip is ASAIR AFS01.
afs01: manufacturer is ASAIR.
afs01: interface is IIC.
afs01: driver version is 1.0.
afs01: min supply voltage is 4.8V.
afs01: max supply voltage is 5.2V.
afs01: max current is 10.00mA.
afs01: max temperature is 50.0C.
afs01: min temperature is 25.0C.
afs01: start read test.
afs01: chip id is 0x03 0x0D 0xB5 0x47.
afs01: gas flow is 159.4sccm.
afs01: gas flow is 117.7sccm.
afs01: gas flow is 159.4sccm.
afs01: finish read test.
```

```shell
afs01 -e read --times=3

afs01: gas flow is 35.4sccm.
afs01: gas flow is 18.9sccm.
afs01: gas flow is 18.9sccm.
```

```shell
afs01 -e id

afs01: chip id is 0x03 0x0D 0xB5 0x47.
```

```shell
afs01 -h

Usage:
  afs01 (-i | --information)
  afs01 (-h | --help)
  afs01 (-p | --port)
  afs01 (-t read | --test=read) [--times=<num>]
  afs01 (-e read | --example=read) [--times=<num>]
  afs01 (-e id | --example=id)

Options:
  -e <read | id>, --example=<read | id>       Run the driver example.
  -h, --help                                    Show the help.
  -i, --information                             Show the chip information.
  -p, --port                                    Display the pin connections of the current board.
  -t <read>, --test=<read>                      Run the driver test.
      --times=<num>                             Set the running times.([default: 3])
```

