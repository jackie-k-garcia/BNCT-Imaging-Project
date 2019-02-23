#ifndef PixelROGeometry_h
#define PixelROGeometry_h 1

#include "G4VReadOutGeometry.hh"
#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"

class PixelROGeometry : public G4VReadOutGeometry
{
public:
  PixelROGeometry();
  PixelROGeometry(G4String);
  ~PixelROGeometry();

  // const G4VPhysicalVolume* GetPMTPixel(int i, int j, int k)
  // {
  //   return physiROMatrix[i][j][k];
  // }

private:

  G4VPhysicalVolume* Build();

  #include "DetectorParameterDef.hh"

  G4Box*             solidROWorld;     // Pointer to the solid World
  G4LogicalVolume*   logicROWorld;     // Pointer to the logical World
  G4VPhysicalVolume* physiROWorld;     // Pointer to the physical World

  G4Tubs*            solidROMatrix;    // Pointer to the solid Matrix
  G4LogicalVolume*   logicROMatrix;
  // G4VPhysicalVolume* physiROMatrix; //[64][64][1];

  // G4Box*             solidROLinlayer;  // Pointer to the solid Linlayer
  // G4LogicalVolume*   logicROLinlayer;
  // G4VPhysicalVolume* physiROLinlayer;
  //
  // G4Box*             solidROPixel;     // Pointer to the solid Pixel
  // G4LogicalVolume*   logicROPixel;
  // G4VPhysicalVolume* physiROPixel;

};

#endif
