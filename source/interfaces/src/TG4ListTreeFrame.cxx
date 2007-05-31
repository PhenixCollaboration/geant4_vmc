// $Id: TG4ListTreeFrame.cxx,v 1.4 2006/12/12 16:21:15 brun Exp $

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

// Category: interfaces
//
//========================================================
//
//------------TG4ListTreeFrame.cxx--------------------------------//
//--------- Frame for the ListTree container---//
//
//========================================================= 
//
// Author: D. Adamova
 
#include "TG4ListTreeFrame.h"
#include "TG4GuiVolume.h"
#include "TG4Globals.h"

#include <TGListTree.h>
#include <TGCanvas.h>
#include <TGTab.h>

#include <G4LogicalVolume.hh>
#include <G4UImanager.hh>

ClassImp(TG4ListTreeFrame)

TG4ListTreeFrame::TG4ListTreeFrame( TGTab* Tab, TGMainFrame* ActionFrame)
  : TObject(),
    fCanvasWindow(0),
    fVolumesListTree(0)
{
//------>canvas for the ListTree
   TGCompositeFrame* parent= Tab->AddTab("Volumes");
   fCanvasWindow = new TGCanvas( parent, 400, 240);   
   ULong_t back= TGFrame::GetWhitePixel(); 
   fCanvasWindow->ChangeBackground(back);
 
//----->ListTree for the logical volumes
   fVolumesListTree= new TGListTree(fCanvasWindow->GetViewPort(), 10, 10, kHorizontalFrame);
   fVolumesListTree->Associate(ActionFrame);
//------->container for the ListTree
   fCanvasWindow->SetContainer(fVolumesListTree);

   TGLayoutHints *lCanvasLayout = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY);
   parent->AddFrame(fCanvasWindow, lCanvasLayout);
   
}

TG4ListTreeFrame::~TG4ListTreeFrame()
{
///---> liquidator 

   G4cout << "\n Now in  TG4ListTreeFrame destructor \n" << G4endl;
   delete fCanvasWindow;
   delete fVolumesListTree;   

}

TGListTreeItem*  TG4ListTreeFrame::
AddItem(TObject* obj, TGListTreeItem* parent, const char* name, 
                       const TGPicture* open, const TGPicture* closed)
{
///----->Add item to the list tree
    return fVolumesListTree->AddItem(parent, name, obj, open, closed);
} 
  
Bool_t TG4ListTreeFrame::ProcessSubMessage(Long_t msg, Long_t parm1)
{
///---> Processes events generated by the ListTree widget

        switch (GET_SUBMSG(msg)) {

//----->Cases to Handle mouse click
   //-->case 1 
        case kCT_ITEMCLICK: 
    //---> Button 1: Select volume
            if (parm1 == kButton1){
            TGListTreeItem* item = fVolumesListTree->GetSelected();
             if (item) {
             
             TG4GuiVolume* volume=((TG4GuiVolume*) item->GetUserData());   
             G4LogicalVolume* lvolume = volume->GetLogicalVolume();

              if  ( lvolume ) {
               G4cout << "The selected logical volume name is   " 
                    << lvolume->GetName() << G4endl;
                  };
              };
            }; 
              
    //---> Button 3: Draw Volume
            if (parm1 == kButton3){
             TGListTreeItem* item = fVolumesListTree->GetSelected();
             if (item){
                DrawSelectedVolume(item);};
            }; 
                  
            break;
            
   //-->case 2            
        case kCT_ITEMDBLCLICK:
            if (parm1 == kButton1) {
                if (fVolumesListTree->GetSelected() != 0) {
                    gClient->NeedRedraw(fVolumesListTree);
                };
            };
            break;
   //-->default for GET_SUBMSG            
        default:
            break;
        }
        
    return kTRUE;        
}

void  TG4ListTreeFrame::DrawSelectedVolume(TGListTreeItem* item)
{
///---> draw the volume belonging to the item

  TG4GuiVolume* volume=((TG4GuiVolume*) item->GetUserData());
  G4LogicalVolume* lvolume = volume->GetLogicalVolume();             
//-------->>>>>>inserted part for getting parent and number of daughters
  TGListTreeItem* iParent = item -> GetParent();
  G4int noDght, ii;
  G4int icopy = 0;
  G4String parentName, lName;
    
  if (iParent) {
    
      TG4GuiVolume* vParent   = ((TG4GuiVolume*) iParent->GetUserData());
      G4LogicalVolume* lvParent = vParent->GetLogicalVolume();
      parentName = lvParent->GetName();
      noDght = lvParent->GetNoDaughters();
//------>>>> end of getting parent and number of daughters

   //------->>>>inserted for getting no on copies
      ii = 0;
      while ( ii < noDght){
         if ( lvParent->GetDaughter(ii)->GetLogicalVolume() ==  lvolume )
              icopy++;  
     
             ii++;
          };
   //------>>>> end of getting no of copies

      lName = lvolume->GetName();
  }
//------->>>>> case of iParent = 0        
  else {
      lName = "ALIC";
      icopy = 1;
  };
     
  G4cout << "For logical volume   " << lName << "   "
         << "the number of copies is :!   "  << icopy << G4endl;
//------> looping over number of copies
   ii=0;              
   while ( ii < icopy) { 
      G4String lCommand = "/vis/scene/add/volume  " ;
      lCommand += lName;
      lCommand += "  ";
      TG4Globals::AppendNumberToString( lCommand, ii);
      lCommand += "  -1";
      G4cout << "!!!!ADD VOLUME COMMAND IS!!!!   " << lCommand << G4endl;
      G4UImanager::GetUIpointer()->ApplyCommand( lCommand );
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/sceneHandler/attach");
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/refresh");
      ii++;
      };
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
}

//________________________________________________________________________________
void TG4ListTreeFrame::SendCloseMessage()
{
///---> Supposed to brighten up the "Volumes" panel
///---> plus close the Volumes tree to the ALICE icon

  TGListTreeItem* first = fVolumesListTree->GetFirstItem();
  Int_t btn = kButton1;
  fVolumesListTree->Clicked( first, btn);
  fVolumesListTree->DoubleClicked( first, btn);
  gClient->NeedRedraw(fVolumesListTree);

}

//__________________________________________________________________________________

