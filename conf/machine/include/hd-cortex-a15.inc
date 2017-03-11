PREFERRED_VERSION_linux-hd = "4.10.0"

IMAGE_CLASSES += "hd-emmc_image_multi"
IMAGE_FSTYPES += "hd-emmc"
IMAGE_ROOTFS_SIZE ?= "294912"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/hd.inc