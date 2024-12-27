#pragma once 
#ifndef DLIST_H
#define DLIST_H
#define TwoStackAlgo

#include <iostream>
#include <stdexcept> // Für Ausnahmewürfe wie unterflow_error

// Definition der Node-Klasse (einzelne Elemente der doppelt verketteten Liste)
template <typename T>
class Node {
public:
    // Konstruktor: Initialisiert ein Node mit Daten und setzt Zeiger auf nullptr
    Node(T data) : _data(data), _next(nullptr), _prev(nullptr) {}

    // Setter für den nächsten Node
    void next(Node* node) { _next = node; }

    // Getter für den nächsten Node
    Node* next() const { return _next; }

    // Setter für den vorherigen Node
    void prev(Node* node) { _prev = node; }

    // Getter für den vorherigen Node
    Node* prev() const { return _prev; }

    // Getter für die gespeicherten Daten
    T data() const { return _data; }

private:
    T _data;        // Die gespeicherten Daten
    Node* _next;    // Zeiger auf den nächsten Node
    Node* _prev;    // Zeiger auf den vorherigen Node
};

// Definition der Klasse DList (doppelt verkettete Liste)
template <typename T>
class DList {
public:
    // Konstruktor: Initialisiert die Liste als leer
    DList() : _first(nullptr), _last(nullptr) {}

    // Destruktor: Löscht alle Elemente aus der Liste
    ~DList() { flush(); }

    // Überprüft, ob die Liste leer ist
    bool isEmpty() const { return _first == nullptr; }

    // Entfernt alle Elemente aus der Liste
    void flush() {
        while (!isEmpty()) { // Solange die Liste nicht leer ist, entferne von vorne
            getFromFront();
        }
    }

    // Fügt ein Element am Anfang der Liste hinzu
    void addToFront(T data) {
        Node<T>* newNode = new Node<T>(data); // Neues Node erstellen
        if (isEmpty()) {
            _first = _last = newNode; // Wenn leer, ist das neue Node sowohl das erste als auch das letzte
        }
        else {
            newNode->next(_first); // Verknüpfe das neue Node mit dem aktuellen ersten Node
            _first->prev(newNode); // Setze den vorherigen Zeiger des aktuellen ersten Nodes
            _first = newNode;      // Setze das neue Node als erstes Node
        }
    }

    // Fügt ein Element am Ende der Liste hinzu
    void addToBack(T data) {
        Node<T>* newNode = new Node<T>(data); // Neues Node erstellen
        if (isEmpty()) {
            _first = _last = newNode; // Wenn leer, ist das neue Node sowohl das erste als auch das letzte
        }
        else {
            newNode->prev(_last); // Verknüpfe das neue Node mit dem aktuellen letzten Node
            _last->next(newNode); // Setze den nächsten Zeiger des aktuellen letzten Nodes
            _last = newNode;      // Setze das neue Node als letztes Node
        }
    }

    // Entfernt und gibt das erste Element der Liste zurück
    T getFromFront() {
        if (isEmpty()) throw std::underflow_error("Liste ist leer"); // Fehler, wenn leer
        Node<T>* nodeToRemove = _first; // Das erste Node, das entfernt wird
        T data = nodeToRemove->data();  // Speichere die Daten des ersten Nodes
        _first = _first->next();        // Setze das zweite Node als neues erstes
        if (_first) _first->prev(nullptr); // Entferne den Rückwärtszeiger, falls vorhanden
        else _last = nullptr;           // Wenn Liste leer wird, setze _last auf nullptr
        delete nodeToRemove;            // Speicher des entfernten Nodes freigeben
        return data;                    // Gib die Daten zurück
    }

    // Entfernt und gibt das letzte Element der Liste zurück
    T getFromBack() {
        if (isEmpty()) throw std::underflow_error("Liste ist leer"); // Fehler, wenn leer
        Node<T>* nodeToRemove = _last;  // Das letzte Node, das entfernt wird
        T data = nodeToRemove->data();  // Speichere die Daten des letzten Nodes
        _last = _last->prev();          // Setze das vorletzte Node als neues letztes
        if (_last) _last->next(nullptr); // Entferne den Vorwärtszeiger, falls vorhanden
        else _first = nullptr;          // Wenn Liste leer wird, setze _first auf nullptr
        delete nodeToRemove;            // Speicher des entfernten Nodes freigeben
        return data;                    // Gib die Daten zurück
    }

    // Getter für das erste Node
    Node<T>* getFirst() const { return _first; }

private:
    Node<T>* _first; // Zeiger auf das erste Element
    Node<T>* _last;  // Zeiger auf das letzte Element
};

// Definition der Klasse Queue (Warteschlange, FIFO)
template <typename T>
class Queue {
public:
    // Konstruktor: Initialisiert eine leere Queue
    Queue() : _list() {}

    // Überprüft, ob die Queue leer ist
    bool isEmpty() const { return _list.isEmpty(); }

    // Fügt ein Element zur Queue hinzu
    void enqueue(T data) { _list.addToBack(data); }

    // Entfernt und gibt das erste Element der Queue zurück
    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue ist leer"); // Fehler, wenn leer
        return _list.getFromFront(); // Entfernt das erste Element
    }

    // Gibt das erste Element der Queue zurück, ohne es zu entfernen
    T peek() const {
        if (isEmpty()) throw std::underflow_error("Queue ist leer"); // Fehler, wenn leer
        return _list.getFirst()->data(); // Zugriff auf die Daten des ersten Elements
    }

private:
    DList<T> _list; // Verwendet eine DList als interne Datenstruktur
};

// Definition der Klasse Stack (Stapel, LIFO)
template <typename T>
class Stack {
public:
    // Konstruktor: Initialisiert einen leeren Stack
    Stack() : _list() {}

    // Überprüft, ob der Stack leer ist
    bool isEmpty() const { return _list.isEmpty(); }

    // Fügt ein Element zum Stack hinzu
    void push(T data) { _list.addToFront(data); }

    // Entfernt und gibt das oberste Element des Stacks zurück
    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack ist leer"); // Fehler, wenn leer
        return _list.getFromFront(); // Entfernt das erste Element
    }

    // Gibt das oberste Element des Stacks zurück, ohne es zu entfernen
    T peek() const {
        if (isEmpty()) throw std::underflow_error("Stack ist leer"); // Fehler, wenn leer
        return _list.getFirst()->data(); // Zugriff auf die Daten des ersten Elements
    }

private:
    DList<T> _list; // Verwendet eine DList als interne Datenstruktur
};

#endif