#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	void vaciar();

private:
	/*
	 * Estructura interna
	 */
	map< int , map<int,C> > grafo;

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
	this->vertice=adyacente;
    this->costo=costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
	return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
	return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
	this->operator=(otroGrafo);
}

template <typename C> Grafo<C>::~Grafo()
{
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    grafo.clear();
    
	typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
	/*
	* Otra opción
	* grafo.insert(otroGrafo.begin(), otroGrafo.end());
	*/
    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
	return grafo.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
	return grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
	return (grafo.find(vertice)!=grafo.end());
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{	
	if ((existeVertice(origen)) and (existeVertice(destino))){
		typename map<int,C>::const_iterator it = grafo.find(origen);
		return it->second.find(destino) != it->second.end();
	}
    return false;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
	if ((existeVertice(origen)) and (existeVertice(destino)))
    	return grafo[origen][destino];
	return null;
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
	typename map<int, map<int,C> >::const_iterator it;
    it = grafo.begin();
    while (it != grafo.end()){
    	vertices.push_back(it->first);
    	it++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
	if (existeVertice(origen)){
		typename map<int,C>::const_iterator itBegin = grafo.find(origen))->second.begin();
		typename map<int,C>::const_iterator itEnd = grafo.find(origen))->second.end();
		while (itBegin != itEnd){
			Arco agregar(itBegin->first,itBegin->second);
			adyacentes.push_back(agregar);
			itBegin++;
		}
	}
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
	map <int,C> inicio;
    if (!existeVertice(vertice))
    	grafo[vertice] = inicio;
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
	typename map<int, map<int, C> >::iterator itera;
    itera=grafo.begin();
    while(itera != grafo.end()){
        if(itera->second.find(vertice)!= itera->second.end())
            itera->second.erase(vertice);
        itera++;
    }
    grafo.erase(vertice);
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
	agrega_arco(origen, destino, costo);
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
	if ((existeVertice(origen)) and (existeVertice(destino)))
    	grafo[origen][destino] = costo;
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    if ((existeVertice(origen)) and (existeVertice(destino))){
        ///grafo[origen].erase(destino); otra opcion
        typename map<int, map<int,C> >::iterator itera;
        typename map<int,C>::iterator itera2;
        itera=(grafo.find(origen));
        itera2=(itera->second.find(destino));
        itera->second.erase(itera2);
    }
}

template <typename C> void Grafo<C>::vaciar()
{
	grafo.clear();
}

#endif /* GRAFO_H_ */
