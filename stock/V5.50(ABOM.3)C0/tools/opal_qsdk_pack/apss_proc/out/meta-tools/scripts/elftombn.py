# ==========================================================================
# Copyright (c) 2017 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ==========================================================================

from optparse import OptionParser
import os
import mbn_tools

##############################################################################
# main
##############################################################################
def main():
	parser = OptionParser(usage='usage: %prog [options] arguments')

	parser.add_option("-f", "--first_filepath",
			action="store", type="string", dest="elf_inp_file1",
			help="First ELF file to merge.")

	parser.add_option("-o", "--output_filepath",
			action="store", type="string", dest="binary_out",
			help="Merged filename and path.")

	(options, args) = parser.parse_args()
	if not options.elf_inp_file1:
		parser.error('First ELF filename not given')

	if not options.binary_out:
		parser.error('Output filename not given')

	gen_dict = {}

	elf_inp_file1 = options.elf_inp_file1

	binary_out = options.binary_out

	mbn_type = 'elf'
	header_format = 'reg'
	gen_dict['IMAGE_KEY_IMAGE_ID'] = mbn_tools.ImageType.SBL1_IMG
	gen_dict['IMAGE_KEY_MBN_TYPE'] = mbn_type
	image_header_secflag = 'non_secure'

	source_base = os.path.splitext(str(binary_out))[0]
	target_base = os.path.splitext(str(binary_out))[0]
	source_elf = source_base + "_nohash.elf"
	target_hash = target_base + ".hash"
	target_hash_hd = target_base + "_hash.hd"
	target_phdr_elf = target_base + "_phdr.pbn"
	target_nonsec = target_base + "_combined_hash.mbn"

	# Create hash table
	rv = mbn_tools.pboot_gen_elf([],
			elf_inp_file1,
			target_hash,
			elf_out_file_name = target_phdr_elf,
			secure_type = image_header_secflag)
	if rv:
		raise RuntimeError, "Failed to run pboot_gen_elf"

	# Create hash table header
	rv = mbn_tools.image_header([],
			gen_dict,
			target_hash,
			target_hash_hd,
			image_header_secflag,
			elf_file_name = target_phdr_elf)
	if rv:
		raise RuntimeError, "Failed to create image header for hash segment"

	files_to_cat_in_order = [target_hash_hd, target_hash]
	mbn_tools.concat_files (target_nonsec, files_to_cat_in_order)

	# Add the hash segment into the ELF
	mbn_tools.pboot_add_hash([],
			target_phdr_elf,
			target_nonsec, binary_out)

	return

main()
