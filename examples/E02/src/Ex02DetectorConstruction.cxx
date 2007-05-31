// $Id: Ex02DetectorConstruction.cxx,v 1.4 2007/02/14 16:34:04 brun Exp $

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

//
// Geant4 ExampleN02 adapted to Virtual Monte Carlo 
//
// Id: Ex02DetectorConstruction.cc,v 1.11 2002/01/09 17:24:09 ranjard Exp 
// GEANT4 tag Name: geant4-04-00-patch-02 
//
// by Ivana Hrivnacova, 21.4.2002
 
#include <iostream>

#include <TVirtualMC.h>
#include <TGeoManager.h>

#include "Ex02DetectorConstruction.h"
#include "Ex02ChamberParameterisation.h"

ClassImp(Ex02DetectorConstruction)

using namespace std;

//_____________________________________________________________________________
Ex02DetectorConstruction::Ex02DetectorConstruction()
  : TObject(),
    fWorldLength(0.),  
    fTargetLength(0.), 
    fTrackerLength(0.),
    fNofChambers(0) ,  
    fChamberWidth(0.),  
    fChamberSpacing(0.),
    fImedAir(0),
    fImedPb(0),
    fImedXe(0)
{
  //fpMagField = new ExN02MagneticField();

//--------- Sizes of the principal geometrical components (solids)  ---------
  
  fNofChambers = 5;
  fChamberWidth =   20;
  fChamberSpacing = 80;
  
  fTrackerLength = (fNofChambers+1)*fChamberSpacing; // Full length of Tracker
  fTargetLength  = 5.0;                              // Full length of Target
  fWorldLength= 1.2 *(fTargetLength+fTrackerLength);
}

//_____________________________________________________________________________
Ex02DetectorConstruction::~Ex02DetectorConstruction()
{
  //delete fpMagField;
}

//_____________________________________________________________________________
void Ex02DetectorConstruction::ConstructMaterials()
{
//--------- Material definition ---------

  // Create Root geometry manager 
  new TGeoManager("TGeo", "Root geometry manager");
   
  Double_t a;
  Double_t z;
  Double_t density;
  Double_t radl;
  Double_t absl;
 
  Double_t a2[2] = { 14.01, 16.00};
  Double_t z2[2] = {  7.0,   8.0};
  Double_t w2[2] = {  0.7,   0.3};
  density = 1.29e-03;  
  Int_t imatAir = 1;
  gGeoManager->Mixture("Air", a2, z2, density, 2, w2, imatAir); 

  a = 207.19;
  z = 82.;
  density = 11.35;
  radl = 0.5612;
  absl = 0.1;
  Int_t imatPb = 2;  
  gGeoManager->Material("Lead", a, z, density, imatPb, radl, absl);  

  a = 131.29;
  z = 54.;
  density = 5.458e-03;
  //pressure    = 1*atmosphere;
  //temperature = 293.15*kelvin;
  radl =  1553.9; 
  absl = 0.1;
  Int_t imatXe = 3;
  gGeoManager->Material("XenonGas", a, z, density, imatXe, radl, absl);
  
  //
  // Tracking medias
  //

  Int_t ifield = 2;          // User defined magnetic field
  Double_t fieldm = 10.;     // Maximum field value (in kiloGauss)
  Double_t epsil  = .001;    // Tracking precision, 
  Double_t stemax = -0.01;   // Maximum displacement for multiple scat 
  Double_t tmaxfd = -20.;    // Maximum angle due to field deflection 
  Double_t deemax = -.3;     // Maximum fractional energy loss, DLS 
  Double_t stmin  = -.8;
  fImedAir = 1;
  gGeoManager->Medium("Air", fImedAir, imatAir, 0, ifield, fieldm, tmaxfd, 
                      stemax, deemax, epsil, stmin); 
  fImedPb = 2;
  gGeoManager->Medium("Lead", fImedPb, imatPb, 0, ifield, fieldm, tmaxfd, 
                      stemax, deemax, epsil, stmin); 
  fImedXe = 3;
  gGeoManager->Medium("XenonGas", fImedXe, imatXe, 0, ifield, fieldm, tmaxfd,
                      stemax, deemax, epsil, stmin); 
}    

