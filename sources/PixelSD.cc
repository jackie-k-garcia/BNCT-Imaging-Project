//
//  PixelSD.cc	CIPHER 3
//

#include "PixelSD.hh"

#include "PixelHit.hh"
#include "DetectorConstruction.hh"

#include "RunAction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UIsession.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4strstreambuf.hh"
#include "G4ios.hh"

#include <sstream>

#include "G4SteppingVerbose.hh" //to get the process name
#include "G4VProcess.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"


PixelSD::PixelSD(G4String name, RunAction *run)
:G4VSensitiveDetector(name), Run(run),
 // NbOfPixelsInX(10),NbOfPixelsInY(10)
{
  G4String HCname;
  collectionName.insert(HCname="PixCollection");
}



PixelSD::~PixelSD()
{;}



void PixelSD::Initialize(G4HCofThisEvent*)
{
  PixCollection = new PixelHitsCollection
                      (SensitiveDetectorName, collectionName[0]);

  for (G4int j=0;j<NbOfPixelsInX;j++)
  {
    for (G4int k=0;k<NbOfPixelsInY;k++)
    {
      PixelID[j][k] = -1;
    }
  }

  evtorder = 0;
  recordY = -1; recordZ = -1;

  copyIDinY =-1;
  copyIDinZ =-1;
  edep =-2;
  Run->fillPerHit(copyIDinY, copyIDinZ, edep);
}



G4bool PixelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{

  if(!ROhist) return false;
  G4Track* track= aStep->GetTrack();
  G4double initenergy = track->GetVertexKineticEnergy();
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4String process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName(); //Process Hit Identification
                                              //(Compton,Photoelectr.,Pair Prod.,etc)


 G4cout << " Process : " << process << " " << G4endl;
// G4cout << " Initial Energy : " << initenergy << " " << G4endl;

  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
      stepl = aStep->GetStepLength();

  if ((edep==0.) && (stepl==0.)) return false;


  G4VPhysicalVolume* physVol = ROhist->GetVolume();
  //  G4VPhysicalVolume* motherVol = ROhist->GetVolume(1);

  // Examine to figure out how to incorporate an array matrix
  copyIDinX = ROhist->GetReplicaNumber();
  copyIDinY = ROhist->GetReplicaNumber(1);

  PixelHit* pixHit = new PixelHit(physVol->GetLogicalVolume(), copyIDinX, copyIDinY);

  int ipixel = PixCollection->insert( pixHit );
  ipixel=ipixel*1;

  //
  // Controls the module number of interaction
  //

  //G4double xposi = aStep->GetTrack()->GetPosition().z();
  G4double yposi = aStep->GetTrack()->GetPosition().x();
  G4double zposi = aStep->GetTrack()->GetPosition().y();
  copyIDinX = initenergy;   // ERROR?
  copyIDinY = yposi;
  // copyIDinZ = zposi;

  // Interaction order, discrimination of processes and output data control

  // if(process=="compt")
  // {
  //         evtorder++;
  //         Run->fillPerHit(copyIDinY,copyIDinZ,edep);
  // }
  // if(process=="polarCompt")
  // {
  // 	evtorder++;
  // 	Run->fillPerHit(copyIDinY,copyIDinZ,edep);
  // }

  // Check which photon interaction processes we have to bin.
  if(process=="phot")
  {
    evtorder++;
  	Run->fillPerHit(copyIDinX,copyIDinY,edep);
  }
  if(process=="eIoni")
  {
    evtorder++;
    Run->fillPerHit(copyIDinX,copyIDinY,edep);
  }

  if(process=="Transportation") {}

  if(process=="initStep"){}

  return true;
}



void PixelSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  // Flag End of Event to RunAction.hh
  Run->fillPerHit(-1,-1,-1);

  static G4int HCID = -1;

  if(HCID<0)
  {
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }

  HCE->AddHitsCollection(HCID, PixCollection);
}



void PixelSD::clear()
{}

void PixelSD::DrawAll()
{}

void PixelSD::PrintAll()
{}
