
#include "set.h"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <ostream>


/** 
 * 
 * Stuttura dove definiamo l'operator() il quale
 * restituisce true se i valori interi dati in input sono uguali.
 * False altrimenti.
 * 
 * 
 * 
 */
struct equalsInt{

    bool operator()(int a, int b) const{
        return a == b;
    }

};

/**
 * 
 * Struttura dove definiamo l'operator(), il quale
 * restituisce true se le stringhe date in input sono uguali.
 * False altrimenti.
 * 
 */
struct equalsString{

    bool operator()(const std::string &a, const std::string &b) const{
        return a == b;
    }

};




/**
 * @brief struttura punto
 * 
 * Struttura che ci permette di creare un punto.
 * 
 */
struct punto {

    int x;  ///< Coordinata x del punto
    int y;  ///< Coordinata y del punto

    /**
     * Costruttore di default
     * 
     */
    punto() : x(),y(){}

    /**
     * Costruttore secondario
     * 
     * @param xx valore da copiare in x
     * @param yy valore da copiare in y
     */
    punto(int xx, int yy) : x(xx), y(yy) {}

    /**
     * operator!=
     * 
     * operator che mi restituisce true se due punti sono diversi
     * 
     * @param other secondo punto da confrontare
     */
    bool operator!=(const punto &other) const{
        return x != other.x | y != other.y;
    }

    /**
     * operator==
     * 
     * operator che mi restituisce true se due punti sono uguali
     * 
     * @param other secondo punto da confrontare
     */
    bool operator==(const punto &other) const{
        return x == other.x && y == other.y;
    }

    /**
     * Distruttore
     * 
     */
    ~punto() {}

    
/**
  Ridefinizione dell'operatore di stream << per un punto.
  Necessario per l'operatore di stream della classe set.
*/
friend std::ostream &operator<<(std::ostream &os, const punto &p) {
  os<<"("<<p.x<<","<<p.y<<")";
  return os;
}



};

/**
 * 
 * Struttura dove definiamo l'operator(), il quale
 * restituisce true se i punti dati in input sono
 * uguali.
 * False altrimenti.
 * 
 * 
 */
struct equalsPunto{

