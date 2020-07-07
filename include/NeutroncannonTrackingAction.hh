
#ifndef NeutroncannonTrackingAction_h
#define NeutroncannonTrackingAction_h

#include "G4UserTrackingAction.hh"

#include "globals.hh"

class NeutroncannonTrackingAction : public G4UserTrackingAction {

public:
    NeutroncannonTrackingAction();
    virtual ~NeutroncannonTrackingAction(){}

    virtual void PreUserTrackingAction(const G4Track *aTrack);
    virtual void PostUserTrackingAction(const G4Track *aTrack);

};

#endif

