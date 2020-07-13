DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://downloads.mutant-digital.net/${MACHINE}/${MACHINE}-drivers-${KV}-${SRCDATE}.zip"

S = "${WORKDIR}"

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

do_compile() {
}

do_install() {
	install -d ${D}/lib/modules/${KV}/extra
	install -d ${D}/${sysconfdir}/modules-load.d
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
	install -m 0755 ${S}/*.ko ${D}${base_libdir}/modules/${KV}/extra
	for i in ${MACHINE}_1 ${MACHINE}_2 ${MACHINE}_3 ${MACHINE}_4; do
		echo $i >> ${D}/${sysconfdir}/modules-load.d/${MACHINE}.conf
	done
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f /lib/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f /lib/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}

do_package_qa() {
}

FILES_${PN} += "${sysconfdir}/modules-load.d/${MACHINE}.conf ${bindir} ${sysconfdir}/init.d ${base_libdir}/modules/${KV}/extra"

INSANE_SKIP_${PN} += "already-stripped"
INHIBIT_PACKAGE_STRIP = "1"

RREPLACES_${PN} = "kernel-module-${MACHINE}-1-4.4.35 kernel-module-${MACHINE}-2-4.4.35 kernel-module-${MACHINE}-3-4.4.35 kernel-module-${MACHINE}-4-4.4.35 kernel-module-hi-play-4.4.35"
RCONFLICTS_${PN} = "kernel-module-${MACHINE}-1-4.4.35 kernel-module-${MACHINE}-2-4.4.35 kernel-module-${MACHINE}-3-4.4.35 kernel-module-${MACHINE}-4-4.4.35 kernel-module-hi-play-4.4.35"