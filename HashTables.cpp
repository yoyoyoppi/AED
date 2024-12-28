#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Nodo de la lista enlazada para manejar colisiones
template<typename T>
struct Nodo {
    T data;
    Nodo* next;

    Nodo(T d) : data(d), next(nullptr) {}
};

// Lista enlazada para manejar colisiones
template<typename T>
class List {
private:
    Nodo<T>* head;

public:
    List() : head(nullptr) {}

    // Insertar si no existe (evitar duplicados)
    bool insert(T value) {
        Nodo<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {  // Si el valor ya existe (transformación Morse)
                return false;  // No se inserta de nuevo
            }
            current = current->next;
        }
        // Insertar un nuevo nodo al frente
        Nodo<T>* newNode = new Nodo<T>(value);
        newNode->next = head;
        head = newNode;
        return true;  // Se inserta con éxito
    }

    // Destructor para liberar memoria
    ~List() {
        Nodo<T>* current = head;
        while (current != nullptr) {
            Nodo<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Tabla Hash con chaining
template<typename T>
class HashTable {
private:
    vector<List<T>> table;
    int capacity;

    // Función hash simple basada en el módulo
    int hashFunction(T key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue + ch) % capacity;  // Suma los caracteres y aplica módulo
        }
        return hashValue;
    }

public:
    // Constructor
    HashTable(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    // Insertar si no existe (para evitar duplicados)
    bool insert(T value) {
        int index = hashFunction(value);
        return table[index].insert(value);
    }
};
