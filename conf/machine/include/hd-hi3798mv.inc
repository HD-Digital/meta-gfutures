KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-hd = "4.4.35"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-hd"
PREFERRED_PROVIDER_virtual/egl ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libopencl ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "hd-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "hd-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"

# require conf/machine/include/arm/arch-armv8.inc
require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/hd-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Qt
PACKAGECONFIG_GL_pn-qtbase = "no-opengl linuxfb"

# Kodi
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali --enable-player=hiplayer"

MACHINE_EXTRA_RRECOMMENDS = " \
	ffmpeg \
	ntfs-3g \
	"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "hd"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_hdfastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.hdfastboot8gb.gz ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.fastboot.gz; \
	cp ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootoptions.img; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/bootargs-8gb.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/bootargs-8gb.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/logo.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"