//_____________________________________________________________________________
void Ex02DetectorConstruction::ConstructGeometry()
{
//--------- Sizes of the principal geometrical components (solids)  ---------
  
  Int_t targetMater  = fImedPb;
  Int_t chamberMater = fImedXe;
   
  Double_t targetSize  = 0.5*fTargetLength;    // Half length of the Target  
  Double_t trackerSize = 0.5*fTrackerLength;   // Half length of the Tracker
      
  Double_t* ubuf = 0;

//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  //------------------------------ 
  // World
  //------------------------------ 

  Double_t halfWorldLength = 0.5*fWorldLength;
  
  Double_t world[3];
  world[0] = halfWorldLength;
  world[1] = halfWorldLength;
  world[2] = halfWorldLength;
  TGeoVolume *top = gGeoManager->Volume("WRLD","BOX", fImedAir, world, 3);
  gGeoManager->SetTopVolume(top);

  //------------------------------ 
  // Target
  //------------------------------
  
  Double_t target[3];
  target[0] = targetSize;
  target[1] = targetSize;
  target[2] = targetSize;
  gGeoManager->Volume("TARG", "BOX", targetMater, target, 3);

  Double_t posX =  0.;
  Double_t posY =  0.;
  Double_t posZ =  -(targetSize+trackerSize);
  gGeoManager->Node("TARG", 1 ,"WRLD", posX, posY, posZ, 0, kTRUE, ubuf);

  cout << "Target is " << fTargetLength << " cm" 
       //<< " of " << TargetMater->GetName() 
       << " of lead "
       << endl;

  //------------------------------ 
  // Tracker
  //------------------------------
  
  Double_t tracker[3];
  tracker[0] = trackerSize;
  tracker[1] = trackerSize;
  tracker[2] = trackerSize;
  gGeoManager->Volume("TRAK", "BOX", fImedAir, tracker, 3);

  posX = 0.;
  posY = 0.;
  posZ = 0.;
  gGeoManager->Node("TRAK", 1 ,"WRLD", posX, posY, posZ, 0, kTRUE, ubuf);
 
  //------------------------------ 
  // Tracker segments
  //------------------------------
  // 
  // An example of Parameterised volumes
  // dummy values for G4Box -- modified by parameterised volume
  // - implemented using Gsposp

  Double_t chamber[3];
  chamber[0] = -1;
  chamber[1] = -1;
  chamber[2] = -1;
  gGeoManager->Volume("CHMB","BOX", chamberMater, chamber, 0);

  Double_t firstPosition = -trackerSize + 0.5*fChamberWidth;
  Double_t firstLength = fTrackerLength/10;
  Double_t lastLength  = fTrackerLength;
  Ex02ChamberParameterisation* chamberParam 
    = new Ex02ChamberParameterisation(  
			   fNofChambers,          // NoChambers 
			   firstPosition,         // Z of center of first 
			   fChamberSpacing,        // Z spacing of centers
			   fChamberWidth,          // Width Chamber 
			   firstLength,           // lengthInitial 
			   lastLength);           // lengthFinal
  for (Int_t i=0; i<fNofChambers; i++) {
    Double_t pos[3];
    Double_t dim[3];
    chamberParam->ComputeTransformation(i, pos);
    chamberParam->ComputeDimensions(i, dim);
    gGeoManager->Node("CHMB", i ,"TRAK", pos[0], pos[1], pos[2], 0, 
                      kTRUE, dim, 3); 
  }  

  cout << "There are " << fNofChambers 
       << " chambers in the tracker region. "
       << "The chambers are " << fChamberWidth*10. << " mm of " 
       //<< ChamberMater->GetName() 
       << "Xenon gas"
       << "\n The distance between chamber is "
       << fChamberSpacing << " cm" 
       << endl;
	 

  // close geometry
  gGeoManager->CloseGeometry();
    
  // notify VMC about Root geometry
  gMC->SetRootGeometry();

  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 
/*

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String trackerChamberSDname = "ExN02/TrackerChamberSD";
  ExN02TrackerSD* aTrackerSD = new ExN02TrackerSD( trackerChamberSDname );
  SDman->AddNewDetector( aTrackerSD );
  logicChamber->SetSensitiveDetector( aTrackerSD );
*/  

//--------- Visualization attributes -------------------------------
/*
  G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  logicWorld  ->SetVisAttributes(BoxVisAtt);  
  logicTarget ->SetVisAttributes(BoxVisAtt);
  logicTracker->SetVisAttributes(BoxVisAtt);
  
  G4VisAttributes* ChamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  logicChamber->SetVisAttributes(ChamberVisAtt);
*/  
//--------- example of User Limits -------------------------------

  // below is an example of how to set tracking constraints in a given
  // logical volume(see also in N02PhysicsList how to setup the process
  // G4UserSpecialCuts).  
  // Sets a max Step length in the tracker region
  // Double_t maxStep = 0.5*fChamberWidth, maxLength = 2*fTrackerLength;
  // Double_t maxTime = 0.1*ns, minEkin = 10*MeV;
  // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //                                               minEkin));
  
}

//_____________________________________________________________________________
void Ex02DetectorConstruction::SetTargetMaterial(const TString& /*materialName*/)
{
  Warning("SetTargetMaterial", "Not available in virtual Monte Carlo");
}
 
//_____________________________________________________________________________
void Ex02DetectorConstruction::SetChamberMaterial(const TString& /*materialName*/)
{
  Warning("SetTargetMaterial", "Not available in virtual Monte Carlo");
}
