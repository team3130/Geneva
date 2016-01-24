/*
 * ToggleClass.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Colin
 */

#include "ToggleClass.h"

template <typename T>
Toggle<T>::Toggle(T toggle1Val, T toggle2Val)
{
	m_status = toggle1Val;
	m_toggleVal1 = toggle1Val;
	m_toggleVal2 = toggle2Val;

	m_risingEdgeMem = true;
	m_fallingEdgeMem = true;
}

template <typename T>
//Returns true on a rising edge, else, returns false
bool Toggle<T>::risingEdge(bool varToEdgeCheck){
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

template <typename T>
//Returns true on a falling edge, else, returns false
bool Toggle<T>::fallingEdge(bool varToEdgeCheck){
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

template <typename T>
//Returns true on either are rising or falling edge, else, returns false
bool Toggle<T>::dualEdge(bool varToEdgeCheck){
	return fallingEdge(varToEdgeCheck) || risingEdge(varToEdgeCheck);
}

template <typename T>
//Changes the output state between the two values described in the constructor
void Toggle<T>::toggleStatus(){
	if (m_status == m_toggleVal1){
		m_status = m_toggleVal2;
	}else{
		m_status = m_toggleVal1;
	}
}

template <typename T>
//If an edge change is present, changes the output state and then returns the new state,
//else, returns the old state
T Toggle<T>::toggleStatusOnEdgeChange(bool checkedVar, edgeType edgeMode){
	if(edgeMode == Toggle<T>::KFallingEdge){
		if(fallingEdge(checkedVar)){
			toggleStatus();
		}
	}else if(edgeMode == Toggle<T>::KDualEdge){
		if(dualEdge(checkedVar)){
			toggleStatus();
		}
	}else if(edgeMode == Toggle<T>::KRisingEdge){
		if(risingEdge(checkedVar)){
			toggleStatus();
		}
	}
	return getStatus();
}
