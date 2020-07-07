# Geant4_skeleton
Sekelton for geant4 example
Si tratta di uno scheletro molto semplificato tratto da TestEm4 

Note sull'utilizzo dei file sorgenti

  --> ActionInitialization iniziallizza tutti i moduli (RunAction, SteppingAction, TrackingAction...) 
  
              	SetUserAction(new RunAction);
                    --> Su RunAction crei le ntuple per root usando i metodi dell'Analysis manager
  
  	 	PrimaryGeneratorAction *primGen = new PrimaryGeneratorAction;
                    --> PrimaryGeneratorAction da riempire con i dettagli del particle gun
              
	      SetUserAction(primGen);
	      
              EventAction* eventAction = new EventAction();
                    --> EventAction ad ogni evento cancella le variabili e riempie le ntuple
		    
              SetUserAction(eventAction);
	      
              SetUserAction(new SteppingAction(eventAction,primGen));
                    --> Stepping Action per studiare il passaggio delle particelle negli strati di materiale
		    
              SetUserAction(new TrackingAction );
                    --> Usare tracking action per accedere ad esempio all' energia cinetica associata alle tracce
    
    --> PhysicsList va riempito con la "fisica da accendere"
    --> DetectorConstruction va riempito con la geometria 
	
    
    
    
