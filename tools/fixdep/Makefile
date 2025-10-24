NAME = fixdep
SRCS = fixdep.c
# 动态获取项目根目录路径
ECOS_HOME := $(shell cd $(dir $(lastword $(MAKEFILE_LIST)))/../.. && pwd)
include $(ECOS_HOME)/src/scripts/build.mk
