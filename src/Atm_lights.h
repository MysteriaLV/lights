#pragma once

#include <Automaton.h>

class Atm_lights: public Machine {

 public:
  enum { OFF, DIM, DIM_WITH_TABLE, ALARM, FLICKERING, NORMAL, MAINTENACE }; // STATES
  enum { EVT_OFF, EVT_DIM, EVT_POWER_CONSOLE_CONNECTED, EVT_ALARM, EVT_FLICKER, EVT_NORMAL, EVT_MAINTENACE, ELSE }; // EVENTS
  Atm_lights( void ) : Machine() {};
  Atm_lights& begin( void );
  Atm_lights& trace( Stream & stream );
  Atm_lights& trigger( int event );
  int state( void );
  Atm_lights& off( void );
  Atm_lights& dim( void );
  Atm_lights& power_console_connected( void );
  Atm_lights& alarm( void );
  Atm_lights& flicker( void );
  Atm_lights& normal( void );
  Atm_lights& maintenace( void );

 private:
  enum { ENT_OFF, ENT_DIM, ENT_DIM_WITH_TABLE, ENT_ALARM, ENT_FLICKERING, ENT_NORMAL, ENT_MAINTENACE }; // ACTIONS
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
        <EVT_POWER_CONSOLE_CONNECTED>DIM_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </OFF>
      <DIM index="1" on_enter="ENT_DIM">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_POWER_CONSOLE_CONNECTED>DIM_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </DIM>
      <DIM_WITH_TABLE index="2" on_enter="ENT_DIM_WITH_TABLE">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </DIM_WITH_TABLE>
      <ALARM index="3" on_enter="ENT_ALARM">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </ALARM>
      <FLICKERING index="4" on_enter="ENT_FLICKERING">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </FLICKERING>
      <NORMAL index="5" on_enter="ENT_NORMAL">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </NORMAL>
      <MAINTENACE index="6" on_enter="ENT_MAINTENACE">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>DIM</EVT_DIM>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_FLICKER>FLICKERING</EVT_FLICKER>
        <EVT_NORMAL>NORMAL</EVT_NORMAL>
      </MAINTENACE>
    </states>
    <events>
      <EVT_OFF index="0" access="PUBLIC"/>
      <EVT_DIM index="1" access="PUBLIC"/>
      <EVT_POWER_CONSOLE_CONNECTED index="2" access="PUBLIC"/>
      <EVT_ALARM index="3" access="PUBLIC"/>
      <EVT_FLICKER index="4" access="PUBLIC"/>
      <EVT_NORMAL index="5" access="PUBLIC"/>
      <EVT_MAINTENACE index="6" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

