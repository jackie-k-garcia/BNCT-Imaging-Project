#ifndef PixelHit_h
#define PixelHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

// #include "G4SystemOfUnits.hh"
// #include "G4PhysicalConstants.hh"
// #include "G4UnitsTable.hh"

class PixelHit : public G4VHit
{
  public:

    // Constructors with overloaded arguments.
    PixelHit();
    PixelHit(G4LogicalVolume* logVol);
    // PixelHit(G4LogicalVolume* logVol, G4double x, G4double y, G4double z);
    PixelHit(const PixelHit &right);

    // Ordinary destructor
    virtual ~PixelHit();

    // Overloading equal sign and equivalence test operators.
    const PixelHit& operator=(const PixelHit &right);
    int operator==(const PixelHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
    void *operator new(size_t, void* p) {return p;}

    // Defining methods to draw or print the pixel hit.
    void Draw();
    void Print();

  public:

    // Set the energy deposition in the pixel.
    inline void SetEngDep(G4double de) {engDepPix = de;}

    // Add energy deposition to the pixel.
    inline void AddEngDep(G4double de) {engDepPix += de;}

    // Get the energy deposition in the pixel.
    inline G4double GetEngDep() {return engDepPix;}

    // Set the parametrized coordinates of the pixel hit.
    inline void SetPixelLoc(G4int x, G4int y, G4int z) {pixLoc.set(x, y, z);}

    // Obtain the parametrized coordinates of the pixel hit.
    inline G4ThreeVector GetPixelLoc() {return pixLoc;}
    // inline G4int GetPixelLoc[PMTNbX][PMTNbY][PMTNbM]() {return PMTPixLoc;}

    // Set the position of the hit.
    inline void SetHitPos(G4ThreeVector xyz) {hitPos = xyz;}

    // Get the position of the hit.
    inline G4ThreeVector GetHitPos() {return hitPos;}

    // Return the logical volume of referenced pixel.
    inline const G4LogicalVolume* GetLogVol() {return pixelLogVol;}

  private:

    #include "DetectorParameterDef.hh"                // Import the gamma camera parameters

    // // Initialize the X and Y coordinates of the pixel hit as reference from a
    // //  coordinate system fixed to the scintillator matrix.
    // G4double XPixelID;
    // G4double YPixelID;

    //
    // Define the hit information parameters.
    //

    // Initialize the energy deposition in the pixel.
    G4double engDepPix;

    // Initialize the position of the hit.
    G4ThreeVector hitPos;

    // Define the PMT pixel parameterization of the pixel hit.
    G4ThreeVector pixLoc;

    // Define the start of the hit.
    G4ThreeVector hitStart;

    // Define the rotation of the hit drawing.
    G4RotationMatrix hitRot;

    // Define a logical volume to reference the pixel of interest for the hit.
    const G4LogicalVolume* pixelLogVol;

};

// typedef G4THitsCollection<PixelHit> PixelHitsCollection;

using PixelHitsCollection = G4THitsCollection<PixelHit>;

extern G4ThreadLocal G4Allocator<PixelHit>* PixelHitAllocator;

inline void* PixelHit::operator new(size_t)
{
  if (!PixelHitAllocator) PixelHitAllocator = new G4Allocator<PixelHit>;

  return (void*) PixelHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void PixelHit::operator delete(void* aHit)
{
  PixelHitAllocator->FreeSingle((PixelHit*) aHit);
}

#endif
