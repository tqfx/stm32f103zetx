# 环境搭建

## 安装

- [Visual Studio Code](https://code.visualstudio.com/Download)

- [Java](https://www.oracle.com/java/technologies/javase-downloads.html)

- [STM32CubeMX](https://www.st.com/zh/development-tools/stm32cubemx.html)

- [ST-Link-V2](https://www.st.com/zh/development-tools/st-link-v2.html#tools-software)

- [Make](http://gnuwin32.sourceforge.net/packages/make.htm)

- [OpenOCD](http://openocd.org/)

- [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

  推荐使用 [msys2](https://msys2.org) 安装工具链

    ```bash
    pacman -S mingw-w64-x86_64-openocd
    pacman -S mingw-w64-x86_64-make
    pacman -S mingw-w64-x86_64-arm-none-eabi-toolchain
    ```

> 不要忘记将工具链加入系统环境变量
