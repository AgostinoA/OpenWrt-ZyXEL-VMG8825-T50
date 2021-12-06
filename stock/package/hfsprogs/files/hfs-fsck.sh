#!/bin/sh
#
# Copyright (c) 2013 Mikhail Gusarov
#
# This is free software, licensed under the GNU General Public License v2+.
#

fsck_hfs() {
  fsck.hfsplus "$device" 2>&1 | logger -t "fstab: fsck_hfs ($device)"
  local status="$?"
  case "$status" in
    0)
      return 0;;
    4)
      reboot;; # Filesystem is fixed, reboot is required
    8)
      echo "fsck_hfs ($device): Unable to fix filesystem!" | logger -t fstab
      return 1;;
    *)
      echo "fsck_hfs ($device): Error $status. Check is not complete." \
        | logger -t fstab
      return 1;;
  esac
}

fsck_hfsplus() {
  fsck_hfs "$@"
}

append libmount_known_fsck "hfs"
append libmount_known_fsck "hfsplus"