//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//  Detector Construction Class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"
#include <vector>

class G4Box;

class G4LogicalVolume;
class G4VPhysicalVolume;
// class G4Region;

class G4Material;
// class DetectorMessenger; // NOTE: Must create this class based off StratSep code!
class G4MultiFunctionalDetector;
// class DetectorMessenger;
class PixelSD; // NOTE: Must create this class based off StratSep code!

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:

    // void PrintPixelParameters();
    // void SetPixelThickness(G4double);
    // void SetPixelMaterial(G4String);
    // void SetCeramicMaterial(G4String);

  public:

    // Construct the world geometry as well as define the materials and the SD
    //  and RO geometry.
    virtual G4VPhysicalVolume* Construct();

    // void UpdateGeometry();

    // Construct the sensitive detectors and electromagnetic fields through them,
    //  if desired.
    void ConstructSDandField();

    // const G4VPhysicalVolume* GetScintPixel(int i, int j, int k)
    // {
    //   return physiScint[i][j][k];
    // }

    // // G4LogicalVolume* ReturnVolume() const {return fScoringVolume;}
    // G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}
    //
    // std::vector<G4LogicalVolume*> GetScoringVolumeVec() const
    // {
    //   return fScoringVolumeVec;
    // }
    //
    // // Return the number of elements in the scoring volume vector.
    // G4int GetScoreVolVecSize() const {return fScoringVolumeVec.size();}

  public:

     G4double GetWorldSizeX()           {return WorldSizeX;};  // Return the world size parameters
     G4double GetWorldSizeY()           {return WorldSizeY;};
     G4double GetWorldSizeZ()           {return WorldSizeZ;};

     G4double GetScintArrayWidth()      {return ScintArrayHeight;};     // Return the matrix size parameters
     G4double GetScintArrayHeight()     {return ScintArrayWidth;};
     G4double GetScintArrayThickness()  {return ScintArrayThickness;};

     G4double GetScintCrystalHeight()          {return ScintCrystalHeight;};    // Return the pixel size parameters
     G4double GetScintCrystalWidth()           {return ScintCrystalWidth;};
     G4double GetScintCrystalThickness()       {return ScintCrystalThickness;};

     const G4VPhysicalVolume* GetPhysiWorld()      {return physiWorld;};   // Return the world physical volume
    //  const G4VPhysicalVolume* GetPhysiScintArray() {return physiScint;};   // Return the matrix physical volume

  private:

    #include "DetectorParameterDef.hh"                  // Import the model parameters

    // Define the world.
    G4Box*             solidWorld;                      // Pointer to the solid world
    G4LogicalVolume*   logicWorld;                      // Pointer to the logical world
    G4VPhysicalVolume* physiWorld;                      // Pointer to the physical world

    // Define the tumor.
    // G4Tubs*             solidTumor;                      // Pointer to the solid world
    G4LogicalVolume*   logicTumor;                      // Pointer to the logical world
    G4VPhysicalVolume* physiTumor;                      // Pointer to the physical world

    // Define the body.
    // G4Tubs*             solidBody;                      // Pointer to the solid world
    G4LogicalVolume*   logicBody;                      // Pointer to the logical world
    G4VPhysicalVolume* physiBody;                      // Pointer to the physical world

    // Define the scintillator pixel array.
    G4Box*             solidScint;                     // Pointer to the solid scintillator matrix
    G4LogicalVolume*   logicScint;                     // Pointer to the logical scintillator matrix
    // G4VPhysicalVolume*
    //   physiScint[64][32][1];        // Pointer to the physical scintillator matrix
    // G4VPhysicalVolume* physiScintPixel;

    // Define the collimator array.
    G4Box*             solidCollim;                             // Pointer to the solid collimator matrix
    G4LogicalVolume*   logicCollim;                             // Pointer to the logical collimator matrix
    // G4VPhysicalVolume*
      // physiCollim[CollimNbS][CollimNbX][CollimNbY][CollimNbM];  // Pointer to the physical collimator matrix

    // Define the materials in use.
    G4Material*        ScintMaterial;                  // Pointer to the pixel material
    G4Material*        CollimMaterial;                 // Pointer to the collimator material
    G4Material*        TumorMaterial;                  // Pointer to the tumor material
    G4Material*        BodyMaterial;                   // Pointer to the body material
    G4Material*        WorldMaterial;                  // Pointer to the world material

    // G4Material*        MatrixMatrial;     // Pointer to the matrix material
    // G4Material*        CeramicMaterial;   // Pointer to the ceramic material

  private:

    // DetectorMessenger* detectorMessenger;  //pointer to the detector messenger
    PixelSD* pixelSD;  //pointer to the sensitive detector pixel

    // G4Material*        fWorldMater;
    // G4VPhysicalVolume* fPhysiWorld;
    // G4LogicalVolume* scoringVolume;
    // std::vector<G4LogicalVolume*> scoringVolumeVec;

    // Construct the world geometry.
    virtual G4VPhysicalVolume* ConstructWorld();

    void DefineMaterials();

    // G4VPhysicalVolume* ConstructVolumes();
    // G4VPhysicalVolume* ConstructGammaCamera();

    void SetLogicalVolVisAtt();

    // // Use of G4Cache for multi-threaded operation. Allows for storage of
    // // a seperate detector pointer per thread.
    // const G4Cache<G4MultiFunctionalDetector*> fSensitiveDetectorCache;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
