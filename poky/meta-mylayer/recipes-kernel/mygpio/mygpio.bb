DESCRIPTION = "Hello World GPIO Kernel Module"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://mygpio.c;md5=a518a3c58b4fe9aa224292bf53701cc5"

SRC_URI = "file://mygpio.c \
           file://Makefile"

S = "${WORKDIR}"

inherit module

#to include in the kernel build system
# do_install() {
#     install -d ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
#     install -m 0644 mygpio.ko \
#         ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/
# }