# 环境搭建

## 安装

- [Java jre](https://www.oracle.com/java/technologies/javase-downloads.html)
- [STM32CubeMX](https://www.st.com/zh/development-tools/stm32cubemx.html)
- [Visual Studio Code](https://code.visualstudio.com/Download)

  推荐使用 [msys2](https://msys2.org) 安装工具链

    ```bash
    pacman -S mingw-w64-x86_64-make
    pacman -S mingw-w64-x86_64-python
    pacman -S mingw-w64-x86_64-stlink
    pacman -S mingw-w64-x86_64-openocd
    pacman -S mingw-w64-x86_64-arm-none-eabi-toolchain
    ```

- [Make](http://gnuwin32.sourceforge.net/packages/make.htm)
- [Python](https://www.python.org/downloads/)
- [ST-Link-V2](https://www.st.com/zh/development-tools/st-link-v2.html#tools-software)
- [OpenOCD](https://openocd.org/)
- [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

> 不要忘记将工具链加入系统环境变量
