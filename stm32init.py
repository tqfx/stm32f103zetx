#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
import glob
import subprocess

# Source configuration directory
vsc = "stm32init"

# Default STM32 MCU
default_mcu = "STM32MCU"
# Default .elf filename
default_elfname = "ELFNAME"
# Default .cfg filename
default_config = "openocd.cfg"
# Default user' Makefile
default_mk = "make.mk"
# Target configuration directory
dst = ".vscode"


def findtool(tool):
    if "win" in sys.platform:
        find = "where"
    elif "linux" in sys.platform:
        find = "which"
    else:
        raise SystemError
    subp = subprocess.Popen(
        [find, tool], stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="UTF-8"
    )
    subp.wait()
    return subp.stdout.read().split()


def dealdir(dirname):
    '''
    Add delimiter

    Args:
        dirname: The path to process
    Returns:
        The path after being processed
    '''

    if "/" != dirname[-1] and "\\" != dirname[-1]:
        dirname += "/"
    return dirname


# Get the current path
cwd = os.getcwd().replace("\\", "/")
# Get the path to the execution file
pwd = os.path.split(os.path.relpath(sys.argv[0]))[0].replace("\\", "/")

# Add delimiter
pwd = dealdir(pwd)
cwd = dealdir(cwd)
vsc = dealdir(vsc)
dst = dealdir(dst)

config = default_config
# Get the configuration file for the directory where the execution file resides
for path in (cwd, pwd + "../", pwd):
    cfgs = glob.glob(r"{}*.cfg".format(path))
    if [] != cfgs:
        config = os.path.relpath(cfgs[0]).replace("\\", "/")
        break
    del cfgs
    if path == pwd:
        print("unfound", "*.cfg")

elfname = ''
# Get project name
iocs = glob.glob(r"{}*.ioc".format(cwd))
if [] != iocs:
    f = open(iocs[0], "r", encoding="UTF-8")
    texts = f.read().split("\n")
    f.close()
    for text in texts:
        if "ProjectName" in text:
            elfname = text.split("=")[-1]
            break
    del texts
else:
    print("unfound", "*.ioc")
del iocs


def launch(filename="launch.json"):
    '''
    Set launch.json
    '''

    with open(pwd + vsc + filename, "r", encoding="UTF-8") as f:
        text = f.read()

    # Set .elf name
    text = text.replace(default_elfname, elfname)
    # Set .cfg name
    text = text.replace(default_config, config)

    with open(cwd + dst + filename, "wb") as f:
        f.write(text.encode("UTF-8"))

    return


def tasks(filename="tasks.json"):
    '''
    Set tasks.json
    '''

    with open(pwd + vsc + filename, "r", encoding="UTF-8") as f:
        text = f.read()

    with open(cwd + dst + filename, "wb") as f:
        f.write(text.encode("UTF-8"))

    return


def c_cpp_properties(filename="c_cpp_properties.json"):
    '''
    Set c_cpp_properties.json
    '''

    with open(pwd + vsc + filename, "r", encoding="UTF-8") as f:
        text = f.read()

    tools = findtool("arm-none-eabi-gcc")
    if [] != tools:
        tool = tools[0].replace("\\", "/")
        text = text.replace("arm-none-eabi-gcc", tool)
        print("tool:", tool)
    else:
        print("unfound", "arm-none-eabi-gcc")

    # Set STM32 MCU macro
    try:
        asms = glob.glob(r"{}startup*.s".format(cwd))
        asm = os.path.split(asms[0])[-1]
        print("start:", asm)
        mcu = os.path.splitext(asm)[0].split("_")[-1]
        mcu = mcu.upper().replace("X", "x")
        text = text.replace(default_mcu, mcu)
    except IndexError:
        print("unfound", "startup*.s")
        exit()

    with open(cwd + dst + filename, "wb") as f:
        f.write(text.encode("UTF-8"))

    return


def makefile(filename="Makefile"):
    '''
    Set Makefile
    '''

    flags = (
        "-Wextra",
        "-Wpedantic",
        "-Wundef",
        "-Wunused",
        "-Wshadow",
        "-Winline",
        "-Wpacked",
        "-Wpadded",
        "-Wcast-qual",
        "-Wcast-align",
        "-Wattributes",
        "-Wconversion",
        "-Wfloat-equal",
        "-Wswitch-enum",
        "-Wswitch-default",
        "-Wdouble-promotion",
    )

    openocd = "\topenocd -f " + config + " -c init -c halt -c "
    cmd = (
        "flash:\n"
        + openocd
        + '"program $(BUILD_DIR)/$(TARGET).elf verify reset exit"\n'
    )
    cmd += "reset:\n" + openocd + "reset -c shutdown\n"

    if default_mk not in os.listdir():
        text_mk = '# compile gcc flags\n'
        for flag in flags:
            text_mk += "CFLAGS += {}\n".format(flag)
        text_mk += "# C defines\nC_DEFS +=\n"
        text_mk += "# C includes\nC_INCLUDES +=\n"
        text_mk += "# C sources\nC_SOURCES += $(wildcard *.c)\n"
        text_mk += "# AS defines\nAS_DEFS +=\n"
        text_mk += "# ASM sources\nASM_SOURCES +=\n"
        text_mk += "# link flags\nLDFLAGS += -u_printf_float\n"
        with open(default_mk, "wb") as f:
            f.write(text_mk.encode("UTF-8"))

    with open(filename, "r", encoding="UTF-8") as f:
        text = f.read()

    # Set inlcude user' Makefile
    if default_mk not in text:
        text_inc = "-include {}\n".format(default_mk)
        text_src = "# default "
        text = text.replace(text_src, "{}\n{}".format(text_inc, text_src))
        del text_src

    # Deal with the end
    end = "EOF"
    texts = text.split(end)
    text = texts[0] + end
    if " ***" in texts[-1]:
        text += " ***"
    text += "\n" + cmd

    with open(filename, "wb") as f:
        f.write(text.encode("UTF-8"))

    return


def vscinit():
    '''
    initialze .vscode
    '''

    if not os.path.exists(dst):
        os.mkdir(dst)

    return


if "__main__" == __name__:
    vscinit()
    c_cpp_properties()
    launch()
    tasks()
    makefile()
    # Show log
    print("config:", config)
