//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author David Krhovský
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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

PriorityQueue::PriorityQueue() {
    m_pHead = nullptr;
}

PriorityQueue::~PriorityQueue() {
    Element_t *element = GetHead();
    while (element != nullptr) {
        Element_t *toDelete = element;
        element = element->pNext;
        delete toDelete;
    }
}

void PriorityQueue::Insert(int value) {
    if (m_pHead == nullptr) {
        m_pHead = new Element_t();
        m_pHead->value = value;
        m_pHead->pNext = nullptr;
        return;
    }

    if (value > m_pHead->value) {
        Element_t *element = new Element_t();
        element->pNext = m_pHead->pNext;
        element->value = m_pHead->value;
        m_pHead->value = value;
        m_pHead->pNext = element;
        return;
    }

    Element_t *previous = m_pHead;

    for (Element_t *element = GetHead(); element != nullptr; element = element->pNext) {
        if ((value < previous->value) && (value > element->value)) {
            Element_t *insert = new Element_t();
            previous->pNext = insert;
            insert->pNext = element;
            insert->value = value;
            return;
        }
        previous = element;
    }
    previous->pNext = new Element_t();
    previous->pNext->value = value;
    previous->pNext->pNext = nullptr;
}

bool PriorityQueue::Remove(int value) {
    Element_t *previous = m_pHead;

    for (Element_t *element = GetHead(); element != nullptr; element = element->pNext) {
        if (value == element->value) {
            if (element == m_pHead) {
                m_pHead = element->pNext;
                delete element;
                return true;
            } else {
                previous->pNext = nullptr;
                delete element;
                return true;
            }
        }
        previous = element;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value) {
    if (m_pHead == nullptr) {
        return nullptr;
    } else {
        for (Element_t *element = GetHead(); element != nullptr; element = element->pNext) {
            if (value == element->value) {
                return element;
            }
        }
    }
    return nullptr;
}

size_t PriorityQueue::Length() {
    if (m_pHead == nullptr) {
        return 0;
    }
    size_t i = 1;
    for (Element_t *element = GetHead(); element->pNext != nullptr; element = element->pNext) {
        i++;
    }
    return i;
}

PriorityQueue::Element_t *PriorityQueue::GetHead() {
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
