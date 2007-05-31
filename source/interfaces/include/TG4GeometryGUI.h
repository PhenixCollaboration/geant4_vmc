// $Id: TG4GeometryGUI.h,v 1.4 2006/12/12 16:21:15 brun Exp $

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \ingroup interfaces
/// \class TG4GeometryGUI
/// \brief Geant4 VMC Geometry Browser
///
/// \author: D. Adamova, NPI Rez

#ifndef TG4_GEOMETRY_GUI_H
#define TG4_GEOMETRY_GUI_H

#include <TObject.h>

class TG4MainFrame;
class G4LogicalVolume;
class TGListTreeItem;
class G4LogicalVolumeStore;  

class TG4GeometryGUI : public TObject
{
public:
    TG4GeometryGUI();
    virtual ~TG4GeometryGUI();
    
    void  ReadGeometryTree();
    void  RegisterLogicalVolume(G4LogicalVolume* lv, TGListTreeItem* itemv);
    void  ReadMaterials() const; 

 private:
    TG4GeometryGUI(const TG4GeometryGUI& gg) ;
    TG4GeometryGUI& operator=(const TG4GeometryGUI& gg) ;

    TG4MainFrame* fPanel;   // the main  panel
  

    ClassDef(TG4GeometryGUI,1)  // GUI for Geant4 geometry  
};

#endif

