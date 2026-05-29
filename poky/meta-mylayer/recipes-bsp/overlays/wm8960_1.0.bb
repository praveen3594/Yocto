SUMMARY = "WM8960 Overlay"
LICENSE = "CLOSED"

SRC_URI = "file://wm8960-overlay.dts"

do_compile() {
    dtc -@ -I dts -O dtb ${WORKDIR}/wm8960-overlay.dts -o wm8960.dtbo
}

do_install() {
    install -d ${D}/boot/overlays
    install -m 0644 wm8960.dtbo ${D}/boot/overlays/
}

FILES:${PN} += "/boot/overlays/wm8960.dtbo"
