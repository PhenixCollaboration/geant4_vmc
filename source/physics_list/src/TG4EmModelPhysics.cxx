//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4EmModelPhysics.cxx
/// \brief Implementation of the TG4EmModelPhysics class 
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4EmModelPhysics.h"
#include "TG4ModelConfigurationManager.h"
#include "TG4ModelConfiguration.h"
#include "TG4SpecialUrbanMscModel.h"
#include "TG4GeometryManager.h"
#include "TG4GeometryServices.h"
#include "TG4Globals.h"

#include <TVirtualMCDecayer.h>
#include <TVirtualMC.h>

#include <G4TransportationManager.hh>
#include <G4EmConfigurator.hh>
#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4PAIModel.hh>
#include <G4PAIPhotModel.hh>
#include <G4LossTableManager.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4RegionStore.hh>
#include <G4AnalysisUtilities.hh>

//
// static methods
//

//_____________________________________________________________________________
TG4EmModel TG4EmModelPhysics::GetEmModel(const G4String& modelName)
{
/// Return the model tope for given model name

  if ( modelName == GetEmModelName(kPAIModel) ) {       
    return kPAIModel;
  }  
  else if ( modelName == GetEmModelName(kPAIPhotonModel) ) {
    return kPAIPhotonModel;
  }  
  else if ( modelName == GetEmModelName(kSpecialUrbanMscModel) ) {
    return kSpecialUrbanMscModel;
  }
  else if ( modelName == GetEmModelName(kNoEmModel) ) {      
    return kNoEmModel; 
  }  
  else {
    TG4Globals::Exception(
      "TG4EmModelPhysics", "GetEmModel", 
      TString(modelName.data()) + " unknown model name.");
     return kNoEmModel;
  }
}       

//_____________________________________________________________________________
G4String  TG4EmModelPhysics::GetEmModelName(G4int modelType)
{
/// Return model name for given model type

  switch ( modelType ) {
    case kPAIModel:             return "PAI";
    case kPAIPhotonModel:       return "PAIPhoton";
    case kSpecialUrbanMscModel: return "SpecialUrbanMsc";
    case kNoEmModel:            return "";
    default:
      TG4Globals::Exception(
        "TG4EmModelPhysics", "GetEmModelName", 
        TString("Unknown model type ") + TString(modelType));
       return kNoEmModel;
  }
}    
    
//
// ctors, dtor
//

//_____________________________________________________________________________
TG4EmModelPhysics::TG4EmModelPhysics(const G4String& name)
  : TG4VPhysicsConstructor(name)
    // fMessenger(this),
    // fEmModels()
{
/// Standard constructor

  VerboseLevel(1);
}

//_____________________________________________________________________________
TG4EmModelPhysics::TG4EmModelPhysics(G4int theVerboseLevel,
                                     const G4String& name)
  : TG4VPhysicsConstructor(name, theVerboseLevel)
    // fMessenger(this),
    // fEmModels()
{
/// Standard constructor

  VerboseLevel(1);
}

//_____________________________________________________________________________
TG4EmModelPhysics::~TG4EmModelPhysics() 
{
/// Destructor
}

//
// private methods
//

