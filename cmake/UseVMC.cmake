#------------------------------------------------
# The Virtual Monte Carlo packages
# Copyright (C) 2014 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: vmc@pcroot.cern.ch
#-------------------------------------------------

# Configuration file for CMake build for VMC applications.
# It defines include directories, compile definitions and link libraries
# (VMC_LIBRARIES) for all required and optional packages.
#
# I. Hrivnacova, 26/02/2014

#message(STATUS "Processing UseVMC.cmake")

if (NOT VMC_FOUND)
  find_package(VMC REQUIRED)
endif()

set(VMC_LIBRARIES)

# ROOT (required)
include_directories(${ROOT_INCLUDE_DIRS})

# MTRoot (optional)
if (VMC_WITH_MTRoot)
  # MTRoot
  if (MTRoot_FOUND)
     # build outside Geant4VMC
    include_directories(${MTRoot_INCLUDE_DIRS})
    set(MC_LIBRARIES ${MTRoot_LIBRARIES} ${MC_LIBRARIES})
  else()
     # build inside Geant4VMC
     # includes are already defined
     include_directories(${Geant4VMC_SOURCE_DIR}/mtroot/include)
     set(MC_LIBRARIES ${MC_LIBRARIES} mtroot)
  endif(MTRoot_FOUND)
endif(VMC_WITH_MTRoot)

# Finally add Root libraries
set(VMC_LIBRARIES ${VMC_LIBRARIES} ${ROOT_LIBRARIES} -lVMC -lEG)

# Utility to defined installation lib directory
if("${CMAKE_INSTALL_LIBDIR}" MATCHES "")
  include(VMCInstallLibDir)
endif()

#message(STATUS "VMC_LIBRARIES ${VMC_LIBRARIES}")
