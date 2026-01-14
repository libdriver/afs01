### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(afs01 REQUIRED)
```

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
./afs01 -i

afs01: chip is ASAIR AFS01.
afs01: manufacturer is ASAIR.
afs01: interface is IIC.
afs01: driver version is 1.0.
afs01: min supply voltage is 4.8V.
afs01: max supply voltage is 5.2V.
afs01: max current is 10.00mA.
afs01: max temperature is 50.0C.
afs01: min temperature is 25.0C.
```

```shell
./afs01 -p

afs01: SCL connected to GPIO3(BCM).
afs01: SDA connected to GPIO2(BCM).
```

```shell
./afs01 -t read --times=3

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
./afs01 -e read --times=3

afs01: gas flow is 35.4sccm.
afs01: gas flow is 18.9sccm.
afs01: gas flow is 18.9sccm.
```

```shell
./afs01 -e id

afs01: chip id is 0x03 0x0D 0xB5 0x47.
```

```shell
./afs01 -h

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

