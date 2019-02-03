KV = "4.4.35"
SRCDATE = "20190201"

PROVIDES = "virtual/blindscan-dvbs"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "cf1a7e20e733212299fc58293a728b27"
SRC_URI[sha256sum] = "d0edfd90d2372b2a4326673dbe57f50fd6e8b726741fde8c7baf5bb114a4bafa"

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
