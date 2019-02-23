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

  // analysisManager->SetFileName(filename);
  // analysisManager->SetVerboseLevel(1);
  // analysisManager->SetActivation(true);     // Enable activation of histograms

  // Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  // // Initialize the histograms.
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // analysisManager->Write();
  // analysisManager->CloseFile();

  // delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  #include "DetectorParameterDef.icc"

  // // Initialize the histograms.
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetActivation(true);

  analysisManager->SetVerboseLevel(1);

  analysisManager->SetFirstHistoId(1);

  // analysisManager->SetHistoDirectoryName(directory);
// histograms are always active
  analysisManager->OpenFile(filename);

  // // Initialize an array to hold the histogram IDs.
  G4int idTot = PMTNbX*PMTNbY*PMTNbM;

  G4String title[idTot];

  G4int titleID = 0;

  // const G4String title[PixelNbX][PixelNbY][PixelNbM];
  //
  // Fill the histogram ID array.
  for (int i=0; i<PixelNbX; i++)
  {
    for (int j=0; j<PixelNbY; j++)
    {
      for (int k=0; k<PixelNbM; k++)
      {
        titleID++;

        std::string titleTemp;

        titleTemp = "Pixel " + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k);

        title[titleID] = titleTemp;
      }
    }
  }

  titleID = 0;

  // Iterate through and create all histograms.
  for (int i=0; i<PixelNbX; i++)
  {
    for (int j=0; j<PixelNbY; j++)
    {
      for (int k=0; k<PixelNbM; k++)
      {
        titleID++;

        G4int ih = analysisManager->CreateH1(title[titleID], "Gamma Spectrum",
        numBins, engMin, engMax, "keV");

        // analysisManager->SetH1Activation(ih, true);
      }
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{
  // Initialize the histograms.
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n----> Output file is open in "
         << analysisManager->GetFileName() << "."
         << analysisManager->GetFileType() << G4endl;

  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int id, G4double engDep)
{
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->FillH1(id, engDep);
}
