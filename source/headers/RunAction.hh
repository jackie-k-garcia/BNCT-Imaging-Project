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
/// \file RunAction.hh
/// \brief Definition of the RunAction class
//
// $Id: RunAction.hh 66241 2012-12-13 18:34:42Z gunter $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ios.hh"
// #include "G4Accumulable.hh"


#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4ThreeVector.hh"

#include "iomanip"
#include <assert.h>
#include "iostream"
#include "fstream"
#include "functional"
#include "set"
#include "sstream"
#include <vector>
#include <streambuf>

class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
  public:

    // Define the constructor for the run action.
    RunAction();
    // RunAction(const G4String&);

    // Define the destructor for the run action.
    virtual ~RunAction();

    // // Define a method to generate a new run.
    // virtual G4Run* GenerateRun() {return new Run;};

    // Define the beginning of the run action, in which initialization of the
    //   energy deposition accumulables and the histogram analysis manager
    //   occurs.
    virtual void BeginOfRunAction(const G4Run* aRun);

    // Define the end of the run action, in which saving of the ROOT file,
    //   dumping of the fluence data, merging of the energy deposition
    //   accumulables, and calculation of the root-mean-squared (RMS) energy
    //   deposition occurs.
    virtual void EndOfRunAction(const G4Run* aRun);

    void fillPerHit(G4ThreeVector, G4double, G4int);
    // void fillPerHit(G4ThreeVector, G4double, G4int = 0);
    // void fillPerHit(G4ThreeVector, G4double = 0.0, G4int);
    // void fillPerHit(G4ThreeVector = G4ThreeVector(), G4double = 0.0, G4int = 0);

    // void AddEngDep (G4double&);
    // void AddEngDepArr (G4double (&engDep)[2]);

  private:

    #include "DetectorParameterDef.hh"                // Import the gamma camera parameters

    // Create the file to store the hit data.
    std::ofstream outputDataFile;

    G4int runID;

    // G4int         IDinX;
    // G4int         IDinY;
    // G4int         IDinM;
    // G4int         Multiplicity;
    // G4double      PixelEnergy;
    // G4double      TotalPixelEnergy;
    G4double      InitEnergy;
    G4double      totEngDep;
    G4int         EventNumber;
    // G4int         Detected;
    // G4int         FullyDetected;
    // G4int         NbOfDoubles;

    // // Create ordinary accumulables for energy deposition for the case of only
    // //   one scoring logical volume.
    // G4Accumulable<G4double> fEngDep;
    // G4Accumulable<G4double> fEngDepSqr;
    //
    // // Define vectors to store the accumulables for the case of multiple
    // //   scoring logical volumes. CHANGE THE DEFAULT NUMBER OF SCORING
    // //   VOLUMES TO THAT DEFINED BY SOME CUSTOM METHOD CALLING A PRIVATE
    // //   VARIABLE IN THE DETECTOR CONSTRUCTION CLASS.
    // std::vector< G4Accumulable<G4double> > fEngDepArr;
    // std::vector< G4Accumulable<G4double> > fEngDepSqrArr;

    // // Reserve the number of scoring logical volumes for memory for the energy
    // //   deposit arrays.
    // fEngDepArr.reserve(2);
    // fEngDepSqrArr.reserve(2);

    // G4String fOutputFileSpec;
};

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// void RunAction::fillPerHit(G4int eventStep, G4double hitEnergy, G4ThreeVector pixLoc)
// {
//   static G4int EventNumber = 0;
//   // static G4int Multiplicity = 0;
//
//   // static G4double initEnergy = 0;
//   static G4double totalEngDep = 0;
//
//   // EventNumber++;
//
//   /*** Writing to Data File ***/
//
//   // BEGINNING OF EVENT: Increment event number
//   if (eventStep == -1)
//   {
//     // IDinX = 0;
//     // IDinY = 0;
//     EventNumber++;
//   }
//
//   // END OF EVENT: Writing to data file
//   else if (eventStep == 1)
//   {
//
//     // if (TotalPixelEnergy == InitEnergy) { FullyDetected++; }
//
//     // if (TotalPixelEnergy > 20*keV) { Detected++; }
//
//     // Open the data file for writing and name it.
//     outputDataFile.open("gammacameradata");
//
//     // Fill the output data file.
//     outputDataFile << " Source Photon #:   " << EventNumber                             // << G4endl
//                    << " Position:          "
//                    << pixLoc.x() << " " << pixLoc.y() << " " << pixLoc.Z()
//                    << " Energy Deposition: " << totalEngDep;                               // << G4endl
//                   //  << " Fully Detected:  " << FullyDetected;
//     // outputDataFile << "Detected: " << Detected << G4endl; << " Fully Detected: " << FullyDetected;
//
//     // Close the output data file.
//     outputDataFile.close();
//
//     /*** Reseting the variables at the end of the current event ***/
//     totalEngDep = 0;
//     // Multiplicity = 0;
//
//   }
//
//   // DURING EVENT: Writing on File
//   else
//   {
//     // Multiplicity++;
//     //
//     // if (Multiplicity == 1) { InitEnergy=IDinX; }
//
//     totalEngDep = totalEngDep + hitEnergy;
//
//     // if (PixelEnergy > 20*keV)
//     // {
//     //   TotalPixelEnergy = TotalPixelEnergy + PixelEnergy;
//     // }
//
//     // // Print to screen the hit information.
//     // G4cout << "Initial Energy: " << InitEnergy
//     //        << " Energy: " << PixelEnergy << " Total: "
//     //        << TotalPixelEnergy << G4endl;
//
//   }
//
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
