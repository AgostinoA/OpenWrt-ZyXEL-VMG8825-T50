# ===========================================================================
#Copyright (c) 2017 Qualcomm Technologies, Inc.
#All Rights Reserved.
#Confidential and Proprietary - Qualcomm Technologies, Inc.
# ===========================================================================

import xml.etree.ElementTree as ET
import itertools
import os
import subprocess
import sys
from getopt import getopt
from getopt import GetoptError

arch=""
flash="nor,nand,norplusnand,emmc,norplusemmc"
bootImgDir=""
rpmImgDir=""
tzImgDir=""
nhssImgDir=""
wififwImgDir=""

cdir = os.path.dirname(__file__)
cdir = os.path.abspath(cdir)
inDir = ""
mode = ""

def print_help():
	print "\nUsage: python prepareSingleImage.py <option> <value>\n"

	print "--arch \t\tArch(e.g ipq40xx/ipq807x/ipq807x_64)\n"
	print " \t\te.g python prepareSingleImage.py --arch ipq807x\n\n"

	print "--fltype \tFlash Type (nor/nand/emmc/norplusnand/norplusemmc)"
	print " \t\tMultiple flashtypes can be passed by a comma separated string"
	print " \t\tDefault is all. i.e If \"--fltype\" is not passed image for all the flash-type will be created.\n"
	print " \t\te.g python prepareSingleImage.py --fltype nor,nand,norplusnand\n\n"

	print "--in \t\tGenerated binaries and images needed for singleimage will be copied to this location"
	print "\t\tDefault path: ./<ARCH>/in/\n"
	print "\t\te.g python prepareSingleImage.py --gencdt --in ./\n\n"

	print "--bootimg \tBoot image path"
	print "\t\tIf specified the boot images available at <PATH> will be copied to the directory provided with \"--in\"\n"
	print "\t\te.g python prepareSingleImage.py --bootimg <PATH>\n\n"

	print "--tzimg \tTZ image path"
	print "\t\tIf specified the TZ images available at <PATH> will be copied to the directory provided with \"--in\"\n"
	print "\t\te.g python prepareSingleImage.py --tzimg <PATH>\n\n"

	print "--nhssimg \tNHSS image path"
	print "\t\tIf specified the NHSS images available at <PATH> will be copied to the directory provided with \"--in\"\n"
	print "\t\te.g python prepareSingleImage.py --nhssimg <PATH>\n\n"

	print "--rpmimg \tRPM image path"
	print "\t\tIf specified the RPM images available at <PATH> will be copied to the directory provided with \"--in\"\n"
	print "\t\te.g python prepareSingleImage.py --rpmimg <PATH>\n\n"

	print "--gencdt \tWhether CDT binaries to be generated"
	print "\t\tIf not specified CDT binary will not be generated"
	print "\t\tThis Argument does not take any value\n"
	print "\t\te.g python prepareSingleImage.py --gencdt\n\n"

	print "--genpart \tWhether flash partition table(s) to be generated"
	print "\t\tIf not specified partition table(s) will not be generated"
	print "\t\tThis Argument does not take any value\n"
	print "\t\te.g python prepareSingleImage.py --genpart\n\n"

	print "--genbootconf \tWhether bootconfig binaries to be generated"
	print "\t\tIf not specified bootconfig binaries will not be generated"
	print "\t\tThis Argument does not take any value\n"
	print "\t\te.g python prepareSingleImage.py --genbootconf\n\n"

	print "--genmbn \tWhether u-boot.elf to be converted to u-boot.mbn"
	print "\t\tIf not specified u-boot.mbn will not be generated"
	print "\t\tThis is currently used/needed only for IPQ807x"
	print "\t\tThis Argument does not take any value\n"
	print "\t\te.g python prepareSingleImage.py --genmbn\n\n"

	print "--help \t\tPrint This Message\n\n"

	print "\t\t\t\t <<<<<<<<<<<<< A Sample Run >>>>>>>>>>>>>\n"
	print "python prepareSingleImage.py --arch ipq40xx --fltype nor,nand,norplusnand --gencdt --genbootconf --genpart --in ./in_put/\n\n\n"


def copy_images(image_type, build_dir):
	global arch
	global configDir

	tree = ET.parse(configDir)
	root = tree.getroot()

	entries = root.findall("./data[@type='COPY_IMAGES']/image[@type='" + image_type + "']/entry")
	for entry in entries:
		image_path = entry.find(".//image_path")
		image_path.text = build_dir.rstrip() + image_path.text
		print "image_path.text:" + image_path.text
		print "cp " + image_path.text  + " " + inDir
		os.system("cp " + image_path.text  + " " + inDir)

def gen_cdt():
	global srcDir
	global configDir

	cdt_path = srcDir + '/gen_cdt_bin.py'
	prc = subprocess.Popen(['python', cdt_path, '-c', configDir, '-o', inDir], cwd=cdir)
	prc.wait()

	if prc.returncode != 0:
		print 'ERROR: unable to create CDT binary'
		return prc.returncode
	return 0

