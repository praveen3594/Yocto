SUMMARY = "Test audio file"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = "file://${WORKDIR}/test.wav;md5=8ee2262bab43ecd6dfa51cc75858179d"

SRC_URI = "file://test.wav"

do_install() {
    install -d ${D}/usr/share/sounds/
    install -m 0644 ${WORKDIR}/test.wav ${D}/usr/share/sounds/test.wav
}

FILES:${PN} += "/usr/share/sounds/test.wav"
