# - Try to find OpenShiftCompliance
# Once done, this will define
#
# OPENSHIFTCOMPLIANCE_FOUND - system has OPENSHIFTCOMPLIANCE
# OPENSHIFTCOMPLIANCE_INCLUDE_DIRS - the OPENSHIFTCOMPLIANCE include directories
# OPENSHIFTCOMPLIANCE_LIBRARIES - link these to use OPENSHIFTCOMPLIANCE

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(OPENSHIFTCOMPLIANCE_PKGCONF openshiftcompliance)

# Include dir
find_path(OPENSHIFTCOMPLIANCE_INCLUDE_DIR
  NAMES openshiftcompliance.h
  HINTS ${OPENSHIFTCOMPLIANCE_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(GCONF_LIBRARY
  NAMES openshiftcompliance
  HINTS ${OPENSHIFTCOMPLIANCE_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(OPENSHIFTCOMPLIANCE_PROCESS_INCLUDES OPENSHIFTCOMPLIANCE_INCLUDE_DIR)
set(OPENSHIFTCOMPLIANCE_PROCESS_LIBS OPENSHIFTCOMPLIANCE_LIBRARY)
libfind_process(OPENSHIFTCOMPLIANCE)
