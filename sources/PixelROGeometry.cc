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
  solidWorld = new G4Box("World",
                         WorldSizeX/2,
                         WorldSizeY/2,
                         WorldSizeZ/2);

  logicWorld = new G4LogicalVolume(solidWorld,
                                   defaultMaterial,
                                   "World");

  physiWorld = new G4PVPlacement(0,
                                 G4ThreeVector(),
                                 "World",
                                 logicWorld,
                                 NULL,
                                 false,
                                 0);

  //
  // PMT matrix. Each PMT serves as a pixel in the readout.
  //
  solidMatrix = new G4Box("PMT Array",
                          PixelSizeX/2,
                          PixelSizeY/2,
                          PixelThickness/2);

  logicMatrix = new G4LogicalVolume(solidMatrix,
                                    PixelMaterial,  // NOTE: Must be double-checked!
                                    "PMT Array");

  for (G4int i=0; i<NbX; i++)
  {
    for (G4int j=0; j<NbX; j++)
    {
      for (G4int k=0; k<NbM; k++)
      {
        G4ThreeVector pixelPos(PixelSizeX/2 + PixelSizeX*i,
                               PixelSizeY/2 + PixelSizeY*j,
                               0);

        physiMatrix[i][j][k] = new G4PVPlacement(0,
                                                 pixelPos,
                                                 "PMT Array",
                                                 logicMatrix,
                                                 physiWorld,
                                                 false,
                                                 0);
      }
    }
  }

  // Flag the PMTs as sensitiv. The pointer to the dummy sensitive
  //  detector serves only to check for sensitivity.
  DummySD* dummySensDet = new DummySD;
  logicMatrix->SetSensitiveDetector(dummySensDet);

  return physiROWorld;

}
