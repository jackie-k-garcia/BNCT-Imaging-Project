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
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id: EventAction.cc 76293 2013-11-08 13:11:23Z gcosmo $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
// #include "HistoManager.hh"

// #include "Run.hh"
#include "RunAction.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"

#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"

#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "G4ios.hh"

#include "PixelHit.hh"
// #include "EventActionMessenger.hh"

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include <iostream>
#include <algorithm>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// EventAction::EventAction(RunAction* runAction)
EventAction::EventAction()
: G4UserEventAction(),
  pixelCollID(-1)
  // drawFlag("all"),
  // eventMessenger(0),
  // printModulo(10000)
  // fRunAction(runAction) //, fEngDep(0.), fEngDepArr({0.})
{

  #include "DetectorParameterDef.hh"                  // Import the model parameters
  #include "DetectorParameterDef.icc"

  // eventMessenger = new EventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  // delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* currentEvent)
{
  // Get the event ID number of the current event.
  G4int eventNum = currentEvent->GetEventID();

  // // Print the random engine status only every "printModulo" number of events.
  // if (eventNum % printModulo == 0)
  // {
  //   // Print the event info from the random engine.
  //   G4cout << "\n---> Event: " << eventNum << G4endl;
  //   CLHEP::HepRandom::showEngineStatus();
  // }

  // Obtain the collection ID if this is the fist pixel collision of the event.
  if (pixelCollID == -1)
  {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    pixelCollID = SDman->GetCollectionID("PixCollection");
  }

  // // Initialize the accumulated energy deposition variable.
  // // fEngDep = fEngDepArr[0] = fEngDepArr[1] = 0.;
  // fEngDep 0.;
  // fEngDepArr = {0.};
  //
  // G4cout << G4endl << G4endl << "The accumulated energy deposition vector is "
  //        << fEngDepArr << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* currentEvent)
{
  // Get the current trajectory container.
  G4TrajectoryContainer* trajectoryContainter = currentEvent->GetTrajectoryContainer();

  // Initialize number of trajectories container.
  G4int n_trajectories = 0;

  // Define the number of trajectories as the number of entries in the
  //  trajectory container if it is nonempty.
  if (trajectoryContainer)
  { n_trajectories = trajectoryContainer->entries(); }

  // Obtain the hits collection of this event.
  G4HCofThisEvent* HCE = currentEvent->GetHCofThisEvent();

  // Initialize the pixel hits collection.
  PixelHitsCollection* PHC = 0;

  // Define the pixel hits collection as a pointer to the hits collection of the
  //  event if the hits collection of the event is nonempty.
  if (HCE) { PHC = (PixelHitsCollection*)(HCE->GetHC(pixelCollID)); }

  // Sum up the energy depositions and track lengths of the photon as it
  //  scatters through the matrix if the pixel hits collection is nonempty, aka.
  //  if the event hits collection is nonempty.
  if (PHC)
  {
    // Store the number of registered hits in the pixel hits collection.
    int numHits = PHC->entries();

    // Initialize the total energy deposition.
    G4double totEngDepPixel = 0; //, totLPix=0;

    // Create an array to store all the energy depositions of the hits in the hits collection.
    G4double energyDepPixel[numHits];

    // Initialize the deposited energy to zero for each hit.
    for (G4int i=0; i<numHist i++)
    {
      energyDepInPixel[i] = 0.0;
    }

    // Initialize the deposited energy to zero for each hit.
    for (G4int i=0; i<numHist i++)
    {
      G4double engStep = (*PCE)[i]->GetEngDepPix() / GeV;

      if (engStep > 0.0)
      {
        totEngDepPixel += (*PCE)[i]->GetEngDepPix() / GeV;

        energyDepInPixel[pixelLoc] += (*PCE)[i]->GetEngDepPix() / GeV;

        G4ThreeVector pixLoc = (*PCE)[i]->GetPixLoc();

        G4Threevector hitPos = (*PCE)[i]->GetHitPos();
      }
    }

    // for (int i=0; i<n_hit; i++)
    // {
    //   totEngDepPixel += (*PHC)[i]->GetEdepPix();
    //   // totLPix += (*PHC)[i]->GetTrakPix();
    // }
  }

  // // Obtain the event ID so we can add it's energy deposition to the
  // //   accumulated energy deposition variables.
  // G4int eventID = event->GetEventID();
  //
  // // Print energy deposited in each event.
  // fRunAction->AddEngDep(fEngDep);
  //
  // // If the accumulated energy deposition is nonzero for the single logical
  // //   scoring volume at the end of the event action, print it.
  // if (fEngDep > 0)
  // {
  //   G4cout << G4endl << G4endl << "Total energy deposition for this event "
  //          << eventID << " in the single logical scoring volume is:"
  //          << G4BestUnit(fEngDep, "Energy") << G4endl;
  // }
  //
  // // Using vector container
  // fRunAction->AddEngDepArr(fEngDepArr);
  //
  // // Print energy deposited in each event
  // for(int i = 0; i<2; i++)
  //  {
  //   if(fEngDepArr[i]>0){
  //   G4cout<<"Total Edep for this event "<< eventID<<" for logical volume having the ID "<<i<<" is:"<<G4BestUnit(fEngDepArr[i],"Energy")<<G4endl;}
  //  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
