DESCRIPTION = "Hello World Kernel Module"
SECTION = "kernel"
LICENSE = "GPL-2.0"
LIC_FILES_CHKSUM = "file://mymodule.c;md5=dbc82da4ced6ce6850fdd31ec8e7e9b2"

SRC_URI = "file://mymodule.c \
           file://Makefile"

S = "${WORKDIR}"

inherit module
KERNEL_MODULE_AUTOLOAD += "mymodule"

