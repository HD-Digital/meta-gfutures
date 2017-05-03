PREFERRED_VERSION_linux-hd = "4.10.12"

IMAGE_FSTYPES += "ubi"
UBI_VOLNAME = "rootfs"

TARGET_ARCH = "mipsel"
DEFAULTTUNE ?= "mips32el"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/hd.inc
