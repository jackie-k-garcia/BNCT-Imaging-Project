// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
// Detector Construction Class
//
// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include <vector>
// #include "G4Cache.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4MultiFunctionalDetector;

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    // Define the constructor and destructor methods for this class.
    DetectorConstruction();
    virtual ~DetectorConstruction();

    // Define a method to construct the geometry.
    virtual G4VPhysicalVolume* Construct();

    // Define a method to return a single chosen scoring volume in the simple
    //  scoring calculation.
    G4LogicalVolume* GetScoringVolume const {return fScoringVolume;}

    // Define a method to return the vector of scoring volumes given in the
    //  in-depth scoring calculation.
    std::vector<G4LogicalVolume*> GetScoringVolume() const
    {
      return fScoringVolumeVec;
    }

    // Return the number of elements in the scoring volume vector.
    G4int GetScoreVolVecSize() const {return fScoringVolumeVec.size();}

    // Construct the sensitive detectors and electromagnetic fields through them,
    //  if desired.
    void ConstructSDandField();

  private:

    // Create a G4Material pointer for the world material.
    G4Material*                        fWorldMaterial;

    // Create a G4VPhysicalVolume pointer for the world volume.
    G4VPhysicalVolume*                 fPhysicalWorld;

    // Create a G4LogicalVolume pointer for the scoring volume.
    G4LogicalVolume*                   fScoringVolume;

    // Create a vector of G4LogicalVolume pointers to store the scoring volume
    //  vector.
    std::vector<G4LogicalVolume*>    fScoringVolumeVec;

    // Create a private method to define materials for the simulation.
    void DefineMaterials();

    // Create a G4PhysicalVolume pointer for the
}
