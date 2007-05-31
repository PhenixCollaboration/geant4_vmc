// $Id: TG4Verbose.h,v 1.5 2006/12/12 16:21:15 brun Exp $

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \ingroup global
/// \class TG4Verbose
/// \brief Base class for defining the verbose level and 
/// a common messenger 
///
/// Class defines the verbose level and the static messenger 
/// (common for all instances).                              
/// Used as a base class for all Geant4 VMC verbose classes;
/// enables to handle the standard output in a common way.
///
/// \author I. Hrivnacova; IPN, Orsay

#ifndef TG4_VERBOSE_H
#define TG4_VERBOSE_H

#include "TG4VVerbose.h"
#include "TG4VerboseMessenger.h"

#include <globals.hh>

class G4UIcommand;

class TG4Verbose : public TG4VVerbose
{
  public:
    TG4Verbose(const G4String& cmdName);
    TG4Verbose(const G4String& cmdName, G4int verboseLevel);      
    virtual ~TG4Verbose();

  private:
    TG4Verbose();
    TG4Verbose(const TG4Verbose& right);
    TG4Verbose& operator=(const TG4Verbose& right);

    // methods
    virtual TG4VerboseMessenger* CreateMessenger();    

    // static data members
    static const G4String        fgkDirectoryName;// directory name
    static G4int                 fgCounter;       // object counter
    static TG4VerboseMessenger*  fgMessenger;     // messenger
    
    // data members
    G4UIcommand*                 fCommand;        // verbose command
};     

#endif //TG4_VERBOSE_H