    bool operator()(const punto &a, const punto &b) const{
        if(a.x == b.x && a.y == b.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

/**
 *  
 * @brief CoordinatePari
 * 
 * Mi dice se le coordinate del punto p sono pari
 * 
 */
bool cordinatePari(const punto &p){
    return p.x %2 ==0 && p.y%2 ==0;
}


/**
 * @brief cordinateDispari
 * 
 * Mi dice se le cordinate del punto p sono dispari
 * 
 * 
 */
bool cordinateDispari(const punto &p){
    return p.x %2 !=0 && p.y%2 !=0;
}

/**
 * @brief cordinateUguali
 * 
 * Mi dice se le cordinate del punto p sono uguali
 * 
 */
bool cordinateUguali(const punto &p){
    return p.x == p.y;
}





/**
 * Test d'uso della set con valori interi
 * 
 * @brief Test d'uso della set con valori interi
 * 
 */
void test_set_interi(){

    std::cout<< "******** TEST SET INTERI ********" <<std::endl;


    set<int,equalsInt> s1;
    s1.add(1);
    s1.add(4);
    s1.add(7);

    std::cout<< "s1 dopo add" <<std::endl;
    std::cout<< s1 <<std::endl;

    s1.remove(4);
    std::cout<< "s1 dopo remove" <<std::endl;
    std::cout<< s1 <<std::endl;

    set<int,equalsInt> s2(s1);
    std::cout<< "test copy constructor. s2" <<std::endl;
    std::cout<< s2 <<std::endl;

    set<int,equalsInt> s3;
    s3 = s1;
    std::cout<< "s3 dopo operator=" <<std::endl;
    std::cout<< s3 <<std::endl;

    

    std::cout<< "operator[] su s1 in posisione 1: " <<std::endl;
    std::cout<< s1[1] <<std::endl;

    std::cout<< "test operator== (s1==s2)" <<std::endl;
    std::cout<< (s1==s2) <<std::endl;


    set<int,equalsInt> s5;
    s5.add(1);
    s5.add(2);
    s5.add(3);
    set<int,equalsInt> s6;
    s6.add(2);
    s6.add(4);
    s6.add(5);
    s6.add(1);
    s6.add(10);

    std::cout<< "s5:" <<std::endl;
    std::cout<< s5 <<std::endl;
    std::cout<< "s6" <<std::endl;
    std::cout<< s6 <<std::endl;

    std::cout<< "test operator+ s5+s6" <<std::endl;
    set<int,equalsInt> s4 = s5+s6;
    std::cout<< s4 <<std::endl;

    std::cout<< "test operator- s5-s6" <<std::endl;
    set<int,equalsInt> s7 = s5-s6;
    std::cout<< s7 <<std::endl;

    std::cout<< "test creazione set con iteratori" <<std::endl;
    int dati[7] = {1,3,4,6,5,8,9};
    set<int,equalsInt> s8(dati, dati+7);
    std::cout<< s8 <<std::endl; 

    set<int,equalsInt> s9;
    std::cout<< "test vuota" <<std::endl;
    std::cout<< s9.vuota() <<std::endl;
    s9.add(1);
    std::cout<< "test vuota 2" <<std::endl;
    std::cout<< s9.vuota() <<std::endl;    






}






/**
 * 
 * Test d'uso della set con valori di tipo stringa
 * 
 * @brief Test d'uso della set con valori di tipo stringa
 * 
 */
void test_set_stringhe(){

    std::cout<< "******** TEST SET STRING ********" <<std::endl;


    set<std::string,equalsString> s1;
    s1.add("ciao");
    s1.add("prova");

    std::cout<< "s1 dopo add"<<std::endl;
    std::cout<< s1 <<std::endl;

    set<std::string,equalsString> s2(s1);
    std::cout<< "s2 dopo copy constructor"<<std::endl;
    std::cout<< s2 <<std::endl;

    s2.remove("ciao");
    std::cout<< "s2 dopo remove di ciao "<<std::endl;
    std::cout<< s2 <<std::endl;

    set<std::string,equalsString> s3;
    s3 = s2;
    std::cout<< "s3 dopo operatore= " <<std::endl;
    std::cout<< s3 <<std::endl;

    std::cout<< "test operator su s1" <<std::endl;
    std::cout<< s1[0] <<std::endl;

    std::cout<< "test operator== tra s1 e s3" <<std::endl;
    std::cout<< (s1==s3) <<std::endl;

    set<std::string,equalsString> s4;
    s4.add("prova");
    s4.add("ciao");
    std::cout<< "test operator== tra s1 e s4" <<std::endl;
    std::cout<< (s1==s4) <<std::endl;

    set<std::string,equalsString> s5;
    s5.add("mondo");
    s5.add("test");
    std::cout<< "test operator+ tra s1 e s5" <<std::endl;
    std::cout<< (s1+s5) <<std::endl;

    set<std::string,equalsString> s6;
    s6.add("mondo");
    std::cout<< "test operator- tra s5 e s6" <<std::endl;
    set<std::string,equalsString> s7 = s5-s6;
    std::cout<< s7 <<std::endl;

    std::cout<< "test creazione set con iteratori" <<std::endl;
    std::string dati[5] = {"ciao","mondo","prova","salve","test"};
    set<std::string,equalsString> s8(dati,dati+5);
    std::cout<< s8 <<std::endl;


}

/**
 * Test d'uso della set composta da oggetti punto.
 * 
 * 
 */
void test_set_punti(){

    std::cout<< "******** TEST SET PUNTI ********" <<std::endl;


   set<punto,equalsPunto> s1;
   s1.add(punto(1,1));
   s1.add(punto(2,1));

   std::cout<<" s1 dopo add"<<std::endl;
   std::cout<< s1 <<std::endl;

   set<punto,equalsPunto> s2(s1);
   std::cout<<"stampa di s2 dopo copy constructor"<<std::endl;
   std::cout<< s2 <<std::endl;

   s2.remove(punto(1,1));
   std::cout<<"s2 dopo remove di punto(1,1) "<<std::endl;
   std::cout<< s2 <<std::endl;

   set<punto,equalsPunto> s3;
   s3 = s2;
   std::cout<<"s3 dopo operator= con s2"<<std::endl;
   std::cout<< s3 <<std::endl;

   std::cout<<"test operator[] su s1"<<std::endl;
   std::cout<< s1[0] <<std::endl;

   set<punto,equalsPunto> s4;
   s4.add(punto(2,2));
   s4.add(punto(5,9));
   s4.add(punto(10,7));
   s4.add(punto(1,2));

   set<punto,equalsPunto> s5;
   s5.add(punto(3,4));
   s5.add(punto(6,7));
   s5.add(punto(4,0));

   set<punto,equalsPunto> s6;
   s6.add(punto(6,7));
   s6.add(punto(4,0));
   s6.add(punto(3,4));

   set<punto,equalsPunto> s7;
   s7.add(punto(10,7));
   s7.add(punto(2,2));
   
   
   std::cout<<"test operator== tra s4 e s5 "<<std::endl;
   std::cout<< (s4==s5) <<std::endl;

   std::cout<<"test operator== tra s5 e s6 "<<std::endl;
   std::cout<< (s5==s6) <<std::endl;

   std::cout<<"test operator+ tra s4 e s5 "<<std::endl;
   std::cout<< (s4+s5) <<std::endl;

   std::cout<<"test operator- tra s4 e s7 "<<std::endl;
   set<punto,equalsPunto> s8 = s7-s4;
   std::cout<< s8 <<std::endl;

   punto dati[4] = {punto(0,0), punto(3,2), punto(7,8), punto(10,1)};
   set<punto,equalsPunto> s9(dati,dati+4);
   std::cout<< "test creazione set con iteratori" <<std::endl;
   std::cout<< s9 <<std::endl;



}


/**
 * Test d'uso di una set costrante composta da valori di tipo int.
 * 
 * Con una set costante:
 * 
 * La add non è chiamabile su un oggetto const.
 * La svuota/distruttore non è chiamabile su un oggetto const
 * 
 * @param S set costante
 */
void test_set_const_int(const set<int,equalsInt> &S){
    
    std::cout<< "******** TEST SET CONSTANTE INTERI ********" <<std::endl;


    //add e remove e distruttore non possibili su un const

    std::cout<< "visualizzo set costante" <<std::endl;
    std::cout<< S <<std::endl;

    std::cout<< "test operatore[] su S" <<std::endl;
    std::cout<< S[2] <<std::endl;

    set<int,equalsInt> s1(S);
    std::cout<< "test copy constructor con S" <<std::endl;
    std::cout<< s1 <<std::endl;

    set<int,equalsInt> s2;
    s2 = S;
    std::cout<< "test operator= con S" <<std::endl;
    std::cout<< s2 <<std::endl;

    std::cout<< "test operator== con s1==S" <<std::endl;
    std::cout<< (s1==S) <<std::endl;

    s2.add(6);
    std::cout<< "test operator== con s2==S" <<std::endl;
    std::cout<< (s2==S) <<std::endl;

    set<int,equalsInt> s3;
    s3.add(0);
    s3.add(9);
    s3.add(20);
    s3.add(50);

    set<int,equalsInt> s4 = S+s3;
    std::cout<< "test operator+ con S e s3" <<std::endl;
    std::cout<< s4 <<std::endl;

    set<int,equalsInt> s5 = s4-S;
    std::cout<< "test operator- con S e s4" <<std::endl;
    std::cout<< s5 <<std::endl;

}

/**
 * @brief Test d'uso della funzione globale e generica filter_out con una set di punti
 * 
 */
void test_filter_out(){

    std::cout<< "******** TEST FILTER_OUT SU SET PUNTI ********" <<std::endl;

    set<punto,equalsPunto> s;

    s.add(punto(1,1));
    s.add(punto(2,4));
    s.add(punto(3,5));
    s.add(punto(6,7));
    s.add(punto(7,7));
    s.add(punto(8,10));

    std::cout<< "s" <<std::endl;
    std::cout<< s <<std::endl;

    std::cout<< filter_out(s,cordinatePari) <<std::endl;
    std::cout<< filter_out(s,cordinateDispari) <<std::endl;
    std::cout<< filter_out(s,cordinateUguali) <<std::endl;




}

/**
 * Test d'uso dell'iterator con set di interi e set di punti
 * 
 */
void test_iterator(){

 //   std::cout<< "******** TEST CONST ITERATOR ********" <<std::endl;

 int dati[5]={1, 5, 9, 3, 0};
    set<int, equalsInt>s(dati, dati+5);
    set<int, equalsInt>::const_iterator i,a,b;
    assert(a==b);
    i=s.begin();
    set<int, equalsInt>::const_iterator ii(i);
    assert(i==ii);
    assert((*i) == (*ii));
    i++;
    ii++;
    assert(i==ii);
    assert((*i) == (*ii));
    ++i;
    ii++;
    assert(i==ii);
    assert((*i) == (*ii));

    assert(*i == 9 && *ii==9);
    i++;
    assert(i!=ii);
    assert((*i) != (*ii));
    const int *p=&(*i);
    assert(*p==3);
    
    punto setPunti[9]={punto(-1,-5),punto(0,0),punto(1,-4),punto(-4,-3),punto(10,3),punto(4,-1),punto(-2,1),punto(-9,-7),punto(2,1)};
    set<punto, equalsPunto> s1(setPunti, setPunti+9);
    set<punto, equalsPunto>::const_iterator iter;

    set<punto, equalsPunto>::const_iterator iter2;
    assert(iter==iter2);
    
    iter = s1.begin();
    set<punto, equalsPunto>::const_iterator iter3(iter);
    assert(iter == iter3);
    assert(*iter == *iter3);

    iter++;
    assert(*iter == punto(0,0));

    ++iter;
    assert(*iter == punto(1,-4));
    
    assert(iter != iter2);

    iter = s1.begin();
    assert((iter->x)==-1);
    assert((iter->y)==-5);

    i=ii;
    assert(i==ii);
    assert((*i) == (*ii));




    




}







int main(){
    

    test_set_interi();

    test_set_stringhe();

    test_set_punti();

    set<int,equalsInt> s;
    s.add(1);
    s.add(2);
    s.add(8);
    s.add(7);

    test_set_const_int(s);

    test_filter_out();

    test_iterator();
    
    return 0;
};
