DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"

KERNEL_RELEASE = "4.10.0"
COMPATIBLE_MACHINE = "hd+|vs+"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".0"

SRC_URI[mips.md5sum] = "1bca7dc4f68196efe7cf8af085841851"
SRC_URI[mips.sha256sum] = "0b53d7cf932da13e4dc81856c4041e409b4c44fbc533ab5c99dcf22ff2b79a63"
SRC_URI[arm.md5sum] = "3826019f1a8d60b12937e27192501af2"
SRC_URI[arm.sha256sum] = "bf4d8196d185d1b4973f5c9053f506e65883869b92d05940fe7091574a8ecdf7"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux-${PV}/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

SRC_URI += "http://downloads.mutant-digital.net/linux-${PV}-${ARCH}.tar.gz;name=${ARCH} \
	file://defconfig \
	"

SRC_URI_append_arm = " \
	file://findkerneldevice.py \
	file://reserve_dvb_adapter_0.patch \
	file://blacklist_mmc0.patch \
	"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"

# MIPSEL

FILES_kernel-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}*"

KERNEL_IMAGETYPE_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_DIR_mipsel = "."
KERNEL_IMAGEDEST_mipsel = "/tmp"
KERNEL_CONSOLE_mipsel = "null"
SERIAL_CONSOLE_mipsel ?= ""

# Replaced by kernel_output_dir
KERNEL_OUTPUT_mipsel = "vmlinux.gz"

pkg_postinst_kernel-image_mipsel() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			flash_eraseall /dev/mtd1
			nandwrite -p /dev/mtd1 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz
		fi
	fi
	true
}

# ARM

KERNEL_OUTPUT_arm = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"
KERNEL_IMAGETYPE_arm = "zImage"
KERNEL_IMAGEDEST_arm = "tmp"

FILES_kernel-image_arm = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} /${KERNEL_IMAGEDEST}/findkerneldevice.py"

kernel_do_install_append_arm() {
        install -d ${D}/${KERNEL_IMAGEDEST}
        install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/findkerneldevice.py ${D}/${KERNEL_IMAGEDEST}
}

pkg_postinst_kernel-image_arm() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			python /${KERNEL_IMAGEDEST}/findkerneldevice.py
			dd if=/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} of=/dev/kernel
		fi
	fi
    true
}