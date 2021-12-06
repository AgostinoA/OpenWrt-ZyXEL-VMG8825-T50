#!/usr/bin/python
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

cdir = os.path.dirname("")
cdir = os.path.abspath(cdir)
outputdir = ""

def process_bootconfig(config_file):
	global mbn_gen
	global outputdir
	global cdir

        tree = ET.parse(config_file)
        root = tree.getroot()

	arch = root.find(".//data[@type='ARCH']/SOC")
	ARCH_NAME = str(arch.text)

	nand_param = root.find(".//data[@type='NAND_PARAMETER']")
	nand_pagesize = int(nand_param.find('page_size').text)
	nand_pages_per_block = int(nand_param.find('pages_per_block').text)

	bootconfig = "$$/" + ARCH_NAME + "/bootconfig/bootconfig.xml"
	bootconfig = bootconfig.replace('$$', cdir)

	mbn_gen = '$$/scripts/nand_mbn_generator.py'
        mbn_gen = mbn_gen.replace('$$', cdir)

	print '\tNand page size: ' + str(nand_pagesize) + ', pages/block: ' \
		+ str(nand_pages_per_block)
	print '\tBootconfig info: ' + bootconfig

# Create user partition
	nand_raw_bootconfig='nand_raw_bootconfig.bin'
	nand_raw_bootconfig = os.path.splitext(nand_raw_bootconfig)[0] + ".bin"

	print '\tCreating raw partition'
	prc = subprocess.Popen(['python', mbn_gen, bootconfig,
				nand_raw_bootconfig], cwd=outputdir)
	prc.wait()
	if prc.returncode != 0:
		print 'ERROR: unable to create raw partition'
		return prc.returncode
	else:
		print '...Raw partition created'

	bootconfig_gen = outputdir + '/bootconfig_tool'
	os.chmod(bootconfig_gen, 0744)
	rawpart_path = os.path.join(outputdir, nand_raw_bootconfig)
	nand_bootconfig = outputdir + '/bootconfig.bin'

# Create nand bootconfig
	print '\tCreating Nand bootconfig',
	prc = subprocess.Popen([
			bootconfig_gen,
			'-s',
			str(nand_pagesize),
			'-p',
			str(nand_pages_per_block),
			'-i',
			rawpart_path,
			'-o',
			nand_bootconfig,
			], cwd=outputdir)
	prc.wait()
	if prc.returncode != 0:
		print 'ERROR: unable to create system partition'
		return prc.returncode
	else:
		print '...Bootconfig created\n\n'

	return 0

def main():
	global bootconfig_gen
	global outputdir
	if len(sys.argv) > 1:
		try:
			opts, args = getopt(sys.argv[1:], "c:o:")
		except GetoptError, e:
			print "config file and bootconfig type are needed to generate bootconfig binaries"
			raise
		for option, value in opts:
			if option == "-c":
				config_file = value
			elif option == "-o":
				outputdir = value
	else:
		print "Error: config file and output path are needed to generate bootconfig binaries\n"
		return -1

	if process_bootconfig(config_file) < 0:
			return -1


if __name__ == '__main__':
    main()
