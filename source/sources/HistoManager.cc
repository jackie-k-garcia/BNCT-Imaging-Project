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
/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// $Id: HistoManager.cc 98265 2016-07-04 17:47:54Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
// #include "DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"
// #include "G4AnalysisManager.hh"
// #include "G4LogicalVolume.hh"
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// HistoManager::HistoManager(DetectorConstruction* det)
  // , fDetector(det), fScoringVolume1(0.)
HistoManager::HistoManager()
{
  #include "DetectorParameterDef.icc"

  // Initialize the histograms.
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile(filename);
  analysisManager->SetHistoDirectoryName(directory);
  // analysisManager->SetFileName(filename);
  // analysisManager->SetVerboseLevel(1);
  // analysisManager->SetActivation(true);     // Enable activation of histograms

  // Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  // Initialize the histograms.
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();

  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Initialize the histograms.
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // // Obtain the run manager.
  // Run* run = static_cast<Run*>(
  //       G4RunManager::GetRunManager()->GetNonConstCurrentRun());



  // // Define an array to store the title of each histogram.
  // const G4String title[] =
  //         {
  //           "Neutrons Leaving World"                          // ID = 0
  //           "Energy Deposition in Volume 1",                  // ID = 1
  //           "Energy Deposition in Volume 2",                  // ID = 2
  //         };

  // // Define the maximum number of histograms as the number of elements in
  // //  the title array. The numerator gives the total number of bytes used to
  // //  hold the array in memory. The denominator gives the number of bytes
  // //  used to hold the one element of the array in memory (the first).
  // const G4int kMaxHisto = sizeof(title) / sizeof(*title);

  // // Initialize an array to hold the histogram IDs.
  std::string title[PixelNbX][PixelNbY][PixelNbM];

  // const G4String title[PixelNbX][PixelNbY][PixelNbM];
  //
  // Fill the histogram ID array.
  for (int i=0; i<PixelNbX; i++)
  {
    for (int j=0; j<PixelNbY; j++)
    {
      for (int k=0; k<PixelNbM; k++)
      {

        // // Create a temporary, dynamic pointer to hold the string version of
        // //  the histogram ID.
        // std::string* temp_ptr = new std::string;
        //
        // // Set the temporary pointer's dereference value equal to the string
        // //  version of the histogram ID currently chosen by the for loop
        // //  iterator.
        // *temp_ptr = std::to_string(i);
        //
        // // Dynamically cast the temporary pointer to a G4String reference
        // //  object and set the casted reference equal to the reference of the
        // //  ID array element currently chosen by the for loop iterator.
        // &id[i] = dynamic_cast<G4String*> (temp_ptr);

        title[i][j][k] = "Pixel at Location(" + std::to_string(i) + ", "
        + ", " + std::to_string(j) + ", "
        + ", " + std::to_string(k) + ")";

        // Release the memory held by the temporary pointer.
        // delete temp_ptr;
      }
    }
  }
  // const G4String id[] = {"0", "1", "2","3", "4", "5", "6", "7", "8"};

  // // Bin parameters
  // G4int nbins = 1000;    // For a set energy window, affects energy width
  //                       //   of each bin
  // G4double x_min = 0.;  // Minimum value on the x-axis (MeV)
  // G4double y_min = 3.;  // Minimum value on the y-axis (MeV)

  // // G4int ih = analysisManager->CreateH3(id[k], title[k], nbins, x_min, y_min);
  // analysisManager->CreateNtuple("Data - Detector Array 1", "Energy Deposition per Pixel per Event");
  // analysisManager->CreateNtupleDColumn("Energy Deposition (MeV)");
  // analysisManager->CreateNtupleIColumn("PMT Plane (1 or 2, each shifted)");
  // analysisManager->CreateNtupleIColumn("x-pixel location");
  // analysisManager->CreateNtupleIColumn("y-pixel location");
  // analysisManager->CreateNtupleIColumn("z-pixel location");
  // analysisManager->FinishNtuple();


  // Iterate through and create all histograms.
  for (int i=0; i<PixelNbX; i++)
  {
    for (int j=0; j<PixelNbY; j++)
    {
      for (int k=0; k<PixelNbM; k++)
      {
        G4int ih = analysisManager->CreateH1(title[i][j][k], "Gamma Spectrum",
        numBins, engMin, engMax, "keV");

        analysisManager->SetH1Activation(ih, true);
      }
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
