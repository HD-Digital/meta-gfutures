KV = "4.4.35"
SRCDATE = "20190319"

PROVIDES = "virtual/blindscan-dvbs"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "05362cd64a869fa0a57c9d5605de4615"
SRC_URI[sha256sum] = "090085f31895e7e7cccd8d50d692040f33455f56fa844521a64689d864e00d5b"

COMPATIBLE_MACHINE = "hd60"

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
