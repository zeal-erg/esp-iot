# README for esp-iot project

iot code base on esp32 platfrom

## QUICK START

### 环境配置

1. 安装依赖的python 软件；

   ```shell
   sudo apt-get install git wget flex bison gperf python python-pip python-setuptools cmake ninja-build ccache libffi-dev libssl-dev
   ```

   

2. 设置工具，执行install.sh（如果执行失败，请看如下的问题修复方式:）

   - ```shell
     Traceback (most recent call last):
       File "/home/share/samba/iot/src/esp-iot/esp-idf/tools/idf_tools.py", line 1201, in action_install_python_env
         import virtualenv   # noqa: F401
     ModuleNotFoundError: No module named 'virtualenv'
     ```

   - 先判断pip是否存在 (如果提醒 ModuleNotFoundError: No module named 'pip'，执行sudo apt-get install python3-pip 即可)

   - 再次执行 ./install.sh 

3. 然后执行

   ```shell
   . ./export.sh
   ```

   - 执行如果 提醒**IDF_PATH must be set before sourcing this script**

   ```shell
   export IDF_PATH=$(pwd)/esp-idf
   ```

   - 查看原厂指导手册

   <https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/get-started-legacy/add-idf_path-to-profile.html?highlight=idf_path>

4. 安装所需python特定包 

   ```shell
   python -m pip install --user -r requirements.txt
   ```

5. 更新submodule仓库

   ```shell
    git submodule update --init --recursive
   ```

## Contents

## docs 

相关功能详细介绍文档

## esp-idf

esp32 sdk目录

## iot_frame

扩展第三方支持库

## tools

系列脚本文件

## project

项目文件目录树

```reStructuredText
project
└── iot_esp32
    ├── build_app.sh
    ├── iot_common
    ├── iot_component
    ├── iot_user
    │   └── iot_esp32_sample
    ├── main
    │   └── main
    └── Makefile
```

### iot_esp32

项目名称，基于乐鑫esp32的工程文件目录；

### iot_common

项目共用文件目录；

### iot_component

项目相关组件结构；

### iot_user

具体项目工程地址，可在此处扩展支持自己的测试工程（参考iot_esp32_sample）；

### main

main.c 文件

### build_app.sh

编译脚本（勿动）





