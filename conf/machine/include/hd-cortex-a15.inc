PREFERRED_VERSION_linux-hd = "4.10.12"

IMAGE_CLASSES += " hd-emmc_image_multiboot"
IMAGE_FSTYPES += " hdemmc tar"
IMAGE_ROOTFS_SIZE ?= "294912"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/hd.inc

SOC_FAMILY = "bcm7251s"

MTD_KERNEL = "mmcblk0p2"
MTD_ROOTFS = "mmcblk0p3"

MTD_BOOTFS = "mmcblk0p1"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

STB_PLATFORM = "gfuturesbcmarm"
