#include "PixelHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4VHit.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

#include "G4Transform3D.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<PixelHit>* PixelHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PixelHit::PixelHit()
: G4VHit(), pixelLogVol(0)
{}

// PixelHit::PixelHit(G4LogicalVolume* logVol, G4double x, G4double y)
// :pixelLogVol(logVol), XPixelID(y), YPixelID(z)

PixelHit::PixelHit(G4LogicalVolume* logVol)
: G4VHit(), pixelLogVol(logVol)
{}

PixelHit::~PixelHit()
{}


PixelHit::PixelHit(const PixelHit& right)
: G4VHit(right)
{
  // XPixelID = right.XPixelID;
  // YPixelID = right.YPixelID;
  // TrackLengthPix = right.TrackLengthPix;

  // Initialize the hit information parameters.
  engDepPix   = right.engDepPix;
  hitPos      = right.hitPos;
  pixLoc   = right.pixLoc;
  hitStart    = right.hitStart;
  hitRot      = right.hitRot;
  pixelLogVol = right.pixelLogVol;

  // Pos = right.Pos;
  // pixelLogVol = right.pLogV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const PixelHit& PixelHit::operator=(const PixelHit& right)
{
  // Include the default behavior of a hit "=" overloaded operator.
  G4VHit::operator=(right);

  // Initialize the hit information parameters.
  engDepPix   = right.engDepPix;
  hitPos      = right.hitPos;
  pixLoc      = right.pixLoc;
  hitStart    = right.hitStart;
  hitRot      = right.hitRot;
  pixelLogVol = right.pixelLogVol;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int PixelHit::operator==(const PixelHit& right) const
{
  return ((hitPos == right.hitPos) && (engDepPix == right.engDepPix));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PixelHit::Draw()
{
  G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();

  if(visManager)
  {
    G4Transform3D transRotPos(hitRot, hitPos);

    G4VisAttributes visAttributes;

    const G4VisAttributes* logVolVisAttributes = pixelLogVol->GetVisAttributes();

    if (pixelLogVol) visAttributes = *logVisAttributes;

    G4Colour colour(1., 0., 0.);

    visAttributes->SetColour(colour);
    visAttributes->SetForceWireframe(false);
    visAttributes->SetForceSolid(true);

    visManager->Draw(*pixerlLogVol, visAttributes, transRotPos);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PixelHit::Print()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
