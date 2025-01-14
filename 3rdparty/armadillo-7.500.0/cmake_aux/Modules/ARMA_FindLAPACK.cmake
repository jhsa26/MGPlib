# - Find a LAPACK library (no includes)
# This module defines
#  LAPACK_LIBRARIES, the libraries needed to use LAPACK.
#  LAPACK_FOUND, If false, do not try to use LAPACK.
# also defined, but not for general use are
#  LAPACK_LIBRARY, where to find the LAPACK library.

SET(LAPACK_NAMES ${LAPACK_NAMES} lapack)
FIND_LIBRARY(LAPACK_LIBRARY
  NAMES ${LAPACK_NAMES}
  PATHS /usr/lib64/atlas /usr/lib/atlas /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib
  )

IF (LAPACK_LIBRARY)
  SET(LAPACK_LIBRARIES ${LAPACK_LIBRARY})
  SET(LAPACK_FOUND "YES")
ELSE (LAPACK_LIBRARY)
  SET(LAPACK_FOUND "NO")
ENDIF (LAPACK_LIBRARY)


IF (LAPACK_FOUND)
   IF (NOT LAPACK_FIND_QUIETLY)
      MESSAGE(STATUS "Found LAPACK: ${LAPACK_LIBRARIES}")
   ENDIF (NOT LAPACK_FIND_QUIETLY)
ELSE (LAPACK_FOUND)
   IF (LAPACK_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find LAPACK")
   ENDIF (LAPACK_FIND_REQUIRED)
ENDIF (LAPACK_FOUND)

# Deprecated declarations.
GET_FILENAME_COMPONENT (NATIVE_LAPACK_LIB_PATH ${LAPACK_LIBRARY} PATH)

MARK_AS_ADVANCED(
  LAPACK_LIBRARY
  )
