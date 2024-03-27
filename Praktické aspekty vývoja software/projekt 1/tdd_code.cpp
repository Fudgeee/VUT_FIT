//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Adrián Matušík <xmatus35@stud.fit.vutbr.cz>
// $Date:       $2022-03-02
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Adrián Matušík
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t* element = GetHead();
    while (element != NULL){
        Element_t* next_element = element->pNext;
        free(element);
        element = next_element;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t* element = GetHead();
    if(element == NULL){
        m_pHead = NewElement(value, NULL);
    }
    else{
        Element_t* prev_element = NULL;
        while(element != NULL && element->value >= value){
            prev_element = element;
            element = element->pNext;
        }
        if(element == NULL){ 
            element = NewElement(value, NULL);
            prev_element->pNext = element;
        }
        else if(m_pHead->value < value){
            m_pHead = NewElement(value, element);
        }
        else{
            prev_element->pNext = NewElement(value, element); 
        }      
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t* element = GetHead();
    if(element != NULL){
        Element_t* prev_element = NULL;
        while(element != NULL && element->value != value){
            prev_element = element;
            element = element->pNext;
        }
        if(element == NULL){
            return false;
        }
        if(prev_element == NULL){
            m_pHead = element->pNext;
        }
        else{
            prev_element->pNext = element->pNext;
        }
        free(element);
        return true;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t* element = GetHead();
    while(element != NULL){
        if(element->value == value){
            return element;
        }
        element = element->pNext;
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
    Element_t* element = GetHead();
    if(element != NULL){
        int counter = 0;
        while(element != NULL){
            element = element->pNext;
            counter++;
        }
        return counter;
    }
	return 0;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

PriorityQueue::Element_t *PriorityQueue::NewElement(int value, Element_t *pNext)
{
    Element_t* element = new Element_t();
    element->value = value;
    element->pNext = pNext;
    return element;
}

/*** Konec souboru tdd_code.cpp ***/
