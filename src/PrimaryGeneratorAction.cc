#include "PrimaryGeneratorAction.h"
#include "ConfigArray.h"
#include "EventAction.h"

#include "G4ParticleTypes.hh"
#include "G4IonTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "TF1.h"

#include <cmath>

PrimaryGeneratorAction::PrimaryGeneratorAction(RunAction* runact, EventAction* evtact)
{
runaction=runact;
eventaction=evtact;

ParticleGun = new G4GeneralParticleSource();

G4SPSPosDistribution* PositionDist = ParticleGun->GetCurrentSource()->GetPosDist();
G4SPSEneDistribution* EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();

G4ThreeVector SourcePosition;

switch (Config.GetSourceType())
	{
	case 1: // D source
	{
		ParticleGun->SetParticleDefinition(G4Deuteron::DeuteronDefinition());
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	case 2: // T source
	{
		ParticleGun->SetParticleDefinition(G4Triton::TritonDefinition());
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	case 3: // alpha source
	{
		ParticleGun->SetParticleDefinition(G4Alpha::AlphaDefinition());
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	case 4: // proton source
	{
		ParticleGun->SetParticleDefinition(G4Proton::ProtonDefinition());
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	case 5: // He3 source
	{
		G4int Z = 2, A = 3, Estar = 0 * keV;
		G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, Estar);
		ParticleGun->SetParticleDefinition(ion);
		ParticleGun->SetParticleCharge(2.0*eplus);
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	case 6: // mu source
	{
		ParticleGun->SetParticleDefinition(G4MuonMinus::MuonMinusDefinition());
		EnergyDist->SetEnergyDisType("Mono");
		PositionDist->SetPosDisType("Point"); 
		PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0*cm, -1000.*cm));
	break;
	}
	default:
	G4cerr << "Unknown source type!\n";
	}

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
delete ParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	G4SPSEneDistribution* EnergyDist;

	G4double Energy = 0.;
	G4ThreeVector Position(0., 0., 0.);
	G4ThreeVector Direction(0., 0., 0.);
	G4SPSAngDistribution* AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
	switch (Config.GetSourceType())
	{
		case 1: // D source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

	    // Energy generation
	    TF1* energy = new TF1 ("energy", "exp([0]+[1]*x)+exp([2]+[3]*x)", 0.5, 300.);
		  EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
		  {
	      G4double EnergyProb;
	      energy->SetParameter( 0, -11.48);
	      energy->SetParameter( 1, -0.005137);
	      energy->SetParameter( 2, -3610);
	      energy->SetParameter( 3, 3.816);
	      G4double max = energy->GetMaximum(0.5, 300);
	      do
	      {
	        Energy = 0.5 + 299.5 * G4UniformRand();
	        EnergyProb = (1. / (max * 1.01)) * energy->Eval(Energy);
	      } while (EnergyProb < G4UniformRand());
		  }
		  EnergyDist->SetMonoEnergy(Energy*MeV);
		  delete energy;
		}
		break;
		 
		case 2: // T source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

			// Energy generation
	    TF1* energy = new TF1 ("energy", "exp([0]+[1]*x)+exp([2]+[3]*x)", 0.5, 200.);
		  EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
		  {
	      G4double EnergyProb;
	      energy->SetParameter( 0, -12.32);
	      energy->SetParameter( 1, -0.004891);
	      energy->SetParameter( 2, -3446);
	      energy->SetParameter( 3, 5.729);
	      G4double max = energy->GetMaximum(0.5, 200);
	      do
	      {
	        Energy = 0.5 + 199.5 * G4UniformRand();
	        EnergyProb = (1. / (max * 1.01)) * energy->Eval(Energy);
	      } while (EnergyProb < G4UniformRand());
		  }
		  EnergyDist->SetMonoEnergy(Energy*MeV);
		  delete energy;
		}
		break;

		case 3: // alpha source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

			// Energy generation
	    TF1* energy = new TF1 ("energy", "exp([0]+[1]*x)+exp([2]+[3]*x)", 0.5, 150.);
		  EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
		  {
	      G4double EnergyProb;
	      energy->SetParameter( 0, -2.493);
	      energy->SetParameter( 1, -0.03745);
	      energy->SetParameter( 2, -9.473);
	      energy->SetParameter( 3, -0.03745);
	      G4double max = energy->GetMaximum(0.5, 150);
	      do
	      {
	        Energy = 0.5 + 149.5 * G4UniformRand();
	        EnergyProb = (1. / (max * 1.01)) * energy->Eval(Energy);
	      } while (EnergyProb < G4UniformRand());
		  }
		  EnergyDist->SetMonoEnergy(Energy*MeV);
		  delete energy;
		}
		break;

		case 4: // proton source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

			// Energy generation
	    TF1* energy_high = new TF1 ("energy_high", "pol3", 20, 500.);
	    TF1* energy_low = new TF1 ("energy_low", "pol2", 0, 20.);
		  EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();

		  if(G4UniformRand() < 0.055) // energy below 20 MeV
		  {
	      G4double EnergyProb;
	      energy_low->SetParameter(0, 6.586);
			  energy_low->SetParameter(1, 29.99);
			  energy_low->SetParameter(2, -0.9686);
	      G4double max = energy_low->GetMaximum(0., 20);
	      do
	      {
	        Energy = 20 * G4UniformRand();
	        EnergyProb = (1. / (max * 1.01)) * energy_low->Eval(Energy);
	      } while (EnergyProb < G4UniformRand());
		  }
		  else
		  {
		  	G4double EnergyProb;	
	      energy_high->SetParameter(0, 6598);
			  energy_high->SetParameter(1, -21.35);
			  energy_high->SetParameter(2, 0.01366);
			  energy_high->SetParameter(3, 9.246E-6);
	      G4double max = energy_high->GetMaximum(20, 500);
	      do
	      {
	        Energy = 20 + 480 * G4UniformRand();
	        EnergyProb = (1. / (max * 1.01)) * energy_high->Eval(Energy);
	      } while (EnergyProb < G4UniformRand());
		  }
		  EnergyDist->SetMonoEnergy(Energy*MeV);
		  // G4cerr<<Energy<<G4endl;
		  delete energy_low;
		  delete energy_high;
		}
		break;

		case 5: // He3 source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

			// Energy generation
			TF1* energy = new TF1 ("energy", "exp([0]+[1]*x)+exp([2]+[3]*x)", 0.5, 150.);
			EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
			{
				G4double EnergyProb;
				energy->SetParameter( 0, 4.235);
				energy->SetParameter( 1, -0.03479);
				energy->SetParameter( 2, 5.762);
				energy->SetParameter( 3, -0.034);	
				G4double max = energy->GetMaximum(0.5, 150);
				do
				{

					Energy = 0.5 + 149.5 * G4UniformRand();
					EnergyProb = (1. / (max * 1.01)) * energy->Eval(Energy);
				} while (EnergyProb < G4UniformRand());
			}
			EnergyDist->SetMonoEnergy(Energy*MeV);
					  // G4cerr<<Energy<<G4endl;

			delete energy;
		}
		break;

		case 6: // mu source
		{
			AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
			AngularDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

			// Energy generation
			TF1* energy = new TF1 ("energy", "landau", 0.5, 2000.);
			EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
			{
				G4double EnergyProb;
				energy->SetParameter( 0, 7.88650e+04);
				energy->SetParameter( 1, 2.54808e+02);
				energy->SetParameter( 2, 8.39547e+01);
				G4double max = energy->GetMaximum(0.5, 2000);
				do
				{
					Energy = 0.5 + 1999.5 * G4UniformRand();
					EnergyProb = (1. / (max * 1.01)) * energy->Eval(Energy);
				} while (EnergyProb < G4UniformRand());
			}
			EnergyDist->SetMonoEnergy(Energy*MeV);
			// G4cerr<<Energy<<G4endl;

			delete energy;
		}
		break;

		default:
			G4cerr << "Unknown source type!\n";
	}

	// Generate primary vertex
	ParticleGun->GeneratePrimaryVertex(event);

	// Transferring data for NTuple
	eventaction->SetParticleEnergy(ParticleGun->GetParticleEnergy());
	eventaction->SetParticlePosition(ParticleGun->GetParticlePosition());
	eventaction->SetParticleMomentumDirection(ParticleGun->GetParticleMomentumDirection());
}
