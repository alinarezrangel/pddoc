/****************************************************************************
*******************************
*** pddoc: El documentador oficial de PseudoD
*** Descripción: Genera una salida HTML5 desde un código en PseudoD.
*** Creador: Alejandro Linarez Rangel.
*******************************
****************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Lee una lnea del flujo de entrada, y si s == true,
// elimina los espacios.
string linea(istream& in,bool s = true)
{
	string A;
	getline(in,A,'\n');
	if(!in)
		return "";
	if(s)
	{
		A.erase(std::remove_if(A.begin(), 
	                        A.end(),
	                        [](char x){return std::isspace(x);}),
	          A.end());
  }
  return A;
}

// Devuelve un string que contiene todo el flujo.
string leerTodoElArchivo(istream& in)
{
	string all,line;
	while(getline(in,line,'\n'))
	{
		all += line + "\n";
	}
	return all;
}

// Devuelve el CSS por defecto para las paginas web generadas.
string obtenerCSSPorDefecto(void)
{
	return string("section.doc-section { background-color: #eeeeee; }\r\n") +
	       string("span.doc-section-header { background-color: #DDDDDD; font-size: 2em; }\r\n") +
	       string("span.doc-section-orden { font-style: bold; background-color: blue; }\r\n") +
	       string("span.doc-section-type { font-style: bold; background-color: blue; }\r\n") +
	       string("span.doc-section-ins { font-style: italic; background-color: blue; }\r\n") +
	       string("span.doc-section-attr { font-style: bold; background-color: green; }\r\n") +
	       string("span.doc-section-here { font-style: italic; background-color: green; }\r\n") +
	       string("span.doc-section-des-breve { }\r\n") +
	       string("span.doc-section-arg-name { font-style: italic; }\r\n") +
	       string("span.doc-section-dev-des { font-style: italic; }\r\n") +
	       string("span.doc-section-arg-des { }\r\n") +
	       string("span.doc-section-arg-decl { font-style: italic; background-color: blue; }\r\n") +
	       string("footer.docs { background-color: #DDDDDD; font-style: italic; }\r\n") +
	       string("body { background-color: #DDDDDD; }\r\n") +
	       string("section.doc-index { background-color: #eeeeee; }\r\n") +
				 string("span.doc-head-index { background-color: #DDDDDD; font-size: 2em; }\r\n") +
				 string("ul.doc-ul-index { list-style-type: none; }\r\n") +
				 string("span.doc-section-arg-ttl { color: #b33b00; }\r\n") +
				 string("span.doc-section-dev-ttl { color: #b33b00; }\r\n") +
				 string("code.doc-section-code-block { display: block; }\r\n") +
				 string("li.doc-li-index { }\r\n") +
				 string("code.block { display: block; border: 1px solid black; width: 90%; }\r\n") +
				 string("span.doc-section-error-ttl { color: #b33b00; }\r\n") +
				 string("span.doc-section-error-secure { color: green; }\r\n") +
				 string("span.doc-section-error-insecure { color: #800800; }\r\n") +
				 string("span.doc-section-error-inestable { color: red; }\r\n") +
				 string("span.doc-section-error-optional { color: #800800; }\r\n");
}

// Devuelve el header1 por defecto para las paginas web generadas.
// Este head va entre las etiquetas <head> del documento
string obtenerHeader1PorDefecto(void)
{
	return string("<!-- Header del headElement para pddoc por Alejandro Linarez Rangel -->\r\n") +
	       string("<!-- Este documento esta en HTML listo para ser copiado al oficial -->\r\n\r\n") +
	       string("<!-- Ingresa aqui tus enlaces a CSS,(el enlace al estilo ya fue agregado) -->\r\n\r\n") +
	       string("<!-- Ingresa aqui tus enlaces a scripts de JavaScript -->\r\n\r\n") +
	       string("<!-- Ingresa aqui tus scripts de JavaScript -->\r\n\r\n") +
	       string("<!-- Ingresa aqui todo lo que va dentro de la etiqueta head de HTML -->\r\n\r\n");
}

// Devuelve el header2 por defecto para las paginas web generadas.
// Este head va entre las etiquetas <body> del documento, antes que todo.
string obtenerHeader2PorDefecto(void)
{
	return string("<!-- Header del bodyElement para pddoc por Alejandro Linarez Rangel -->\r\n") +
	       string("<!-- Este documento esta en HTML listo para ser copiado al oficial -->\r\n\r\n") +
	       string("<!-- Ingresa aqui tu NavBar -->\r\n\r\n") +
	       string("<!-- Ingresa aqui tus etiquetas personales(h1,header,etc) -->\r\n\r\n") +
	       string("<!-- Ingresa todo lo que deba ir en un elemento body, antes de la pagina -->\r\n\r\n");
}

// Devuelve el footer por defecto.
string obtenerFooterPorDefecto(void)
{
	return string("<!-- Footer del bodyElement para pddoc por Alejandro Linarez Rangel -->\r\n") +
	       string("<!-- Este documento esta en HTML listo para ser copiado al oficial -->\r\n\r\n");
}

// Documenta el flujo de entrada.
string Documentar(istream& in,ostream& out,vector<string>& index)
{
	string line = "";
	vector<string> args;
	while(line != "[DOCUMENTA")
	{
		line = linea(in);
		if(line == "")
			return "</section>";
	}
	// TODO El section ya debe estar abierta
	bool isFile = false;
	bool cbreak = true;
	bool argCnt = false;
	while(line != "DOCUMENTA]")
	{
		in >> line;
		if(line == "@brief")
		{
			out << "<span class=\"doc-section-des-breve\">" << linea(in,false);
			out << "</span><br/>" << endl;
		}
		else if(line == "@arg")
		{
			string arg;
			in >> arg;
			args.push_back(arg);
			if(!argCnt)
			{
				out << "<span class=\"doc-section-arg-ttl\">Argumentos</span><br/>";
				out << endl;
				argCnt = true;
			}
			out << "&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"doc-section-arg-name\">";
			out << arg << "</span>" << endl;
			out << "<span class=\"doc-section-arg-des\">" << linea(in,false);
			out << "</span><br/>" << endl;
		}
		else if(line == "@dev")
		{
			out << "<span class=\"doc-section-dev-ttl\">Devuelve:</span> <span class=\"doc-section-dev-des\">";
			out << linea(in,false) << "</span><br/>" << endl;
		}
		else if((line == "@file")||(line == "@section"))
		{
			isFile = true;
			out << "<span class=\"doc-section-header\">" << linea(in,false);
			out << "</span><br/>" << endl;
		}
		else if(line == "@nsection")
		{
			isFile = true;
			string ref,ttl;
			in >> ref;
			ttl = linea(in,false);
			out << "<a name=\"" << ref;
			out << "\"></a><span class=\"doc-section-header\">" << ttl;
			out << "</span><br/>" << endl;
			index.push_back("<a href=\"#" + ref + "\">" + ttl + "</a>");
		}
		else if(line == "@pbreak")
		{
			out << "<br/>" << endl;
		}
		else if(line == "@addindex")
		{
			index.push_back(linea(in,false));
		}
		else if(line == "@mark")
		{
			out << "<a name=\"" << linea(in,true) << "\"></a>" << endl;
		}
		else if(line == "@cbreak")
		{
			cbreak = false;
		}
		else if(line == "@nocbreak")
		{
			cbreak = false;
		}
		else if(line == "@argyo")
		{
			args.push_back("Yo");
			if(!argCnt)
			{
				out << "<span class=\"doc-section-arg-ttl\">Argumentos</span><br/>" << endl;
				argCnt = true;
			}
			out << "&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"doc-section-arg-name\">Yo</span>" << endl;
			out << "<span class=\"doc-section-arg-des\">Referencia com&uacute;n al valor Yo,(PseudoD la pasa automaticamente).</span><br/>" << endl;
		}
		else if(line == "@errors")
		{
			string val;
			in >> val;
			out << "<span class=\"doc-section-error-ttl\">Garantia de error: </span>";
			if(val == "Active")
			{
				out << "<span class=\"doc-section-error-secure\">Esta libre de errores inesperados</span><br/>" << endl;
			}
			else if(val == "Inactive")
			{
				out << "<span class=\"doc-section-error-insecure\">No esta libre de errores inesperados</span><br/>" << endl;
			}
			else if(val == "Volatil")
			{
				out << "<span class=\"doc-section-error-inestable\">Es realmente inestable</span><br/>" << endl;
			}
			else if(val == "Optional")
			{
				out << "<span class=\"doc-section-error-optional\">Bajo ciertas condiciones, puede lanzar un error inesperado</span><br/>" << endl;
			}
		}
		else if(line == "@list")
		{
			out << "<ul>" << endl;
		}
		else if(line == "@listel")
		{
			out << "<li>" << linea(in,false) << "</li>" << endl;
		}
		else if(line == "@listend")
		{
			out << "</ul>" << endl;
		}
		else if(line != "DOCUMENTA]")
		{
			out << line << " " << linea(in,false) << ((cbreak)? "<br/>" : "") << endl;
		}
	}
	out << "<br/></section>" << endl;
	if(isFile)
		return "";
	in >> line;
	ostringstream os;
	if(((line == "adquirir")||(line == "puntero"))||(line == "funcion"))
	{
		string A,nom,nom2 = "";
		in >> A;
		nom = A;
		for (int i = 0; i < nom.size(); i += 1)
		{
			if(nom[i] == '#')
				nom2 += 'N';
			else if(nom[i] == '.')
				nom2 += 'P';
			else
				nom2 += nom[i];
		}
		os << "<a id=\"" << nom2 << "\"></a>" << endl;
		index.push_back(string("<a href=\"#") + nom2 + string("\">") + line + string(" ") + A + string("</a>"));
		os << "<span class=\"doc-section-header\">" << line << " " << A << "</span><br/>" << endl;
		os << "<code class=\"doc-section-code-block\">";
		os << "<span class=\"doc-section-orden\">" << line << " </span>" << "<span class=\"doc-section-ins\">" << A << " </span>" << endl;
		if(line == "funcion")
		{
			for(int i = 0; i < args.size(); i += 1)
			{
				os << "<span class=\"doc-section-arg-decl\">" << args[i] << " </span>" << endl;
			}
		}
		os << "</code>";
		os << "<br/>" << endl;
	}
	if((line == "instancia")||(line == "Importar.Tipos.Instancia"))
	{
		string A,B;
		in >> B >> A;
		os << "<a id=\"" << A << "\"></a>" << endl;
		index.push_back(string("<a href=\"#") + A + string("\">instancia ") + B + string(" ") + A + string("</a>"));
		os << "<span class=\"doc-section-header\"> instancia " << B << " " << A << "</span><br/>" << endl;
		os << "<code class=\"doc-section-code-block\">";
		os << "<span class=\"doc-section-orden\">" << line << " </span>" << "<span class=\"doc-section-type\">" << B << " </span>" << "<span class=\"doc-section-ins\">" << A << "</span><br/>" << endl;
		os << "</code>";
	}
	if((line == "clase")||(line == "Importar.Tipos.Estructura"))
	{
		string A,B,nom;
		in >> B;
		nom = B;
		os << "<a id=\"" << nom << "\"></a>" << endl;
		index.push_back(string("<a href=\"#") + nom + string("\">clase ") + B + string("</a>"));
		os << "<span class=\"doc-section-header\">clase " << B << "</span><br/>" << endl;
		os << "<code class=\"doc-section-code-block\">";
		os << "<span class=\"doc-section-orden\">" << line << " </span>" << "<span class=\"doc-section-ins\">" << B << "</span><br/>" << endl;
		in >> A;
		while(A != "#(Final).")
		{
			os << "&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"doc-section-attr\">" << A << "</span><br/>" << endl;
			in >> A;
		}
		os << "<span class=\"doc-section-orden\">#(Final).</span><br/>" << endl;
		os << "</code>";
		in >> B;
		if(B == "heredar")
		{
			in >> B;
			os << "<span class=\"doc-section-clss-bs\">Hereda a </span><span class=\"doc-section-here\">" << B << "</span><br/>" << endl;
		}
	}
	return os.str();
}

int main (int argc, char const* argv[])
{
	if(argc == 1)
	{
		cerr << "Error en pddoc: Uso: pddoc (entrada) (salida) (estilo)" << endl;
		return 1;
	}
	if(argc == 2)
	{
		if(string(argv[1]) == "--help")
		{
			cout << "pddoc: Documentador de PseudoD" << endl;
			cout << "Se recomienda utilizar con PseudoD u1.9.3" << endl;
			cout << "\tpddoc --help : muestra esta ayuda y termina." << endl;
			cout << "\tpddoc --css : genera la hoja de estilo CSS por defecto para la pagina." << endl;
			cout << "\tpddoc --head1 : genera el header1." << endl;
			cout << "\tpddoc --head2 : genera el header2." << endl;
			cout << "\tpddoc --foot : genera el footer." << endl;
			cout << "\tpddoc (entrada) (salida) (estilo) (header1) (header2) (footer) (--nofoot) : documenta el archivo entrada, y lo" << endl;
			cout << "\t\talmacena en salida. Utiliza el CSS estilo." << endl;
			return 0;
		}
		if(string(argv[1]) == "--css")
		{
			cout << "/*Creado con pddoc por Alejandro Linarez Rangel*/" << endl;
			cout << obtenerCSSPorDefecto() << endl;
			return 0;
		}
		if(string(argv[1]) == "--head1")
		{
			cout << obtenerHeader1PorDefecto() << endl;
			return 0;
		}
		if(string(argv[1]) == "--head2")
		{
			cout << obtenerHeader2PorDefecto() << endl;
			return 0;
		}
		if(string(argv[1]) == "--foot")
		{
			cout << obtenerFooterPorDefecto() << endl;
			return 0;
		}
		return 1;
	}
	if(argc < 7)
	{
		cerr << "Faltan o sobran argumentos." << endl;
		return 1;
	}
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	ifstream head(argv[4]);
	ifstream bhead(argv[5]);
	ifstream foot(argv[6]);
	bool footer = true;
	if(argc >= 8)
	{
		if(string(argv[7]) == "--nofoot")
		{
			footer = false;
		}
	}
	string decl;
	vector<string> index;
	vector<string> code;
	out << "<!DOCTYPE html>" << endl;
	out << "<html>" << endl;
	out << "<head>" << endl;
	out << "<meta charset=\"utf-8\"/>" << endl;
	//out << "<title>Documentacion de " << string(argv[1]) << "</title>" << endl;
	out << "<link href=\"" << string(argv[3]) << "\" rel=\"stylesheet\" type=\"text/css\">" << endl;
	out << leerTodoElArchivo(head) << endl;
	out << "</head>" << endl;
	out << "<body>" << endl;
	out << leerTodoElArchivo(bhead) << endl;
	while(!(in.eof()))
	{
		ostringstream nout;
		decl = Documentar(in,nout,index);
		string buff;
		buff += "<section class=\"doc-section\">\r\n";
		buff += decl + string("\r\n");
		buff += nout.str() + string("\r\n");
		if((buff != "<section class=\"doc-section\">\r\n</section>\r\n\r\n")&&(buff != "<section class=\"doc-section\">\r\n<br/></section>\r\n\r\n"))
			code.push_back(buff);
	}
	if(index.size() > 0)
	{
		out << "<section class=\"doc-index\">" << endl;
		out << "<span class=\"doc-head-index\">Indice</span><br/>" << endl;
		out << "<ul class=\"doc-ul-index\">" << endl;
		for(int i = 0;i < index.size();i++)
		{
			out << "<li class=\"doc-li-index\">" << index[i] << "</li>" << endl;
		}
		out << "</ul>" << endl;
		out << "</section>" << endl;
	}
	for(int i = 0;i < code.size();i++)
	{
		out << code[i] << endl;
	}
	out << leerTodoElArchivo(foot) << endl;
	out << "<footer class=\"docs\">Esta documentacion fue creada con ";
	out << "<a href=\"https://github.com/alinarezrangel/pddoc\">pddoc</a>.</footer>" << endl;
	out << "</body>" << endl;
	out << "</html>" << endl;
	in.close();
	out.close();
	head.close();
	bhead.close();
	foot.close();
	return 0;
}
