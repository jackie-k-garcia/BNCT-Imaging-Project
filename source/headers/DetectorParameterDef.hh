// File to store parameter variables for gamma camera construction.

// Sizes
G4double           WorldSizeX;
G4double           WorldSizeY;
G4double           WorldSizeZ;

G4double           TumorDiameter;
G4double           TumorLength;
G4ThreeVector      TumorDisplacement;

G4double           BodyDiameter;
G4double           BodyLength;

G4double           ScintCrystalHeight;
G4double           ScintCrystalWidth;
G4double           ScintCrystalThickness;

G4double           CollimBladeHeight;
G4double           CollimBladeWidth;
G4double           CollimBladeThickness;

G4double           PMTPixelDiameter;
G4double           PMTPixelThickness;

// Array dimensions (in pixels in each direction and the number of such arrays, IN GENERAL)
G4int              PixelNbX;
G4int              PixelNbY;
G4int              PixelNbM;

G4int              ScintNbX = 64;
G4int              ScintNbY = 32;
G4int              ScintNbM = 1;

G4int              CollimNbS;     // Collimator blade subset to be parametrized into an array
G4int              CollimNbX;
G4int              CollimNbY;
G4int              CollimNbM;

G4int              PMTNbX;
G4int              PMTNbY;
G4int              PMTNbM;

// Sizes addendum
G4double           ScintArrayWidth;
G4double           ScintArrayHeight;
G4double           ScintArrayThickness;

G4double           CollimArrayWidth;
G4double           CollimArrayHeight;
G4double           CollimArrayThickness;

G4double           PMTArrayWidth;
G4double           PMTArrayHeight;
G4double           PMTArrayThickness;

G4double           ScintArrayDisplacement;
G4double           CollimArrayDisplacement;
G4double           PMTArrayDisplacement;
