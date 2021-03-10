#!/usr/bin/env bash

# Copyright 2021 Red Hat Inc., Durham, North Carolina.
# All Rights Reserved.
#
# Authors:
#      Evgenii Kolesnikov <ekolesni@redhat.com>

. "$builddir/tests/test_common.sh"

set -eo pipefail

source="$srcdir/test_xccdf_requires_conflicts.xml"
result=result.xml

$OSCAP xccdf eval --profile xccdf_org.open-scap_profile_override --results "$result" "$source"

assert_exists 6 '//result[text()="pass"]'
assert_exists 10 '//result[text()="notselected"]'

rm -f "$result"
