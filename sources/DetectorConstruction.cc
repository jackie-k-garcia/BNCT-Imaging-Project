//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The Geant4 software  is  copyright of the Copyright Holders  of *
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
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 70755 2013-06-05 12:17:48Z ihrivnac $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
// #include "DetectorMessenger.hh"

#include "PixelROGeometry.hh"
#include "PixelSD.hh"
// #include "PixelParameterization.hh"

#include "G4Material.hh"
#include "G4Element.hh"
// #include "G4MaterialTable.hh"
// #include "G4ElementTable.hh"

#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
// #include "G4Cons.hh"
// #include "G4Sphere.hh"
// #include "G4Trd.hh"
// #include "G4GenericTrap.hh"
// #include "G4Para.hh"

// #include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
// #include "G4PVParameterised.hh"
// #include "G4PVReplica.hh"

#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

// #include "G4GeometryManager.hh"
// #include "G4PhysicalVolumeStore.hh"
// #include "G4LogicalVolumeStore.hh"
// #include "G4SolidStore.hh"

// #include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AutoDelete.hh"

// #include "G4SDParticleFilter.hh"
// #include "G4MultiFunctionalDetector.hh"
// #include "G4VPrimitiveScorer.hh"
// #include "G4PSCellFlux.hh"

// #include "G4GDMLParser.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
 // solidWorld(0), logicWorld(0), physiWorld(0),
 // solidScint(0), logicScint(0), physiScint(0),
 // solidPixel(0), logicPixel(0), physiPixel(0),
 // PixelMaterial(0), CeramicMaterial(0), WorldMaterial(0)
{
  #include "DetectorParameterDef.icc"

  // detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // G4VPhysicalVolume* fWorldPhysVol;

  DefineMaterials();

  ConstructSDandField();

  // return fWorldPhysVol;
  return ConstructWorld();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{

  G4NistManager* nistManager = G4NistManager::Instance();

  // Initialize strings to hold the name for elements and materials, as well as
  //  the symbol for elements.
  G4String name, symbol;

  // Initialize double-precision floating point numbers to store the mass number,
  //  atomic number and density of each element.
  G4double a, z, density;

  // Initialize integers to hold the number of elemental components in a material
  //  as well as the number of atoms of a specific element that are in a
  //  compound.
  G4int ncomponents, natoms;

  // Initialize a double-precision floating point number to hold the fraction of
  //  the mass of a compound taken by a specific element.
  G4double fractionmass;

  // Set the world material, aka. air.
  G4Material* WorldMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

  // Set the collimator material
  G4Material* CollimMaterial = nistManager->FindOrBuildMaterial("G4_Pb");

  // Set the body material.
  G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* boron = nistManager->FindOrBuildMaterial("G4_B");

  // Defining
  // Initialize a double-precision floating point number to hold the fraction of
  //  the mass of a compound taken by a specific element.
  G4double fractionmass;

  // Set the world material, aka. air.
  G4Material* WorldMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

  // Set the collimator material
  G4Material* CollimMaterial = nistManager->FindOrBuildMaterial("G4_Pb");

  // Set the tumor material.
  G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* boron = nistManager->FindOrBuildMaterial("G4_B");

  density = 1*g/cm^3;   // ASSUME: Small concentration of boron in body tissues,
                        //         near density of water for body tissues.
  boronFrac = 20.0e-6;
  tumorTissueFrac = 1.0 - boronFrac;

  G4Material* TumorMaterial = new G4Material(name="TumorMaterial", density, ncomponents=2);
  TumorMaterial->AddMaterial(water, fractionmass=tumorTissueFrac);
  TumorMaterial->AddMaterial(boron, fractionmass=boronFrac);

  // Set the body material.
  boronFrac /= 3.2;   // ASSUME: 3.2 times less boron in body tissues.
  bodyTissueFrac = 1.0 - boronFrac;

  G4Material* BodyMaterial = new G4Material(name="TumorMaterial", density, ncomponents=2);
  BodyMaterial->AddMaterial(water, fractionmass=bodyTissueFrac);
  BodyMaterial->AddMaterial(boron, fractionmass=boronFrac);

  // Defining elements needed for LSO scintillator compound
  G4Material* Lu = nistManager->FindOrBuildMaterial("G4_Lu");
  G4Material* Si = nistManager->FindOrBuildMaterial("G4_Si");
  G4Material* O  = nistManager->FindOrBuildMaterial("G4_O");
  G4Material* Ce = nistManager->FindOrBuildMaterial("G4_Ce");

  // a = 174.9668*g/mole;
  // G4Element* Lu = new G4Element(name="Lutetium", symbol="Lu", z=71., a);
  //
  // a = 28.085*g/mole;
  // G4Element* Si = new G4Element(name="Silicon", symbol="S", z=14., a);
  //
  // a = 15.999*g/mole;
  // G4Element* O = new G4Element(name="Oxygen", symbol="O", z=8., a);
  //
  // a = 140.116*g/mole;
  // G4Element* Ce = new G4Element(name="Cerium", symbol="Ce", z=58., a);

  // Build LSO material
  density = 7.4*g/cm^3;
  G4Material* LSO = new G4Material(name="LSO", density, ncomponents=4);
  LSO->AddElement(Lu, natoms=2);
  LSO->AddElement(Si, natoms=1);
  LSO->AddElement(O, natoms=5);
  // LSO->AddElement(Ce, fractionmass=0.01);   // NOTE: This is illegal, must replace with an "natoms" designation.

  // Set the scintillator crystal material.
  ScintMaterial = LSO;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{
  //
  // World
  //
  solidWorld = new G4Box("World",
                         WorldSizeX/2,
                         WorldSizeY/2,
                         WorldSizeZ/2);

  logicWorld = new G4LogicalVolume(solidWorld,
                                   WorldMaterial,
                                   "World");

  physiWorld = new G4PVPlacement(0,
                                 G4ThreeVector(),
                                 "World",
                                 logicWorld,
                                 0,
                                 false,
                                 0);

  //
  // Body
  //
  solidBody = new G4Tubs("Body",
                          0,
                          BodyDiameter/2,
                          BodyLength/2,
                          0*radian,
                          twopi*radian);

  logicBody = new G4LogicalVolume(solidBody,
                                   BodyMaterial,
                                   "Body");

  physiBody = new G4PVPlacement(0,
                                G4ThreeVector(),
                                logicBody,
                                "Body",
                                logicWorld,
                                false,
                                0);

  //
  // Tumor
  //
  solidTumor = new G4Tubs("Tumor",
                          0,
                          TumorDiameter/2,
                          TumorLength/2,
                          0*radian,
                          twopi*radian);

  logicTumor = new G4LogicalVolume(solidTumor,
                                   TumorMaterial,
                                   "Tumor");

  physiTumor = new G4PVPlacement(0,
                                 TumorDisplacement,
                                 logicTumor,
                                 "Tumor",
                                 logicBody,
                                 false,
                                 0);

  //
  // Collimator Blade Array
  //
  solidCollim = new G4Box("Collimator Array",
                          CollimCrystalHeight/2,
                          CollimCrystalWidth/2,
                          CollimCrystalThickness/2);

  logicCollim = new G4LogicalVolume(solidCollim,
                                   CollimMaterial,
                                   "Collimator Array");

 for (G4int w=1; i<CollimNbS; i++)
 {
    for (G4int i=1; i<CollimNbX; i++)
    {
      for (G4int j=1; j<CollimNbX; j++)
      {
        for (G4int k=1; k<CollimNbM; k++)
        {
          // Define the rotation angle for the collimator subset as half-pi radians.
          G4double rotAngle = w * halfpi * radian;

          // Define the rotation matrix, with a half-pi rotation per element of the parametrized subset.
          G4RotationMatrix rotMat = G4RotationMatrix();
          rotMat.rotateZ(rotAngle);

          // Define the length at which to rotate from the pixel center.
          G4double rotationLength = 1/2 * CollimBladeHeight;

          // Create a vector to account for the translation in rotation.
          G4ThreeVector transRotVec = rotationLength *
                                        G4ThreeVector(std::cos(rotAngle), std::sin(rotAngle), 0.0);

          // Define the translation vector, accounting for translation in rotation.
          G4ThreeVector collimBladePos(CollimBladeHeight * (i CollimBladeWidth/2)  + transRotVec.x(),
                                       CollimBladeWidth  * (j CollimBladeHeight/2) + transRotVec.y(),
                                       GammaCameraDisplacement);

          // Define a 3D transform to encompass the translation and rotation.
          G4Transform3D transformTransRot = G4Transform3D(rotMat, collimBladePos);

          // // Account for translational rotation.
          // G4double newX, newY, newZ;
          // newX = collimBladePos.x() * transRotVec.x();
          // newY = collimBladePos.y() * transRotVec.y();
          // newZ = collimBladePos.z() * transRotVec.z();
          // collimBladePos->set(newX, newY, newZ)

          physiCollim[w][i][j][k] = new G4PVPlacement(transformTransRot,
                                                      logicCollim,
                                                      "Scintillator Array",
                                                      physiWorld,
                                                      false,
                                                      0);
        }
      }
    }
  }

  //
  // LGO Scintillator Crystal Array
  //
  solidScint = new G4Box("Scintillator Array",
                          ScintCrystalHeight/2,
                          ScintCrystalWidth/2,
                          ScintCrystalThickness/2);

  logicScint = new G4LogicalVolume(solidScint,
                                   ScintMaterial,
                                   "Scintillator Array");

  for (G4int i=0; i<ScintNbX; i++)
  {
    for (G4int j=0; j<ScintNbX; j++)
    {
      for (G4int k=0; k<ScintNbM; k++)
      {
        G4ThreeVector scintCrystalPos(ScintCrystalHeight * (1/2 + i - ScintArrayWidth/2),
                                      ScintCrystalWidth  * (1/2 + j - ScintArrayHeight/2),
                                      GammaCameraDisplacement);

        physiScint[i][j][k] = new G4PVPlacement(0,
                                                scintCrystalPos,
                                                logicScint,
                                                "Scintillator Array",
                                                physiWorld,
                                                false,
                                                i*j*k);
      }
    }
  }

  // Set the visibility of the world and it's logical volumes.
  SetLogicalVolVisAtt();

  // Return the physical world
  return physiWorld;
}

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetLogicalVolVisAtt()
{
  // Make world invisible
  logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

  // Color code body lightly
  G4VisAttributes* bodyVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.2));

  bodyVisAtt->SetVisibility(true);

  logicBody->SetVisAttributes(bodyVisAtt);

  // Color code tumor dark
  G4VisAttributes* tumorVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));

  tumorVisAtt->SetVisibility(true);

  logicTumor->SetVisAttributes(tumorVisAtt);

  // Color code scintillator
  G4VisAttributes* scintVisAtt = new G4VisAttributes(G4Colour(0.1, 0.0, 0.1));

  scintVisAtt->SetVisibility(true);

  logicScint->SetVisAttributes(scintVisAtt);

  // Make collimator as dark as possible
  G4VisAttributes* collimVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));

  collimVisAtt->SetVisibility(true);

  logicCollim->SetVisAttributes(collimVisAtt);
}

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Create a new sensitive detector (SD) manager pointer.
  G4SDManager* SD_manager = G4SDManager::GetSDMpointer();

  // Set the verbose level of the SD manager to 1.
  SD_manager->SetVerboseLevel(1);

  G4String pixelSDname = "/pixel";

  RunAction* runAct = new RunAction;

  PixelSD* pixelSD = new PixelSD(pixelSDname, runAct);

  G4String ROgeometryName = "PixelROGeom";

  G4VReadOutGeometry* pixelRO = new PixelROGeometry(ROgeometryName);

  pixelRO->BuildROGeometry();

  pixelSD->SetROgeometry(pixelRO);

  SD_manager->AddNewDetector(pixelSD);

  logicPixel->SetSensitiveDetector(pixelSD);
}

