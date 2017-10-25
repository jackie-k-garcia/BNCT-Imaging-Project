#include "PixelROGeometry.hh"
#include "DetectorConstruction.hh"
#include "DummySD.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

PixelROGeometry::PixelROGeometry()
{
  #include "DetectorParameterDef.icc"
}

PixelROGeometry::PixelROGeometry(G4String someString)
: G4VReadOutGeometry(someString)
{
  #include "DetectorParameterDef.icc"
}

PixelROGeometry::~PixelROGeometry()
{}

G4VPhysicalVolume* PixelROGeometry::Build()
{
  // Define a dummy material to fill the volumes of the readout geoemtry
  //  but is arbitrary and doesn't affect any results.
  G4Material dummyMat = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

  // Build the readout world.
  solidROWorld = new G4Box("World",
                           WorldSizeX/2,
                           WorldSizeY/2,
                           WorldSizeZ/2);

  logicROWorld = new G4LogicalVolume(solidWorld,
                                     dummyMat,
                                     "RO World");

  physiROWorld = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "RO World",
                                   logicWorld,
                                   0,
                                   false,
                                   0);

  //
  // PMT matrix. Each PMT serves as a pixel in the readout.

  // solidBody = new G4Tubs("Body",
  //                         0,
  //                         BodyDiameter/2,
  //                         BodyLength/2,
  //                         0*radian,
  //                         twopi*radian);
  //
  // logicBody = new G4LogicalVolume(solidBody,
  //                                  BodyMaterial,
  //                                  "Body");
  //
  // physiBody = new G4PVPlacement(0,
  //                               G4ThreeVector(),
  //                               logicBody,
  //                               "Body",
  //                               logicWorld,
  //                               false,
  //                               0);

  solidROMatrix = new G4Tubs("PMT Array",
                             0,
                             PMTPixelDiameter/2,
                             PMTPixelThickness/2,
                             0*radian,
                             twopi*radian);

  // solidMatrix = new G4Box("PMT Array",
  //                         PixelSizeX/2,
  //                         PixelSizeY/2,
  //                         PixelThickness/2);

  logicROMatrix = new G4LogicalVolume(solidMatrix,
                                      dummyMat,  // NOTE: Must be double-checked!
                                      "PMT Array");

  // NOTE: Must add an extra degree of freedom to "shifted" PMT parametrization.
  for (G4int i=0; i<PMTNbX; i++)
  {
    for (G4int j=0; j<PMTNbX; j++)
    {
      for (G4int k=0; k<PMTNbM; k++)
      {
        G4ThreeVector PMTPixelPos(ScintCrystalHeight * (1/2 + i - ScintArrayWidth/2),
                                  ScintCrystalWidth  * (1/2 + j - ScintArrayHeight/2),
                                  PMTArrayDisplacement);

        physiROMatrix[i][j][k] = new G4PVPlacement(0,
                                                   PMTPixelPos,
                                                   "PMT Array",
                                                   logicROMatrix,
                                                   physiROWorld,
                                                   false,
                                                   i*j*k);
      }
    }
  }

  // Flag the PMTs as sensitiv. The pointer to the dummy sensitive
  //  detector serves only to check for sensitivity.
  DummySD* dummySensDet = new DummySD;
  logicMatrix->SetSensitiveDetector(dummySensDet);

  return physiROWorld;

}
