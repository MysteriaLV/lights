#pragma once

#include <Automaton.h>

class Atm_lights: public Machine {

 public:
  enum { OFF, DIM, ALARM, FLICKERING, FULL }; // STATES
  enum { EVT_OFF, EVT_DIM, EVT_ALARM, EVT_FLICKER, EVT_FULL, ELSE }; // EVENTS
  Atm_lights( void ) : Machine() {};
  Atm_lights& begin( void );
  Atm_lights& trace( Stream & stream );
  Atm_lights& trigger( int event );
  int state( void );
  Atm_lights& off( void );
  Atm_lights& dim( void );
  Atm_lights& alarm( void );
  Atm_lights& flicker( void );
  Atm_lights& full( void );

 private:
  enum { ENT_OFF, ENT_DIM, ENT_ALARM, ENT_FLICKERING, ENT_FULL }; // ACTIONS
  int event( int id ); 
  void action( int id ); 

};

extern Atm_lights atm_lights;

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_lights">
    <states>
      <OFF index="0" on_enter="ENT_OFF">
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_FULL>FULL</EVT_FULL>
      </OFF>
      <DIM index="1" on_enter="ENT_DIM">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_FULL>FULL</EVT_FULL>
      </DIM>
      <ALARM index="2" on_enter="ENT_ALARM">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_FULL>FULL</EVT_FULL>
      </ALARM>
      <FLICKERING index="3" on_enter="ENT_FLICKERING">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FULL>FULL</EVT_FULL>
      </FLICKERING>
      <FULL index="4" on_enter="ENT_FULL">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
      </FULL>
    </states>
    <events>
      <EVT_OFF index="0" access="PUBLIC"/>
      <EVT_DIM index="1" access="PUBLIC"/>
      <EVT_ALARM index="2" access="PUBLIC"/>
      <EVT_FLICKER index="3" access="PUBLIC"/>
      <EVT_FULL index="4" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

