/* exif-loader.h
 *
 * Copyright � 2003 Lutz M�ller <lutz@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __EXIF_LOADER_H__
#define __EXIF_LOADER_H__

#include <libexif/exif-data.h>
#include <libexif/exif-loader.h>
#include <libexif/exif-log.h>
#include <libexif/exif-mem.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _ExifLoader ExifLoader;

ExifLoader *exif_loader_new     (void);
ExifLoader *exif_loader_new_mem (ExifMem *);
void        exif_loader_ref     (ExifLoader *);
void        exif_loader_unref   (ExifLoader *);

void        exif_loader_write_file (ExifLoader *, const char *fname);

/*
 * Returns 1 while EXIF data is read (or while there is still 
 * hope that there will be EXIF data later on), 0 otherwise.
 */
unsigned char exif_loader_write (ExifLoader *, unsigned char *, unsigned int);

void          exif_loader_reset (ExifLoader *);
ExifData     *exif_loader_get_data (ExifLoader *);

void exif_loader_log (ExifLoader *, ExifLog *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EXIF_LOADER_H__ */
