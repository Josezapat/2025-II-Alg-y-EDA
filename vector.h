#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstddef>   // size_t
#include <iostream>  // std::ostream
#include <utility>   // std::swap, std::move
#include <stdexcept> // std::out_of_range (si usas at())

// PC1: deben hacer:
//   2 problemas de nivel 2
//   3 problemas de nivel 1
// Cada solución enviarla como un Pull Request
//
// TODO (Nivel 2): Agregar Traits
// TODO (Nivel 2): Agregar Iterators (forward, backward)
// TODO (Nivel 1): Agregar Documentación para doxygen
// TODO (Nivel 2): Agregar control de concurrencia

template <typename T>
class CVector {
    T*     m_pVect = nullptr;
    size_t m_count = 0;  // elementos usados
    size_t m_max   = 0;  // capacidad

public:
    // ----------- Constructores/Destructor -----------
    explicit CVector(size_t n = 0)
        : m_pVect(n ? new T[n] : nullptr), m_count(0), m_max(n) {}

    // (Nivel 1) Constructor por copia (deep copy)
    CVector(const CVector& other)
        : m_pVect(other.m_max ? new T[other.m_max] : nullptr),
          m_count(other.m_count),
          m_max(other.m_max) {
        for (size_t i = 0; i < m_count; ++i) m_pVect[i] = other.m_pVect[i];
    }

    // (Nivel 2) Constructor por movimiento
    CVector(CVector&& other) noexcept
        : m_pVect(other.m_pVect),
          m_count(other.m_count),
          m_max(other.m_max) {
        other.m_pVect = nullptr; other.m_count = 0; other.m_max = 0;
    }

    // (Nivel 1) Destructor seguro
    ~CVector() {
        delete[] m_pVect;
        m_pVect = nullptr;
        m_count = m_max = 0;
    }

    // ----------- Asignaciones (Regla de Cinco) -----------
    // Asignación por copia (copy-and-swap: fuerte seguridad de excepción)
    CVector& operator=(CVector other) { // copia por valor -> ya invoca copy/move según el caso
        swap(other);                    // intercambia con la copia; 'other' destruye lo viejo
        return *this;
    }

    // Asignación por movimiento (noexcept)
    CVector& operator=(CVector&& other) noexcept {
        if (this != &other) {
            delete[] m_pVect;
            m_pVect = other.m_pVect;
            m_count = other.m_count;
            m_max   = other.m_max;
            other.m_pVect = nullptr; other.m_count = 0; other.m_max = 0;
        }
        return *this;
    }

    // Utilidad para intercambiar contenido
    void swap(CVector& other) noexcept {
        using std::swap;
        swap(m_pVect, other.m_pVect);
        swap(m_count, other.m_count);
        swap(m_max,   other.m_max);
    }

    // ----------- Operaciones básicas -----------
    // Inserta al final; crece si es necesario
    void insert(const T& elem) {
        if (m_count == m_max) resize();
        m_pVect[m_count++] = elem;
    }

    // Política de crecimiento: duplica la capacidad (mínimo 8)
    void resize() {
        size_t nueva_cap = (m_max == 0) ? 8 : (m_max * 2);
        T* pTmp = new T[nueva_cap];
        for (size_t i = 0; i < m_count; ++i) pTmp[i] = std::move(m_pVect[i]);
        delete[] m_pVect;
        m_pVect = pTmp;
        m_max   = nueva_cap;
    }

    // Opcional: reservar capacidad explícitamente
    void reserve(size_t cap) {
        if (cap <= m_max) return;
        T* pTmp = new T[cap];
        for (size_t i = 0; i < m_count; ++i) pTmp[i] = std::move(m_pVect[i]);
        delete[] m_pVect;
        m_pVect = pTmp;
        m_max   = cap;
    }

    // ----------- Acceso -----------
    T& operator[](size_t idx) {               // mutable
        return m_pVect[idx];
    }
    const T& operator[](size_t idx) const {   // solo lectura
        return m_pVect[idx];
    }

    // Opción con chequeo de rango (útil en debug)
    T& at(size_t idx) {
        if (idx >= m_count) throw std::out_of_range("CVector::at");
        return m_pVect[idx];
    }
    const T& at(size_t idx) const {
        if (idx >= m_count) throw std::out_of_range("CVector::at");
        return m_pVect[idx];
    }

    // ----------- Utilidades -----------
    size_t size()     const { return m_count; }
    size_t capacity() const { return m_max;   }
    bool   empty()    const { return m_count == 0; }

    
    // (Nivel 2) permitir cout << vector
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const CVector<U>& v);
};

// ----------- operator<< -----------
template <typename U>
std::ostream& operator<<(std::ostream& os, const CVector<U>& v) {
    os << "[";
    for (size_t i = 0; i < v.m_count; ++i) {
        if (i) os << ", ";
        os << v.m_pVect[i];
    }
    return os << "]";
}

#endif // __VECTOR_H__
