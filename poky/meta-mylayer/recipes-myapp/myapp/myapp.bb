DESCRIPTION = "Simple HelloWorld Application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://myapp.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} myapp.c -o myapp
}


do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}

# DESCRIPTION = "My Camera Test App"
# LICENSE = "MIT"
# LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# SRC_URI = "file://camera_test.py"

# S = "${WORKDIR}"

# do_install() {
#     install -d ${D}${bindir}
#     install -m 0755 ${WORKDIR}/camera_test.py ${D}${bindir}/camera_test.py
# }
