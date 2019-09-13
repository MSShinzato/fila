#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class IFila{
public:
    virtual ~IFila(){};
    virtual bool Enfileira(T valor) = 0;
    virtual void Imprime() = 0;
    virtual T Desenfileira(bool* ok) = 0;
};

template <typename T>
class Fila : public IFila<T>{
private:
    T* v;
    int i;
    int f;
    int max;
public:
    Fila(const Fila& outra){
        this->v = new T[outra.max];
        this->i=outra.i;
        this->f=outra.f;
        this->max = outra.max;
        for(int ii=i; ii != f; ii=(ii+1)%max){
            this->v[ii] = outra.v[ii];
        }
        cout << "Construtor por copia" << endl;
    }

    Fila(int maximo) {
        v = new T[maximo+1];
        i=f=0;
        max = maximo+1;
    }

    ~Fila(){
        delete[] v;
    }

    bool Enfileira(T valor){
        if( (f+1) % max == i)
            return false;

        v[f] = valor;
        f = (f + 1) % max;
        return true;
    }

    T Desenfileira(bool* ok = NULL){
        if( i == f) {
            if(ok){
                *ok = false;
            }
            return v[i];
        }

        T temp = v[i];
        i = (i + 1) % max;
        if(ok)
            *ok = true;
        return temp;

    }

    void Imprime(){
        int ii;
        for(ii=i; ii != f; ii=(ii+1)%max){
            cout << v[ii] << " ";
        }
        cout << endl;
    }
    /*const Fila& operator=(const Fila& outra){
        cout << "operator" << endl;
        this->v = new T[outra.max];
        T* g = new T[outra.max];
        copy(v,v+max,g);
    }*/

};

int main() {

    Fila<float> f(5);


    f.Enfileira(10);
    f.Enfileira(5);
    f.Enfileira(3);
    f.Enfileira(8);
//    Fila<float> f2(5);
//    f2=f;

    Fila<float> f3(f);

    f.Imprime();
    //f2.Imprime();
    f3.Imprime();

    bool ok;
    do{
        float x = f.Desenfileira(&ok);
        if(ok)
            cout << "- "<< x << endl;
    }while(ok);

    /*bool ok1;
    do{
        float x = f2.Desenfileira(&ok1);
        if(ok1)
            cout << "- "<< x << endl;
    }while(ok1);*/

    bool ok2;
    do{
        float x = f3.Desenfileira(&ok2);
        if(ok2)
            cout << "- "<< x << endl;
    }while(ok2);

    return 0;
}