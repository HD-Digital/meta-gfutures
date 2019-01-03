KV = "4.4.35"
SRCDATE = "20181221"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "b2bb4d50e2167c7702d3c4d5e9db020e"
SRC_URI[sha256sum] = "3be55c3e632b1f47889adc07ee6a9ff335b88a43b01bc5b3972ae954d3f57f6f"

COMPATIBLE_MACHINE = "hd61"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

/usr/bin/turnoff_power
EOF
}

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"

INSANE_SKIP_${PN} += "already-stripped"
