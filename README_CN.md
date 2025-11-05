# ECOS 嵌入式 SDK

## 快速开始

### 1. 环境配置
执行一键安装脚本进行环境配置
```bash
./install.sh
```
脚本运行完成之后，需要重新打开终端或者执行 `source ~/.bashrc` 来更新环境变量。

### 2. 创建示例工程
在你想创建示例工程的目录下执行以下命令：
```bash
ecos init_project <template_name>
```
其中 `<template_name>` 是你想使用的示例工程模板名称，例如 `hello`。
执行完成后，会在当前目录下创建一个以模板名称命名的子目录，包含了示例工程的所有文件。并将开发板默认配置为StarrySkyC1。

### 3. 创建配置文件
在示例工程目录下执行以下命令：
```bash
make menuconfig
```
使用C1开发板时，默认退出配置界面。随即生成编译所需要的配置文件。

### 4. 编译工程
在示例工程目录下执行以下命令：
```bash
make
```
编译完成后，会在build目录下生成`retrosoc_fw.elf`、`retrosoc_fw.hex`、`retrosoc_fw.bin`文件，使用bin文件进行烧录即可。

- 【代码编写】 [maksyuki](https://github.com/maksyuki/maksyuki)
- 【整理维护 & 代码编写】 [XHTimmo](https://github.com/XHTimmo)