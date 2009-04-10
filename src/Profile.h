// Profile.h
/*
 * Copyright (c) 2009, Dan Heeks
 * This program is released under the BSD license. See the file COPYING for
 * details.
 */

#include "HeeksCNCTypes.h"
#include "DepthOp.h"

class CProfile;

class CProfileParams{
public:
	int m_tool_on_side; // -1=right, 0=on, 1=left

	// these are only used when m_sketches.size() == 1
	bool m_auto_roll_on;
	bool m_auto_roll_off;
	double m_roll_on_point[3];
	double m_roll_off_point[3];
	bool m_start_given;
	bool m_end_given;
	double m_start[3];
	double m_end[3];

	CProfileParams();

	void set_initial_values();
	void write_values_to_config();
	void GetProperties(CProfile* parent, std::list<Property *> *list);
	void WriteXMLAttributes(TiXmlNode* pElem);
	void ReadFromXMLElement(TiXmlElement* pElem);
};

class CProfile: public CDepthOp{
public:
	std::list<int> m_sketches;
	CProfileParams m_profile_params;

	CProfile(){}
	CProfile(const std::list<int> &sketches):m_sketches(sketches){m_profile_params.set_initial_values();}

	// HeeksObj's virtual functions
	int GetType()const{return ProfileType;}
	const wxChar* GetTypeString(void)const{return _T("Profile");}
	void glCommands(bool select, bool marked, bool no_color);
	wxString GetIcon(){if(m_active)return theApp.GetDllFolder() + _T("/icons/profile"); else return CDepthOp::GetIcon();}
	void GetProperties(std::list<Property *> *list);
	void GetTools(std::list<Tool*>* t_list, const wxPoint* p);
	HeeksObj *MakeACopy(void)const;
	void CopyFrom(const HeeksObj* object);
	void WriteXML(TiXmlNode *root);
	bool CanAddTo(HeeksObj* owner);

	void WriteSketchDefn(HeeksObj* sketch, int id_to_use = 0);
	void AppendTextForOneSketch(HeeksObj* object, int sketch);
	void AppendTextToProgram();
	void GetRollOnPos(HeeksObj* sketch, double &x, double &y);
	void GetRollOffPos(HeeksObj* sketch, double &x, double &y);

	static HeeksObj* ReadFromXMLElement(TiXmlElement* pElem);
};