def gen_part(flash):
	global srcDir
	global configDir

	flash_partition_path = srcDir + '/gen_flash_partition_bin.py'
	for flash_type in flash.split(","):
		prc = subprocess.Popen(['python', flash_partition_path, '-c', configDir, '-f', flash_type, '-o', inDir], cwd=cdir)
		prc.wait()

		if prc.returncode != 0:
			print 'ERROR: unable to generate partition table for ' + flash_type
			return prc.returncode
	return 0

def gen_bootconfig():
	global srcDir
	global configDir

	bootconfig_path = srcDir + '/gen_bootconfig_bin.py'
	print "Creating Bootconfig"
	prc = subprocess.Popen(['python', bootconfig_path, '-c', configDir, '-o', inDir], cwd=cdir)
	prc.wait()

	if prc.returncode != 0:
		print 'ERROR: unable to create bootconfig binary'
		return prc.returncode
	return 0

def gen_mbn():
	global srcDir

	bootconfig_path = srcDir + '/elftombn.py'
	print "Converting u-boot elf to mbn ..."
	prc = subprocess.Popen(['python', bootconfig_path, '-f', inDir + "/openwrt-ipq807x-u-boot.elf", '-o', inDir + "/openwrt-ipq807x-u-boot.mbn"], cwd=cdir)
	prc.wait()

	if prc.returncode != 0:
		print 'ERROR: unable to convert U-Boot .elf to .mbn'
		return prc.returncode
	else:
		print "U-Boot .mbn file is created"
		return 0

def main():
	global flash
	global arch
	global bootImgDir
	global tzImgDir
	global nhssImgDir
	global rpmImgDir
	global wififwImgDir
	global srcDir
	global configDir
	global inDir
	global mode

	to_generate_cdt = "false"
	to_generate_part = "false"
	to_generate_bootconf = "false"
	to_generate_mbn = "false"

	if len(sys.argv) > 1:
		try:
			opts, args = getopt(sys.argv[1:], "h", ["arch=", "fltype=", "in=", "bootimg=", "tzimg=", "nhssimg=", "rpmimg=", "wififwimg", "gencdt", "genpart", "genbootconf", "genmbn", "help"])
		except GetoptError, e:
			print_help()
			raise

		for option, value in opts:
			if option == "--arch":
				arch = value
				if arch not in ["ipq40xx", "ipq806x", "ipq807x", "ipq807x_64"]:
					print "Invalid arch type: " + arch
					print_help()
					return -1
				if arch == "ipq807x":
					mode = "32"
				elif arch == "ipq807x_64":
					mode = "64"
					arch = "ipq807x"

			elif option == "--fltype":
				flash = value
				for flash_type in flash.split(","):
					if flash_type not in ["nor", "nand", "norplusnand", "emmc", "norplusemmc"]:
						print "Invalid flash type: " + flash_type
						print_help()
						return -1
			elif option == "--in":
				inDir = value
			elif option == "--bootimg":
				bootImgDir = value
			elif option == "--tzimg":
				tzImgDir = value
			elif option == "--nhssimg":
				nhssImgDir = value
			elif option == "--rpmimg":
				rpmImgDir = value
			elif option == "--wififwimg":
				wififwImgDir = value
			elif option == "--gencdt":
				to_generate_cdt = "true"
			elif option == "--genbootconf":
				to_generate_bootconf = "true"
			elif option == "--genpart":
				to_generate_part = "true"
			elif option == "--genmbn":
				to_generate_mbn = "true"

			elif (option == "-h" or option == "--help"):
				print_help()
				return 0

		srcDir="$$/scripts"
		srcDir = srcDir.replace('$$', cdir)
		configDir="$$/" + arch + "/config.xml"
		configDir = configDir.replace('$$', cdir)

		if inDir == "":
			inDir="$$/" + arch + "/in"
			inDir = inDir.replace('$$', cdir)

		inDir = os.path.abspath(inDir + "/")

		if not os.path.exists(inDir):
			os.makedirs(inDir)

		if bootImgDir != "":
			copy_images("BOOT", bootImgDir)
		if tzImgDir != "":
			copy_images("TZ", tzImgDir)
		if nhssImgDir != "":
			copy_images("NHSS" + mode, nhssImgDir)
		if rpmImgDir != "":
			copy_images("RPM", rpmImgDir)
		if wififwImgDir != "":
			copy_images("WIFIFW", wififwImgDir)

		if to_generate_cdt == "true":
			if gen_cdt() != 0:
				return -1

		if to_generate_bootconf == "true":
			if gen_bootconfig() != 0:
				return -1

		if to_generate_part == "true":
			if gen_part(flash) != 0:
				return -1

		if to_generate_mbn == "true":
			if arch == "ipq807x":
				if gen_mbn() != 0:
					return -1
			else:
				print "Invalid arch \"" + arch + "\" for mbn conversion"
				print "--genmbn is needed/used only for ipq807x or ipq807x_64 type"


		return 0
	else:
		print_help()
		return 0

if __name__ == '__main__':
	main()


