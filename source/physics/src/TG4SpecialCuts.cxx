// $Id: TG4SpecialCuts.cxx,v 1.7 2006/12/12 16:21:16 brun Exp $

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

// Classes TG4pecialCutsFor*
// --------------------------------------
// See the class descriptions in the header file.

#include "TG4SpecialCuts.h"
#include "TG4Limits.h"

//
//  Class TG4SpecialCutsForChargedHadron implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForChargedHadron::TG4SpecialCutsForChargedHadron(
                                                 const G4String& processName)
  : TG4VSpecialCuts(processName) 
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForChargedHadron::~TG4SpecialCutsForChargedHadron() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForChargedHadron::GetMinEkine(const TG4Limits& limits,
                                                     const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.
// --- 

  return limits.GetMinEkineForChargedHadron(track);
}  

//
//  Class TG4SpecialCutsForElectron implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForElectron::TG4SpecialCutsForElectron(const G4String& processName)
  : TG4VSpecialCuts(processName)
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForElectron::~TG4SpecialCutsForElectron() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForElectron::GetMinEkine(const TG4Limits& limits,
                                                const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForElectron(track);
}  

//
//  Class TG4SpecialCutsForEplus implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForEplus::TG4SpecialCutsForEplus(const G4String& processName)
  : TG4VSpecialCuts(processName) 
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForEplus::~TG4SpecialCutsForEplus() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForEplus::GetMinEkine(const TG4Limits& limits,
                                             const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForEplus(track);
}  

//
//  Class TG4SpecialCutsForGamma implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForGamma::TG4SpecialCutsForGamma(const G4String& processName)
  : TG4VSpecialCuts(processName)
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForGamma::~TG4SpecialCutsForGamma() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForGamma::GetMinEkine(const TG4Limits& limits,
                                             const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForGamma(track);
}  

//
//  Class TG4SpecialCutsForMuon implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForMuon::TG4SpecialCutsForMuon(const G4String& processName)
  : TG4VSpecialCuts(processName) 
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForMuon::~TG4SpecialCutsForMuon() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForMuon::GetMinEkine(const TG4Limits& limits,
                                            const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForMuon(track);
}  

//
//  Class TG4SpecialCutsForNeutralHadron implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForNeutralHadron::TG4SpecialCutsForNeutralHadron(
                                              const G4String& processName)
  : TG4VSpecialCuts(processName)
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForNeutralHadron::~TG4SpecialCutsForNeutralHadron() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForNeutralHadron::GetMinEkine(const TG4Limits& limits,
                                                     const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForNeutralHadron(track);
}  

//
//  Class TG4SpecialCutsForOther implementation
//

//_____________________________________________________________________________
TG4SpecialCutsForOther::TG4SpecialCutsForOther(const G4String& processName)
  : TG4VSpecialCuts(processName)
{
/// Standard and default constructor
}

//_____________________________________________________________________________
TG4SpecialCutsForOther::~TG4SpecialCutsForOther() {
//
}

//_____________________________________________________________________________
G4double TG4SpecialCutsForOther::GetMinEkine(const TG4Limits& limits,
                                             const G4Track& track) const
{                                             
/// Return the min kinetic energy cut from limits.

  return limits.GetMinEkineForOther(track);
}  
