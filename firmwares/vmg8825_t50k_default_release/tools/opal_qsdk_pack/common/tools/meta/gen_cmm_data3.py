'''
===============================================================================

 Gen CMM Data

 GENERAL DESCRIPTION
    This script is deprecated in favor if gen_cmm_data1.py and gen_cmm_data2.py.
    It is maintained here for backwards compatibility with older versions of the
    Trace32 scripts.

 Copyright (c) 2012-2012 by QUALCOMM, Incorporated.
 All Rights Reserved.
 QUALCOMM Proprietary/GTDR

===============================================================================

      gen_cmm_data <targ_root> <temp_cmm_script_file_name> <-paths_only> 

   Examples:

      gen_cmm_data3 ..\\..\\.. C:\TEMP\temp_fname.cmm -paths_only
      gen_cmm_data3 ..\\..\\.. C:\ADB\temp_fname.cmm 
      gen_cmm_data3 ..\\..\\.. \\waverider-30\Dropbox\temp_fname.cmm -paths_only
Description:

gen_cmm_data3.py can be called from a CMM script to generate a temporary CMM
script to initialize path information to the component builds.


===============================================================================
'''

import sys
import os
import os.path
import meta_log as lg
import string

#--------------------------------------------------------------------------------#
#creating gen_buildinfo.cmm file in common/tools/cmm directory#
#--------------------------------------------------------------------------------#

def writepathsonly(cmm_script):
    var_values = mi.get_var_values('cmm_var')
    cmm_script.write("GLOBAL &HLOS\n&HLOS=\""+mi.get_product_info('hlos_type')+"\"\n\n" )
    cmm_script.write("GLOBAL &PRODUCT_FLAVORS\n&PRODUCT_FLAVORS=\""+','.join(mi.get_product_flavors())+"\"\n\n" )
    for tag in mi.get_build_list():
   # Don't process the current builds
      if tag != 'common':
        #lg.log("   Processing "+tag)
        print "   Processing "+tag
        path, attrs = mi.get_build_path(tag, get_attrs=True)
        path=string.rstrip(path,os.sep)
        if attrs and 'cmm_root_path_var' in attrs:
           cmm_var_name = attrs['cmm_root_path_var']
           cmm_var_name = cmm_var_name [:string.rfind(cmm_var_name,'_')]+ cmm_var_name [string.rfind(cmm_var_name,'_')+1:]
           if path and cmm_var_name:
              image_dir = mi.get_image_dir(tag)
              if image_dir and os.path.exists(os.path.join(path, image_dir)):
                  if tag == 'apps' :
                     if os.path.exists(os.path.join(path,'LINUX/android')) :
                        path = os.path.join(path,'LINUX/android')
                  cmm_script.write(cmm_tag_template % (cmm_var_name, cmm_var_name, path))

#--------------------------------------------------------------------------------#
#creating gen_buildinfo.cmm file in common/tools/cmm directory#
#--------------------------------------------------------------------------------#
def write_cmm_var(cmm_script):            
   var_values = mi.get_var_values('cmm_var')
#   for var in var_values:
#      cmm_script.write(cmm_tag_template % (var, var, var_values[var]))
   cmm_script.write("ENTRY &ARG0\n\n")
   flavors_list = mi.get_product_flavors()
   if flavors_list:
      default_flavor = flavors_list[0]
   else:
       default_flavor = None
       flavors_list.append("default_flavor")
       
    
   file_vars = mi.get_file_vars(attr='cmm_file_var', abs=False) 
   for var_name in file_vars:
        cmm_script.write("GLOBAL &"+var_name+"\n")
    
   for flavor1 in flavors_list:
        # Look for cmm_file_var attributes:
        cmm_script.write("\nIF (\"&ARG0\"==\""+flavor1+"\")\n(\n")
        file_vars = mi.get_file_vars(attr='cmm_file_var', flavor=flavor1, abs=False)
        for var_name in file_vars:
            file_list = file_vars[var_name]
            for file in file_list:
                if string.find(file,'LINUX')!=-1 and string.find(file,'android')!=-1 :
                    dirs=string.split(file,os.sep)
                    file = string.join(dirs[2:],os.sep)
                cmm_file_array = ''
                cmm_file_array += file + ';'
                cmm_file_array = cmm_file_array[:-1]
                cmm_script.write("\t&"+var_name+"=\""+cmm_file_array+"\"\n")      
        cmm_script.write(")") 
paths_only=0
if len(sys.argv) == 3:
   targ_root = sys.argv[1]
   temp_file = sys.argv[2]
elif len(sys.argv) == 4 and sys.argv[3] == "-paths_only":
   targ_root = sys.argv[1]
   temp_file = sys.argv[2]
   paths_only=1
else:
   print "Error: Invalid number of parameters."
   print __doc__
   sys.exit()

dst_path = os.path.dirname(targ_root)
if (dst_path != '' and    # '' implies current directory, and is allowed
    not os.path.isdir(dst_path)):
   print "Can't find destination directory:", dst_path
   print __doc__
   sys.exit(1)
   
#logfile = os.path.join(dst_path,'gen_cmm_data3')

#lg = lg.Logger(logfile, save_old_log_file=False)

#lg.log("Platform is:" + sys.platform)
#lg.log("Python Version is:" + sys.version)
#lg.log("Current directory is:" + os.getcwd())
#lg.log("Args are:" + str(sys.argv))

print "Platform is:" + sys.platform
print "Python Version is:" + sys.version
print "Current directory is:" + os.getcwd()
print "Args are:" + str(sys.argv)

cmm_script_header = ''
cmm_tag_template = '''GLOBAL &%s
&%s="%s"\n
'''
cmm_script_trailer = '''\nENDDO'''
exception = False
sys.path.append(os.path.dirname(__file__))
import meta_lib as ml

if not targ_root.endswith('/') and not targ_root.endswith('\\'):
   targ_root += '/'
mi = ml.meta_info(logger = lg)

cmm_script = open(temp_file, 'w')

cmm_script.write(cmm_script_header)
#lg.log("Processing meta info")
print "Processing meta info"

if paths_only:
  writepathsonly(cmm_script)  
else:
    write_cmm_var(cmm_script)
    cmm_script.write(cmm_script_trailer)

cmm_script.close()

if os.path.exists(os.path.join(os.path.dirname(temp_file),'EXCEPTION.txt')) and exception == True:
   exception_FILE.close()
else:
   # Create a file TEMP_SUCCESS.txt to indicate the successful completion of TEMP.cmm
   success_txt = os.path.join(os.path.dirname(temp_file),'SUCCESS.txt')
   success_FILE = open(success_txt,'w')
   success_FILE.close()
