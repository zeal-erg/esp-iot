# esp-iot

iot code base on esp32 platfrom

# Contents

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





