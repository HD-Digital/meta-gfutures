KV = "4.4.35"
SRCDATE = "20180907"

PROVIDES = "virtual/blindscan-dvbs"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "f95c2dcec83af0bcfed5b958bd078e8e"
SRC_URI[sha256sum] = "266f7f284d17de375c0e3ffb39708212a57e6d593da1919ba65837cc0a756818"

COMPATIBLE_MACHINE = "hd60"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

if [ "\$1x" == "stopx" ]
then
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