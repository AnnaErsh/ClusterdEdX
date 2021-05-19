#include "DetectorConstruction.h"
#include "ConfigArray.h"

#include <cmath>

#include "G4Material.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"
#include "G4Region.hh"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"


DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

// Materials
G4double A, Z, density;
    
G4Element* H = 
new G4Element("Hydrogen", "H", Z=1., A=1.01*g/mole);
G4Element* C = 
new G4Element("Carbon", "C", Z=6., A=12.01*g/mole);
G4Element* Ar = 
new G4Element("Argon", "Ar", Z=18., A=40.*g/mole);
G4Element* N = 
new G4Element("Nitrogen", "N", Z=7., A=14.01*g/mole);
G4Element* O = 
new G4Element("Oxygen", "O", Z=8., A=16.*g/mole);
G4Element* Fe =
    new G4Element("Iron", "Fe", Z=26., A=55.85*g/mole);

G4Material* Vacuum =
    new G4Material("Vacuum", density=universe_mean_density, 1);
Vacuum->AddElement(H, 1);
G4Material* Air = 
    new G4Material("Air", density=1.293*mg/cm3, 3);
Air->AddElement(N, 75.5*perCent);
Air->AddElement(O, 23.2*perCent);
Air->AddElement(Ar, 1.3*perCent);

G4Material* Iron =
    new G4Material("Iron", density=7.8*g/cm3, 1);
Iron->AddElement(Fe, 1);

// density was taken from here
// https://indico.cern.ch/event/716539/contributions/3245948/attachments/1798384/2933344/VCI2019_PARSA.pdf
G4Material* CH =
    new G4Material("CH", density=0.97*g/cm3, 2);
CH->AddElement(C, 1);
CH->AddElement(H, 1);

// Solids
G4RotationMatrix NoRot_sol;

G4Box* World_sol =
new G4Box("World_sol", 1000.*cm, 1000.*cm, 1550.*cm);

G4Box* CH_sol =
new G4Box("CH_sol", World_sol->GetXHalfLength()-50*cm, World_sol->GetYHalfLength()-50*cm, World_sol->GetZHalfLength()-50.*cm);

// Logical Volumes
// Colours and attributes for visualisation
const G4Colour Cyan(0.0, 1.0, 1.0);
const G4Colour Red(1.0, 0.0, 0.0);
const G4bool Invisible=false;

G4VisAttributes* VisInv = new G4VisAttributes(Invisible); // Invisible mode
G4VisAttributes* VisCyan = new G4VisAttributes(Cyan);
G4VisAttributes* VisRed = new G4VisAttributes(Red);

// Logical Volumes
G4LogicalVolume* World_log = 
new G4LogicalVolume(World_sol, Vacuum, "World_log");
World_log->SetVisAttributes(VisRed); 

G4Region* DetectorRegion = new G4Region("DetectorRegion");

G4LogicalVolume* CH_log = 
    new G4LogicalVolume(CH_sol, CH, "CH_log");
CH_log->SetVisAttributes(VisCyan);
CH_log->SetRegion(DetectorRegion);
    
// Physical Volumes
G4RotationMatrix NoRot;

World = new G4PVPlacement(G4Transform3D(NoRot, G4ThreeVector(0., 0., 0.)), 
    World_log, "World", 0, false, 0);

CH_block = new G4PVPlacement(G4Transform3D(NoRot, G4ThreeVector(0.*cm, 0., 0.)), 
    CH_log, "CH_block", World_log, false, 0);

return World;
}