//_____________________________________________________________________________
void TG4EmModelPhysics::AddModel(
                           TG4EmModel emModel,
                           const G4ParticleDefinition* particle, 
                           const G4String& regions)
{ 
/// Add selected EM model to given particle, process and region.
/// If regionName is not set, the model is set to the world region.

  // Get process name
  G4ProcessVector* processVector
    = particle->GetProcessManager()->GetProcessList();
  for (G4int i=0; i<processVector->length(); i++) {
    G4String processName;
    G4String currentProcessName = (*processVector)[i]->GetProcessName();

    // PAI applied to ionisation
    if ( currentProcessName.contains("Ioni") && ( emModel == kPAIModel || emModel == kPAIPhotonModel ) ) {
      processName = currentProcessName;
    }

    // UrbanMsc applied to msc
    if ( currentProcessName.contains("msc") && ( emModel == kSpecialUrbanMscModel ) ) {
      processName = currentProcessName;
    }

    if ( ! processName.size() ) continue;

    // CreateEM model
    //
    G4VEmModel* g4EmModel = 0;
    G4VEmFluctuationModel* g4FluctModel = 0;
    if ( emModel == kPAIModel ) {
      // PAI
      G4PAIModel* pai = new G4PAIModel(particle, "PAIModel");
      if ( verboseLevel > 2 ) {
        G4cout << "New G4PAIModel" << G4endl;
      }
      g4EmModel = pai;
      g4FluctModel = pai;
    }
    else if ( emModel == kPAIPhotonModel ) {
      // PAIPhoton
      if ( verboseLevel > 2 ) {
        G4cout << "New G4PAIPhotModel" << G4endl;
      }
      G4PAIPhotModel* paiPhot = new G4PAIPhotModel(particle, "PAIPhotModel");
      g4EmModel = paiPhot;
      g4FluctModel = paiPhot;
    }
    else if ( emModel == kSpecialUrbanMscModel ) {
      // SpecialUrbanMsc
      if ( verboseLevel > 2 ) {
        G4cout << "New TG4SpecialUrbanMscModel" << G4endl;
      }
      g4EmModel = new TG4SpecialUrbanMscModel();
      g4FluctModel = 0;
    }

    // Get regions
    std::vector<G4String> regionVector;
    if ( regions.size() ) {
      // use analysis utility to tokenize regions
      G4Analysis::Tokenize(regions, regionVector);
    }
    else {
      // Get world default region
      G4LogicalVolume* worldLV
        = TG4GeometryServices::Instance()->GetWorld()->GetLogicalVolume();
      regionVector.push_back(worldLV->GetRegion()->GetName());
    }

    for (G4int j=0; j<G4int(regionVector.size()); ++j) {

      G4String regionName = regionVector[j];

      if ( VerboseLevel() > 2 ) {
        G4cout << "Adding EM model: " << GetEmModelName(emModel)
               << " to particle: " << particle->GetParticleName()
               << " process: " << processName
               << " region(=material): " << regionName
               << G4endl;
      }

      G4LossTableManager::Instance()->EmConfigurator()
        ->SetExtraEmModel(particle->GetParticleName(), processName, g4EmModel,
                          regionName, 0.0, DBL_MAX, g4FluctModel);
    }
  }
}                               

//_____________________________________________________________________________
void TG4EmModelPhysics::AddModels(const std::vector<TG4ModelConfiguration*>& models)
{
/// Loop over all particles and their processes and check if
/// the process is present in the map

  if ( VerboseLevel() > 1 ) {
    G4cout << "TG4EmModelPhysics::AddModels" << G4endl;
    std::vector<TG4ModelConfiguration*>::const_iterator it;
    for ( it = models.begin(); it != models.end(); it++ ) {
      (*it)->Print();
    }
  }

  std::vector<TG4ModelConfiguration*>::const_iterator it;
  for ( it = models.begin(); it != models.end(); it++ ) {

    // Get model configuration
    TG4EmModel emModel = GetEmModel((*it)->GetModelName());
    G4String particles = (*it)->GetParticles();
    G4String regions = (*it)->GetRegions();

    if ( ! regions.size() ) {
      // add warning
      TString message;
      message = "No regions are defined for ";
      message += (*it)->GetModelName().data();
      TG4Globals::Warning(
       "TG4EmModelPhysics", "AddModels", message);
      continue;
    }
    
    // Add selected models
    auto aParticleIterator = GetParticleIterator();
    aParticleIterator->reset();
    while ((*aParticleIterator)()) {
      G4ParticleDefinition* particle = aParticleIterator->value();
      G4String particleName = particle->GetParticleName();
      
      // skip particles which are not in selection
      if ( particles != "all" &&
           particles.find(particle->GetParticleName()) == std::string::npos ) {
           continue;
      }

      AddModel(emModel, particle, regions);
    }
  }
}

//
// protected methods
//

//_____________________________________________________________________________
void TG4EmModelPhysics::ConstructParticle()
{
/// Instantiate particles - nothing to be done here
}

//_____________________________________________________________________________
void TG4EmModelPhysics::ConstructProcess()
{
/// Loop over all particles and their processes and check if
/// the process is present in the map

  if ( VerboseLevel() > 2 ) {
    G4cout << "TGEmModelPhysics::ConstructProcess " << G4endl;
  }

  // Get model configurations vector from geometry manager
  TG4ModelConfigurationManager* emModelsManager
    = TG4GeometryManager::Instance()->GetEmModelsManager();

  const std::vector<TG4ModelConfiguration*>& models
    = emModelsManager->GetVector();

  // Do nothing if no models were set
  if ( models.size() == 0 ) {
    if ( VerboseLevel() > 1 ) {
      G4cout << "No EM models are defined." << G4endl;
    }
    return;
  }

  // Add user selected models to G4 EM configurator
  AddModels(models);

  // Let G4 EM configurator to add all previously declared models to corresponding
  // processes
  G4LossTableManager::Instance()->EmConfigurator()->AddModels();

  if ( VerboseLevel() > 0 ) {
    G4cout << "### Selected EmModels added to EM processes" << G4endl;
  }
}
