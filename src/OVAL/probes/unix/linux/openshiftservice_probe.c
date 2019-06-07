/**
 * @file   openshiftservice_probe.c
 * @brief  openshiftservice_probe probe
 * @author "Evgeny Kolesnikov" <ekolesni@redhat.com>
 *
 *  TODO: This probe is for processing openshift_object.
 *
 */

/*
 * Copyright 2009-2019 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *   Evgeny Kolesnikov <ekolesni@redhat.com>
 */

/*
 * openshiftservice probe:
 *
 * name
 * TODO: ...
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "_seap.h"
#include "probe-api.h"
#include "probe/entcmp.h"

#include <selinux/selinux.h>
#include "openshiftservice_probe.h"

static int get_selinuxboolean(SEXP_t *ut_ent, probe_ctx *ctx)
{
	int err = 1;
	SEXP_t *item, *val;
    char * unit_name;
    
    val = probe_ent_getval(ut_ent);

    if (val == NULL) {
        SEXP_free (ut_ent);
        return (PROBE_ENOVAL);
    }

    unit_name = SEXP_string_cstr(val);
    SEXP_free (val);

    item = probe_item_create(
            OVAL_LINUX_OPENSHIFTSERVICE, NULL,
            "unit", OVAL_DATATYPE_STRING, unit_name,
            "enabled",  OVAL_DATATYPE_BOOLEAN, true,
            NULL);
    probe_item_collect(ctx, item);

    free(unit_name);

	return 0;
}

int openshiftservice_probe_main(probe_ctx *ctx, void *arg)
{
	SEXP_t *probe_in, *unit;
	int err;

	probe_in  = probe_ctx_getobject(ctx);
	unit = probe_obj_getent(probe_in, "unit", 1);

	if (unit == NULL) {
		return PROBE_ENOVAL;
	}

	err = get_selinuxboolean(unit, ctx);
	SEXP_free(unit);

	return err;
}
