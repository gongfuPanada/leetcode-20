/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <fcntl.h>

#include <rpm/rpmio.h>
#include <rpm/header.h>
#include <rpm/rpmdb.h>

#include <glib.h>

int main(int argc, char *argv[]) 
{
    FD_t fd = NULL;
    Header hdr = NULL;
    char *Name = NULL;
    char *Version = NULL;
    char *Arch = NULL;
    struct rpmtd_s pnames; 
    char *pname = NULL;
    struct rpmtd_s rnames;
    char *rname = NULL;
    rpmdb db = NULL;

    fd = Fopen(argv[1] ? 
               argv[1] : 
               "/var/cache/isoftapp/base/koji.isoft.zhcn.cc.kojifiles.app.pkglist.005-extra", 
               "r");
    if (fd == NULL) {
        printf("ERROR: failed to open header file\n");
        goto exit;
    }
    
    openDatabase("/", "/var/lib/rpm", &db, O_RDONLY, 0644, 0);

    while (hdr = headerRead(fd, HEADER_MAGIC_YES)) {
        Name = headerGetAsString(hdr, RPMTAG_NAME);
        Version = headerGetAsString(hdr, RPMTAG_VERSION);
        Arch = headerGetAsString(hdr, RPMTAG_ARCH);
        printf("%s %s %s\n", Name, Version, Arch);

        headerGet(hdr, RPMTAG_PROVIDENAME, &pnames, HEADERGET_ARGV);
        printf("* provide: %d\n", rpmtdCount(&pnames));
        while (pname = rpmtdNextString(&pnames))
            printf("  %s\n", pname);

        headerGet(hdr, RPMTAG_REQUIRENAME, &rnames, HEADERGET_ARGV);
        printf("* require: %d\n", rpmtdCount(&rnames));
        while (rname = rpmtdNextString(&rnames)) {
            if (rpmdbCountPackages(db, rname) == 0 && 
                rpmdbCountPackagesISoftApp(db, rname) &&  
                rpmdbCountProvides(db, rname) == 0) {
                printf("  %s depend ERROR!!!\n", rname);
            } else {
                printf("  %s\n", rname);
            }
        }

        printf("\n\n");

        headerFree(hdr);
        hdr = NULL;
    }

exit:
    if (fd) {
        Fclose(fd);
        fd = NULL;
    }

    return 0;
}