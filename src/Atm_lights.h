#pragma once

#include <Automaton.h>

class Atm_lights: public Machine {

public:
    enum { OFF, NOPOWER, NOPOWER_WITH_TABLE, POWERED, LABLIGHT, ALARM, MAINTENACE }; // STATES
    enum { EVT_OFF, EVT_DIM, EVT_POWER_CONSOLE_CONNECTED, EVT_NORMAL, EVT_LABORATORY, EVT_ALARM, EVT_MAINTENACE, ELSE }; // EVENTS
    Atm_lights( void ) : Machine() {};
    Atm_lights& begin( void );
    Atm_lights& trace( Stream & stream );
    Atm_lights& trigger( int event );
    int state( void );
    Atm_lights& off( void );
    Atm_lights& dim( void );
    Atm_lights& power_console_connected( void );
    Atm_lights& normal( void );
    Atm_lights& laboratory( void );
    Atm_lights& alarm( void );
    Atm_lights& maintenace( void );

private:
    enum { ENT_OFF, ENT_NOPOWER, ENT_NOPOWER_WITH_TABLE, ENT_POWERED, ENT_LABLIGHT, ENT_ALARM, ENT_MAINTENACE }; // ACTIONS
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
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </OFF>
      <NOPOWER index="1" on_enter="ENT_NOPOWER">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </NOPOWER>
      <NOPOWER_WITH_TABLE index="2" on_enter="ENT_NOPOWER_WITH_TABLE">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </NOPOWER_WITH_TABLE>
      <POWERED index="3" on_enter="ENT_POWERED">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </POWERED>
      <LABLIGHT index="4" on_enter="ENT_LABLIGHT">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_ALARM>ALARM</EVT_ALARM>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </LABLIGHT>
      <ALARM index="5" on_enter="ENT_ALARM">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_MAINTENACE>MAINTENACE</EVT_MAINTENACE>
      </ALARM>
      <MAINTENACE index="6" on_enter="ENT_MAINTENACE">
        <EVT_OFF>OFF</EVT_OFF>
        <EVT_DIM>NOPOWER</EVT_DIM>
        <EVT_POWER_CONSOLE_CONNECTED>NOPOWER_WITH_TABLE</EVT_POWER_CONSOLE_CONNECTED>
        <EVT_NORMAL>POWERED</EVT_NORMAL>
        <EVT_LABORATORY>LABLIGHT</EVT_LABORATORY>
        <EVT_ALARM>ALARM</EVT_ALARM>
      </MAINTENACE>
    </states>
    <events>
      <EVT_OFF index="0" access="PUBLIC"/>
      <EVT_DIM index="1" access="PUBLIC"/>
      <EVT_POWER_CONSOLE_CONNECTED index="2" access="PUBLIC"/>
      <EVT_NORMAL index="3" access="PUBLIC"/>
      <EVT_LABORATORY index="4" access="PUBLIC"/>
      <EVT_ALARM index="5" access="PUBLIC"/>
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