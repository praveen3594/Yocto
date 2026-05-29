DESCRIPTION = "Hello World GPIO Kernel Module"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://mygpio2.c;md5=0fb04fbe8248be7ab73e65dc02fd503f "

SRC_URI = "file://mygpio2.c \
           file://Makefile"

S = "${WORKDIR}"

inherit module

#to include in the kernel build system
# do_install() {
#     install -d ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
#     install -m 0644 mygpio.ko \
#         ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/
# }