//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup E01
/// \file E01/run_g4.C
/// \brief Macro for running Example01 with Geant4.

void run_g4(const TString& configMacro = "g4Config.C")
{
/// Macro function for running Example01 with Geant4 from
/// Root interactive session.
/// Note that since Root 6 the libraries have to be loaded first
/// via load_g4.C.
/// \param configMacro configuration macro name, default \ref E01/g4Config.C

  // MC application
  Ex01MCApplication* appl
    = new Ex01MCApplication("Example01", "The example01 MC application");

  // Initialize MC
  appl->InitMC(configMacro);

  // Run MC
  appl->RunMC(1);

  delete appl;
}