// void DetectorConstruction::ConstructSDandField()
// {
  // // Create a reference to the SD cache pointer.
  // G4MultiFunctionalDetector* &sensitiveDetect  // // Create a reference to the SD cache pointer.
  // G4MultiFunctionalDetector* &sensitiveDetector =
  //   fSensitiveDetectorCache.Get();
  //
  // if (!sensitiveDetector)
  // {
  //   sensitiveDetector = new G4MultiFunctionalDetector("MyDetector");
  //
  //   G4VPrimitiveScorer* flux_scorer;
  //
  //   G4String filterName, partic;leName;
  //   G4SDParticleFilter* neutronFilter =
  //     new G4SDParticleFilter(filterName = "neutronFilter",
  //                            particleName = "neutron");
  //
  //   flux_scorer = new G4PSCellFlux("neutron cell flux");
  //   flux_scorer->SetFilter(neutronFilter);
  //   sensitiveDetector->RegisterPrimitive(flux_scorer);
  // }
  //
  // SD_manager->AddNewDetector(sensitiveDetector);
  // fScoringVolume->SetSensitiveDetector(sensitiveDetector);or =
  //   fSensitiveDetectorCache.Get();
  //
  // if (!sensitiveDetector)
  // {
  //   sensitiveDetector = new G4MultiFunctionalDetector("MyDetector");
  //
  //   G4VPrimitiveScorer* flux_scorer;
  //
  //   G4String filterName, particleName;
  //   G4SDParticleFilter* neutronFilter =
  //     new G4SDParticleFilter(filterName = "neutronFilter",
  //                            particleName = "neutron");
  //
  //   flux_scorer = new G4PSCellFlux("neutron cell flux");
  //   flux_scorer->SetFilter(neutronFilter);
  //   sensitiveDetector->RegisterPrimitive(flux_scorer);
  // }
  //
  // SD_manager->AddNewDetector(sensitiveDetector);
  // fScoringVolume->SetSensitiveDetector(sensitiveDetector);

// }

//
// void DetectorConstruction::PrintPixelParameters()
// {
//
// }
//
// void DetectorConstruction::SetPixelMaterial(G4String materialChoice)
// {
//
// }
//
// void DetectorConstruction::SetPixelThickness(G4double val)
// {
//
// }
//
// void DetectorConstruction::UpdateGeometry()
// {
//
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
