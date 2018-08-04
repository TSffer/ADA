#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Personal
{
	public:
		virtual string Entrada() = 0;
		virtual string Salida() = 0;
		virtual void funcion() = 0;

		void consulta()
		{
            funcion();
			cout<< "Hora de Ingreso : " << Entrada() <<endl;
			cout<< "Hora de Salida  : " << Salida() <<endl;
		}
};

class Gerente : public Personal
{
	private:
		string nombreCompleto;
		int edad;
		string ambienteTrabajo;
	public:
		Gerente(string nombre,int edad,string ambiente)
		{
			this->nombreCompleto = nombre;
			this->edad = edad;
            this->ambienteTrabajo = ambiente;
		}
		string Entrada()
		{
			return  "7:00 am";
		}
		string Salida()
		{
            return "5:30 pm";
		}
		void funcion()
		{
			cout<<"Gerente: "+this->nombreCompleto<<endl;
            cout<<"Ambiente   : " <<this->ambienteTrabajo<<endl;
			cout<<"Funciones:"<<endl;
			cout<<"- Administrar la empresa."<<endl;
			cout<<"- Gestionar nuevas Inversiones."<<endl;
        }
};

class Secretaria : public Personal
{
	private:
		string nombreCompleto;
		int edad;
		string ambienteTrabajo;
	public:
		Secretaria(string nombre,int edad,string ambiente)
		{
			this->nombreCompleto = nombre;
			this->edad = edad;
			this->ambienteTrabajo = ambiente;
		}
		string Entrada()
		{
			return  "7:00 am";
		}
		string Salida()
		{
			return "6:30 pm";
		}
		void funcion()
		{
			cout<<"Secretaria : "<<this->nombreCompleto<<endl;
			cout<<"Ambiente   : " <<this->ambienteTrabajo<<endl;
			cout<<"Funciones  :"<<endl;
			cout<<"- Atender a los clientes."<<endl;
			cout<<"- Organizar los documentos."<<endl;
		}
};

class Visitor;

class Cursos
{
	public:
		virtual void accept(Visitor& )=0;
};

class Fisica : public Cursos
{
	public:
		void accept(Visitor& );
		void course()
		{
			cout<<"Fisica"<<endl;
		}
};

class Calculo : public Cursos
{
	public:
		void accept(Visitor& );
		void course()
		{
			cout<<"Calculo"<<endl;
		}
};

class Visitor
{
	public:
		virtual void visit(Fisica& )=0;
		virtual void visit(Calculo& )=0;
};

class CountAlumnosM : public Visitor
{
	private:
		string comport1,comport2;
		int numAlumnosFisica,numAlumnosCalculo;
	public:
		CountAlumnosM()
		{
			numAlumnosFisica = numAlumnosCalculo = 0;
		}
		virtual void visit(Fisica& )
		{
			//numAlumnosFisica++;
			comport1 = "Temas: a) mruv b)energia y trabajo";
		}
		virtual void visit(Calculo& )
		{
			comport2 = "Las Formulas: a) f(x) = b + mx  b) (a+b)+c = a+(b+c)";
		}
		void reportNum()
		{
			cout<<comport1<<endl;
			cout<<comport2<<endl;
			//cout<<"Nro Matriculados en Fisica :"<<numAlumnosFisica<<endl;
			//cout<<"Nro Matriculados en Calculo :"<<numAlumnosCalculo<<endl;
		}
};

class CallV : public Visitor
{
	public:
		virtual void visit(Fisica& f)
		{
			f.course() ;
		}
		virtual void visit(Calculo& c)
		{
			c.course();
		}
};

void Fisica::accept(Visitor& v)
{
	v.visit(*this);
}

void Calculo::accept(Visitor& v)
{
	v.visit(*this);
}


int main() 
{
	/*Personal *newH[] = {new Gerente("Franciso Carnales",25,"E501"),
                        new Secretaria("Sofia Garcia",27,"D45")};
	for(int i=0;i<2;i++)
	{
		newH[i]->consulta();
        cout<<endl;
    }*/

	Cursos* set[] = {new Fisica,new Calculo};
	
	CountAlumnosM countOp;
	CallV callOp;

	for(int i=0;i<2;i++)
	{
			set[i]->accept(countOp);
			cout<<endl;
			set[i]->accept(callOp);
	}
	countOp.reportNum();

	return 0;
}