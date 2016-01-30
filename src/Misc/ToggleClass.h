/*
 * ToggleClass.h
 *
 *  Created on: Jan 10, 2016
 *      Author: Colin
 */

#ifndef TOGGLECLASS_H
#define TOGGLECLASS_H

template <typename T>
class Toggle
{
private:
	T m_status;
	T m_toggleVal1;
	T m_toggleVal2;

	bool m_risingEdgeMem;
	bool m_fallingEdgeMem;

public:

	enum edgeType{
		KRisingEdge,
		KDualEdge,
		KFallingEdge,
	};

	//toggle1Val is the current value passed to the function being toggled between two values,
	//while toggle2Val will be the value returned after the first time the toggle runs, switching between
	//them on successive toggles.
	Toggle(T toggle1Val, T toggle2Val)
	{
		m_status = toggle1Val;
		m_toggleVal1 = toggle1Val;
		m_toggleVal2 = toggle2Val;

		m_risingEdgeMem = true;
		m_fallingEdgeMem = true;
	}

	bool risingEdge(bool varToEdgeCheck)
	{
		if(varToEdgeCheck){
				if(m_risingEdgeMem){
					m_risingEdgeMem = false;
					return true;
				}
			}else{
				m_risingEdgeMem = true;
				return false;
			}
			return false;
	}

	bool fallingEdge(bool varToEdgeCheck)
	{
		if(!varToEdgeCheck){
			if (m_fallingEdgeMem){
				m_fallingEdgeMem = false;
				return true;
			}
		}else{
			m_fallingEdgeMem = true;
			return false;
		}
		return false;
	}

	bool dualEdge (bool varToEdgeCheck)
	{
		return fallingEdge(varToEdgeCheck) || risingEdge(varToEdgeCheck);
	}

	void toggleStatus()
	{
		if (m_status == m_toggleVal1){
				m_status = m_toggleVal2;
		}else{
			m_status = m_toggleVal1;
		}
	}

	//edgeMode is used to change which type of edge is detected, with the default being risingEdge
	//The options are KRisingEdge, KDualEdge, and KFallingEdge
	T toggleStatusOnEdgeChange(bool varToEdgeCheck, edgeType edgeMode = KRisingEdge)
	{
		if(edgeMode == Toggle<T>::KFallingEdge){
			if(fallingEdge(varToEdgeCheck)){
				toggleStatus();
			}
		}else if(edgeMode == Toggle<T>::KDualEdge){
			if(dualEdge(varToEdgeCheck)){
				toggleStatus();
			}
		}else if(edgeMode == Toggle<T>::KRisingEdge){
			if(risingEdge(varToEdgeCheck)){
				toggleStatus();
			}
		}
		return getStatus();
	}

	T getStatus(){
		return m_status;
	}

	//Sets the current state of the Toggle. MUST BE ONE OF THE TOGGLEABLE VALUES SET IN THE CONSTRUCTOR
	void setStatus(T valueToSet){
		if(valueToSet == m_toggleVal1 || valueToSet == m_toggleVal2){
			m_status = valueToSet;
		}
	}
};

#endif /* TOGGLECLASS_H */
