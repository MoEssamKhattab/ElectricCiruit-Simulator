#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\UI\UI.h"
#include "Connection.h"
#include <fstream>


//Base class for all components (resistor, capacitor,....etc) .
class Component
{
private:
	string m_Label;
	
protected:
	int value;
	int id = (Ccount + 1);
	//Each component has two ending terminals (term1, term2)
	double term1_volt, term2_volt;	//voltage at terminals 1&2

	bool selected = false;

	//Each terminal is connected to set of connections
	Connection *term1_connections[MAX_CONNS]; //list of pointers to connections
	Connection *term2_connections[MAX_CONNS];

	int term1_conn_count;	//actual no. of connections to each terminal
	int term2_conn_count;


	GraphicsInfo *m_pGfxInfo;	//The parameters required to draw a component

public:
	static int Ccount;

	enum comptype {
		RES,
		SWT,
		BAT,
		BLB,
		GND,
		MOD
	};



	Component(GraphicsInfo *r_GfxInfo);
	//void setTerm1Volt(double v);		//sets the voltage at terminal1
	//void setTerm2Volt(double v);		//sets the voltage at terminal2
	//double getTerm1Volt();				//returns the voltage at terminal1
	//double getTerm2Volt();				//returns the voltage at terminal2

	virtual void Operate() = 0;	//Calculates the output voltage according to the inputs
	virtual void Draw(UI* ) = 0;	//for each component to Draw itself
	
	virtual void SetValue(int v);
	virtual int GetValue();
	
	//virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	//virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	bool getSelected();
	void setSelected(bool sel);
	//virtual void setlabel(string label);
	//virtual string getlabel();
	virtual Component* createcopy() = 0;

	virtual void save(ofstream& savefile) = 0;
	virtual void load(ifstream& loadfile) = 0;

	GraphicsInfo* getGraphicsInfo();

	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif