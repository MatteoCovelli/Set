#ifndef SET_H
#define SET_H

#include <cassert>
#include <algorithm>
#include <iostream>
#include <ostream>

#include <iterator>
#include <cstddef>



/**
 * @brief classe set
 * 
 * La classe implementa un set di elementi generici T.
 * Un set è una collezione di dati che NON può contenere duplicati.
 * 
 */
template <typename T, typename Eql> class set {


    /**
     * @brief struttura nodo
     * 
     * Struttura dati nodo interna che viene usata per creare la lista.
     * 
     */
    struct nodo
    {

        T valore;   ///< valore da memorizzare
        nodo *next; ///< puntatore al prossimo nodo della lista

        /**
         * Costruttore di default
         * 
         * @post next == nullptr
         * 
         */
        nodo() : next(nullptr) {}

        /**
         * Costruttore secondario
         * 
         * @param val valore da copiare
         * @param n puntatore a next
         */
        nodo(const T& val, nodo *n) : valore(val), next(n) {}

        /**
         * Copy constructor. Copiamo i dati membro a membro.
         * In questo caso è una struttura interna di supporto
         * alla classe set.
         * 
         * @param other nodo da copiare
         */
        nodo(const nodo &other)
        {
            if (this != &other)
            {
                valore = other.valore;
                next = other.next;
            }
        }

        /**
         * Operatore di assegnamento.
         * 
         * @param other nodo da copiare
         * @return reference al nodo this
         */
        nodo &operator=(const nodo &other)
        {
            valore = other.valore;
            next = other.next;
            return *this;
        }

        /**
         * Distruttore.
         * 
         */
        ~nodo() {}

    };




    nodo *_head;    ///< puntatore al primo nodo della lista
    Eql _equals;    ///< funtore per l'uguaglianza tra dati T

public:

    /**
     * Costruttore di default
     * 
     * @post _head == nullptr
     */
    set() : _head(nullptr) {}

    /**
     * Costruttore secondario con iteratori.
     * Viene creata una set a partire da una sequenza di dati
     * definita da una coppia generica di iteratori su tipi Q.
     * 
     * @post _head == nullptr
     */
    template <typename Q>
    set(Q b, Q e) : _head(nullptr){
        try {
        for( ; b!=e; ++b)
            add(static_cast<T>(*b)); // la add contiene una new che può fallire
        }
        catch(...) {
        // in caso di errore di memoria si svuota la lista
        svuota();
        throw;
        }
    }



    /**
     * Operatore di assegnamento.
     * 
     * @param other lista da copiare
     * @return reference alla lista this
     */
    set& operator=(const set &other)
    {
        if(this != &other)
        {
            set tmp(other);
            std::swap(this->_head, tmp._head);
        }

        return *this;
    }

    /**
     * Copy constructor
     * 
     * @param other lista da copiare
     */
    set(const set &other) : _head(nullptr) {

        nodo *curr = other._head;

        try
        {
           while(curr != nullptr)
           {
               add(curr->valore);
               curr = curr->next;

           }
           
         //  curr = nullptr;

        }
        catch(...)
        {
            svuota();
            throw;
        }
        

    }
    
    /**
     * @brief Funzione di inserimento valore nella lista (PUNTO 2 traccia esame)
     * 
     * La seguente funzione permette di effettuare l'aggiunta di un
     * valore all'interno della lista.
     * 
     * @param val   valore che si vuole inserire
     */
   void add(const T& val) 
   {

       if(_head == nullptr)
       {
            nodo  *tmp = new nodo(val, nullptr);
           _head = tmp;
           return;
       }

       nodo *curr = _head;
       nodo *prev = _head;
       

       while(curr != nullptr)
       {
           if( _equals(curr->valore , val))
           {
            //  std::cout<< "Valore non inserito perchè già presente" <<std::endl;
              return;
           }

           prev = curr;
           curr = curr->next;
       }
        nodo  *tmp = new nodo(val, nullptr);
       prev->next = tmp;

   }

    /**
     * Distruttore.
     * Viene utilizzata la funzione di supporto svuota()
     * 
     */
    ~set()
    {
        svuota();
    }

    /**
     * Funzione che implementa l'operatore di stream per set
     * 
     * @param os stream di output
     * @param s set da spedire sullo stream
     * @return std::ostream& stream di output
     */
    friend std::ostream &operator<<(std::ostream &os, const set &s){

        os<<"Size: "<< s.sizeCollezione() <<std::endl;

        nodo *curr = s._head;

        while(curr !=nullptr)
        {
            os << curr->valore << " ";
            curr = curr->next;
        }

        return os;
    }

    /**
     * @brief operator[]    (PUNTO 1 traccia esame)
     * Permette l'accesso, in sola lettura, all'i-esimo elemento.
     * 
     * @param i i-esimo valore che si vuole visualizzare
     * @return const T& valore in posizione i da restituire
     */
    const T& operator[](int i) const{

        nodo *curr = _head;
        nodo *prev = _head;
        int cont = 0;
        bool trovato = false;

        assert(i >= 0 && i< sizeCollezione());

        while(curr != nullptr && !trovato){
            
            if(cont == i)
            {
                trovato = true;
                
            }
            
            
                prev = curr;
                curr = curr->next;
                
            

            cont++;
        }

        return prev->valore;
    }

    /**
     * @brief Funzione rimozione valore nella set   (PUNTO 3 traccia esame)
     * 
     * La seguente funzione permette di rimuovere un determinato valore
     * all'interno della set
     * 
     * @param val valore che si vuole rimuovere
     */
    void remove(const T& val) {

    nodo *curr = _head;
        nodo *prev = nullptr;
        if (_equals(val, curr->valore))
        {
        _head = curr->next;
        delete curr;
    
        return;
        }
        while (curr != nullptr)
        {
        if (_equals(val, curr->valore))
        {
            prev->next = curr->next;
            delete curr;
        
            return;
        }
        prev = curr;
        curr = curr->next;
        }


    }


    /**
     * Funzione che permette di verificare se un valore è presente
     * all'interno della set
     * 
     * @param val valore che si vuole cercare
     * 
     * @return trovato bool che restituisce true se il valore viene trovato. False altrimenti
     */
    bool trovato(const T& val)const {

        nodo *curr = _head;
        
        bool trovato = false;

        while(curr != nullptr && trovato == false)
        {
            if(_equals(curr->valore, val))
            {
                trovato = true;
                
            }

            curr = curr->next;

        }

        return trovato;

    }

    /**
     * @brief operator==    (PUNTO 7 traccia esame)
     * 
     * La seguente funzione permette di verificare se due set sono uguali.
     * La funzione confronta due set e ritorna true se i due se contengono
     * gli stessi dati.
     * 
     * @param other set di cui si vuole fare il confronto
     * 
     * @return uguali bool che restituisce true se le due set sono uguali. False altrimenti.
     */
    bool operator==(const set& other) const
    {
        bool uguali = true;
        nodo *curr = _head;

        if(sizeCollezione() == 0 && other.sizeCollezione() == 0)
        {
            return true;
        }
        
        if(sizeCollezione() ==0 && other.sizeCollezione() != 0)
        {
            return false;
        }

        if(sizeCollezione() != other.sizeCollezione())
        {
            return false;
        }

        if(sizeCollezione() == other.sizeCollezione())
        {

            
            while(curr != nullptr && uguali)
            {
               

                if(other.trovato(curr->valore) == false)
                {
                    uguali = false;
                }

                curr = curr->next;


            }

            return uguali;

        }

        return uguali;

    }


    /**
     * Funzione svuota.
     * Permette di pulire la lista eliminando tutti i nodi,
     * al fine di garantire una corretta gestione della memoria.
     * 
     */
    void svuota(){
        nodo *curr = _head;

        while(curr != nullptr)
        {
            nodo *cnext = curr->next;
            delete curr;
            curr = cnext;
        }

        _head = nullptr;

    }

    /**
     * @brief sizeCollezione()
     * 
     * Funzione che restituisce la grandezza della collezione set
     * 
     * @return unsigned int dimensione della set
     */
    unsigned int sizeCollezione() const
    {
        nodo *curr = _head;
        unsigned int size = 0;

             while (curr != nullptr) {

                 size++;
                 curr = curr->next;
            }

        return size;
     
    }

    /**
     * @brief vuota()
     * 
     * Funzione che mi restituisce true se la lista è vuota.
     * 
     */
    bool vuota() const{
        return sizeCollezione() == 0;
    }


    class const_iterator {

  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef const T*                  pointer;
    typedef const T&                  reference;
  
    const_iterator() : ptr(nullptr) {
    }
    
    const_iterator(const const_iterator &other) : ptr(other.ptr) {
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~const_iterator() { 
        
    }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return ptr->valore;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return &(ptr->valore);
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ptr = ptr->next;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator& operator++() {
      ptr = ptr->next;
      return *this;
    }

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return (ptr == other.ptr);
    }
    
    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return !(other == *this);
    }

  private:
    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class set;
    const nodo *ptr; 

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const nodo *p) : ptr(p) { }
    
    

    // !!! Eventuali altri metodi privati
    
  }; // classe const_iterator



   // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
    return const_iterator(_head);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
    return const_iterator(nullptr);
  }

};



/**
 * @brief filter_out
 * 
 * Funzione globale e generica che dato un set generico S su tipi T e un predicato
 * booleano generico P, ritorna un nuovo set di tipi T ottenuto prendendo da S
 * tutti gli elementi che soddisfano il predicato P.
 * 
 * @param S set
 * @param pred predicato P
 * @return set<T,Eql> set restituita
 * 
 * @throw std::bad_alloc eccezione nel caso di cattiva allocazione
 */
template<typename T, typename Eql, typename P>
set<T,Eql> filter_out(const set<T,Eql> &S, P pred){

    typename set<T,Eql>::const_iterator b,e;
    set<T,Eql> s1;

    try{

        for(b = S.begin(), e=S.end(); b!=e; ++b) {
            if (pred(*b)){
                s1.add(*b);
            }
        }

    }
    catch(...){
        s1.svuota();
        throw;
    }

    return s1;
}

/**
 * @brief operator+
 * 
 * Funzione globale che, dati in input due set generici su tipi T, ritorna
 * un set di tipi T che contiene gli elementi di entrambi i set ("concatenazione" di set).
 * 
 * @param s1 prima set
 * @param s2 seconda set
 * @return set<T,Eql> set restituita
 * 
 * @throw std::bad_alloc eccezione nel caso di cattiva allocazione
 */
template<typename T, typename Eql>
set<T,Eql> operator+(const set<T,Eql> &s1, const set<T,Eql> &s2){

    set<T,Eql> s;


    try{

        for(int i=0; i<s1.sizeCollezione(); ++i)
        {
            s.add(s1[i]);
        }

        for(int j=0; j<s2.sizeCollezione(); ++j)
        {
            s.add(s2[j]);   
        }
    }
    catch(...){
        s.svuota();
        throw;

    }

    return s;

    

}

/**
 * @brief operator-
 * 
 * Funzione globale che, dati in input due set generici su tipi T, ritorna un set
 * di tipi T che contiene gli elementi comuni a entrambi i set ("intersezione" di set).
 *
 * @param s1 prima set
 * @param s2 seconda set
 * @return set<T,Eql> set restituita
 * 
 * @throw std::bad_alloc eccezione nel caso di cattiva allocazione
 */
template<typename T, typename Eql>
set<T,Eql> operator-(const set<T,Eql> &s1, const set<T,Eql> &s2){

    set<T,Eql> s;

    try{
    
        for(int i=0; i<s1.sizeCollezione(); ++i)
        {
            if(s2.trovato(s1[i]))
            {
                s.add(s1[i]);
            }
        }

    }
    catch(...){
        s.svuota();
        throw;
    }
    
    return s;

}




#endif



